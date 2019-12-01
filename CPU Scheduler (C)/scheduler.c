#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "queue.h"

// Initialising Locks and cpu_stats data
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_empty = PTHREAD_COND_INITIALIZER;
Queue queue;
CPU_Stats cpu_stats;
char *task_file;

// Makes the task file
int task_file_maker(char task_file[])
{
    FILE *fp;
    fp = fopen(task_file, "w");
    srand(time(NULL));

    for(int i=1; i<=100; i++)
    {
        fprintf(fp, "%d %d\n", i, rand() % 50);
    }

    fclose(fp);
    return 0;
}

// Reads the task_file and adds it to a queue with a fixed size
void* task(void *max_queue_size)
{
    FILE *fp;
    fp = fopen(task_file, "r");
    int count = 0;
    while(!feof(fp))
    {
        pthread_mutex_lock(&lock);
        while(queue.count + 2 <= *(int *)max_queue_size) // count + 2 to prevent going over the max size as function adds two tasks.
        {
            Task newTask1;
            Task newTask2;
            int t1_number, t1_burst, t2_number, t2_burst = 0;

            // Ugly Time Formatting Code
            time_t current_time;
            struct tm * time_info;
            char timeString[9];

            time(&current_time);
            time_info = localtime(&current_time);
            strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);

            // Reading in Two Tasks
            fscanf(fp, "%d %d", &t1_number, &t1_burst);
            fscanf(fp, "%d %d", &t2_number, &t2_burst);

            if(feof(fp))
            {
                pthread_mutex_unlock(&lock);
                break;
            }

            newTask1.number = t1_number;
            newTask1.burst = t1_burst;
            newTask1.arrival = time(0);
            newTask2.number = t2_number;
            newTask2.burst = t2_burst;
            newTask2.arrival = time(0);

            enqueue(&queue, newTask1);
            enqueue(&queue, newTask2);

            FILE *fpS;
            fpS = fopen("simulation_log","a");

            fprintf(fpS, "%d: %d \nArrival time: %s\n", newTask1.number, newTask1.burst, timeString);
            fprintf(fpS, "%d: %d \nArrival time: %s\n", newTask2.number, newTask2.burst, timeString);

            fclose(fpS);
            count += 2;
        }
        pthread_cond_wait(&queue_empty, &lock);
        pthread_mutex_unlock(&lock);
    }
    queue.done = 1;

    FILE *fpS;
    fpS = fopen("simulation_log","a");

    time_t current_time;
    struct tm * time_info;
    char timeString[9];

    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);

    fprintf(fpS, "Number of tasks put into Ready-Queue: %d\nTerminate at time: %s\n", count, timeString);

    fclose (fpS);

    return 0;
}


void* cpu(void *incpuN)
{
    int cpuN = (int *) incpuN;
    int task_cpu_completed;
    time_t arrival_t, service_t, comp_t;
    struct tm *arrival_tm, *service_tm, *comp_tm;
    struct Task holder_task;
    char arrival_time[9];
    char service_time[9];
    char completion_time[9];
    int total_local_waiting_time = 0;
    int total_local_turn_around_time = 0;

    while(1)
    {
        pthread_mutex_lock(&lock);
        if(queue.done == 1 && queue.count == 0)
        {
            // Adding local turnaround time and waiting time to the cpu_stats data here
            cpu_stats.total_waiting_time += total_local_waiting_time;
            cpu_stats.total_turnaround_time += total_local_turn_around_time;

            // File IO
            FILE *fp;
            fp = fopen("simulation_log","a");
            fprintf(fp, "CPU-%d, Tasks Completed: %d\n", cpuN, task_cpu_completed);
            fclose(fp);

            pthread_mutex_unlock(&lock);
            break;
        }

        // Accessing cpu_stats Data, if queue.front == NULL then the lock is released in the else()
        if(queue.count != 0)
        {
            holder_task = queue.front->data;

            dequeue(&queue);
            cpu_stats.num_tasks++;
            pthread_mutex_unlock(&lock);
            // ^Unlocking because fprintf() is techncally thread safe in the sense the data wont intermingle

            // Ugly Code to format the time for arrival
            arrival_tm = localtime(&holder_task.arrival);
            strftime(arrival_time, sizeof(arrival_time), "%H:%M:%S", arrival_tm);
            arrival_t = mktime(arrival_tm);

            // Ugly Code to format the time for service
            time(&service_t);
            service_tm = localtime(&service_t);
            strftime(service_time, sizeof(service_time), "%H:%M:%S", service_tm);

            // Ugly Code to format the time for completion
            time(&comp_t);
            comp_tm = localtime(&comp_t);

            // Completion time = Service time + cpu_burst
            if(comp_tm->tm_sec += holder_task.burst > 60)
                comp_tm->tm_min += 1;

            comp_tm->tm_sec = (comp_tm->tm_sec += holder_task.burst) % 60;
            strftime(completion_time, sizeof(completion_time), "%H:%M:%S", comp_tm);

            // File IO
            FILE *fp;

            fp = fopen("simulation_log","a");
            fprintf(fp, "Statistics for CPU-%d:\nTask %d\nArrival time: %s\nService time: %s\n", cpuN, holder_task.number, arrival_time, service_time);
            fclose(fp);

            // Sleeping for a time proportional to the length of cpu_burst
            usleep(holder_task.burst*100);

            // More File IO
            fp = fopen("simulation_log","a");
            fprintf(fp, "Statistics for CPU-%d:\nTask %d\nArrival time: %s\nCompletion time: %s\n", cpuN, holder_task.number, arrival_time, completion_time);

            fclose(fp);

            task_cpu_completed++;
            total_local_waiting_time += difftime(service_t, arrival_t);
            total_local_turn_around_time += difftime(comp_t, arrival_t);
        }
        else
        {
            pthread_cond_signal(&queue_empty);
            pthread_mutex_unlock(&lock);
        }
    }
    return 0;
}


int main(int argc, char *argv[])
{
    // Basic Initialisation
    int max_queue_size = atoi(argv[2]);
    task_file = argv[1];
    task_file_maker(argv[1]);
    initQueue(&queue);

    FILE *fp;
    fp = fopen("simulation_log","w");
    fprintf(fp, "");
    pthread_t task_thread;
    pthread_t cpu_threads[4];

    if(max_queue_size <= 1)
        return 0; // Not great, should have a message, however wasn't allowed to add one
    if(max_queue_size >= 10)
        return 0; // Not great, should have a message, however wasn't allowed to add one
 


    // Creating Threads
    pthread_create(&task_thread, NULL, &task, &max_queue_size);

	for (int i = 1; i < 4; i++) 
    {
		pthread_create(&cpu_threads[i], NULL, &cpu, i);
	}

    // Joining all the Threads
    pthread_join(task_thread, NULL);

    for (int i = 1; i < 4; i++) 
    {
        pthread_join(cpu_threads[i], NULL);
    }

    // File IO
    FILE *fpS;
    fpS = fopen("simulation_log","a");
    fprintf(fpS, "Number of tasks: %d\nAverage waiting time: %d seconds\nAverage turn around time: %d seconds\n", cpu_stats.num_tasks, cpu_stats.total_waiting_time/cpu_stats.num_tasks, cpu_stats.total_turnaround_time/cpu_stats.num_tasks);
    fclose(fpS);

    return 0;
}
