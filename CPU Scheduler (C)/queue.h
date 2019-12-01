#include<stdio.h>
#include<stdlib.h>
#include "structs.h"

void initQueue(Queue *inQueue)
{
	inQueue->done = 0;
    inQueue->count = 0;
    inQueue->front = NULL;
    inQueue->rear = NULL;
}

int isempty(Queue *inQueue)
{
    return (inQueue->rear == NULL);
}

void enqueue(Queue *inQueue, Task inTask)
{
	Node *holder;
	holder = calloc(1, sizeof(Node));
	holder->data = inTask;
	holder->next = NULL;

	if(inQueue->front != NULL)
	{
		inQueue->rear->next = holder;
		inQueue->rear = holder;
	}

	else
	{
		inQueue->front = inQueue->rear = holder;
	}

	inQueue->count++;

}

void dequeue(Queue *inQueue)
{
	if(inQueue->count == 0)
	{
		inQueue->front = NULL;
		inQueue->rear = NULL;
	}
	else
	{
		Node* holder = inQueue->front->next;
		free(inQueue->front);
		inQueue->front = holder;
		inQueue->count--;
	}
	
}