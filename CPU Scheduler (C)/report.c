Data Structures:

// All Structs
    Task: Task is a struct that stores the task#, burst time, arrival time and service.

    Node: just a struct thats stores a Task struct and a pointer to the next Node.

    Queue: is a linked list, an implemented of a first in first out data structure where the data stored is a Node.

    CPU_Stats: just a struct to store, num_tasks, total time waiting and total turnaround time.

// All variables
    lock: Is a mutex lock from the pthread library. Accesed by both cpu and the task threads.

    queue_empty: Is a condition variable to signal that the queue is empty. Accesed by both cpu and the task threads.

    queue: Is a Queue struct. Accesed by both cpu and the task threads.

    cpu_stats: Is a CPU_Stats struct. Accesed by the cpu threads.

    task_file: Is a string for the task file that is going to be used. Accessed by the task thread

    fp & fpS: Are file pointers. Used by both but not shared, similar to using i in a for loop.

    newTask1 & newTask2: Are task structs that are used to enqueue the tasks to the queue. Accesed by the task thread.

    current_time: Is a time_t data type from the time.h library.

    time_info: Is a tm struct (a struct from the time.h library) its used to structure the time for the simulation_log file. Accesed by the task thread.

    cpuN: Is an int used to describe which cpu# each thread is. Accesed by the cpu threads.

    task_cpu_completed: Is and int that counts the tasks that a cpu thread completes. Accesed by the cpu threads.

    arrival_t, service_t, comp_t: Are time_t data types and they are used to store the time of the events that there respective name represents. Accesed by the cpu threads.
    
    *arrival_tm, *service_tm, *comp_tm: Are tm structs they are used to format the time strings for output into the simulation_log file. Accesed by the cpu threads.
    
    holder_task: Is a Task struct and is being used as a holder so that the first item in the queue can be dequeued but still operated on. Accesed by the cpu threads.
    
    arrival_time, service_time, completion_time: Are strings that store the correctly formated time for the time there respective events occured. Accesed by the cpu threads.
    
    total_local_waiting_time: Is the time that each cpu thread spent waiting it is later added to the total waiting time. Accesed by the cpu threads.
    
    total_local_turn_around_time: Is the turnaround time that each cpu thread experienced and is later added to the total turnaround time. Accesed by the cpu threads.
    
    max_queue_size: Is and int that stores the command line input for the maxium sized of the queue. Accesed by the main thread and the task thread.

// How Mututal exclusion is achieved.
    Mututal exclusion is achieved by using "pthread_mutex_lock(&lock);" the cpu and task threads all access the shared resource of the queue.
    Only the thread that has access to the lock has access to the shared resource. This prevents any race conditions from occurring.
    After each thread no longer needs access  to the shared resource they exit the their critical section by releasing the lock by using,
    "pthread_mutex_unlock(&lock);" Although the simulation_log file is a shared resource the OS handles synchronisation. And why I kept them out of the lock.

// Working?
    The language on the assignment sheet with regards to blocking is interesting.
    I have interpreted it as fill the queue up and wait for it to be emptied. until there is no more tasks.
    If thats right then the program works perfectly. I tested it by running the program with all possible inputs.
    (I also tested it with weird settings to see what happens but thats not needed, (like 10000 tasks and 100 cpus)).
    The way I tested invloved running it and checking if the output matches what I expected based on the specs of the assignment.
