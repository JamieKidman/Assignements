typedef struct Task
{
    int number;
    int burst;
    time_t arrival;
    time_t service;
} Task;

typedef struct Node
{
	struct Task data;
	struct Node* next;
} Node;

typedef struct Queue
{
    int done;
    int count;
    struct Node *front;
    struct Node *rear;
} Queue;

typedef struct CPU_Stats
{
    int num_tasks;
    int total_waiting_time;
    int total_turnaround_time;
} CPU_Stats;
