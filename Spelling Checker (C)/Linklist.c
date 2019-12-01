#include "Linklist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Default Constructor
List* createList()
    {
        List* input = calloc(1, sizeof(List));
        return input;
    }

    // using calloc becuase "strings" in c are a pain
    // this function adds a node to the end of the list and stores the data in the heap 
void addNode(List* inList, char* inWord)
    {
        Node* node = calloc(1, sizeof(Node));
        node->word =  calloc(strlen(inWord), sizeof(char));
        strcpy(node->word, inWord);
        inList->tail = node;

        if (inList->size==0)
            inList->head=node;

            //storeing the size of the list is more effeicient than calculationg it
            inList->size++;
    }
    //given a node this function will return the next node, its kinda redundant but it helps me think. yes it really is redundant but i like it
Node* getNext(Node* current)
{
    return current->next;
}

//frees all the memory inorder to delete the link list
void deleteList(List* list)
    {
        Node* current=list->head;
        Node* holder;

        for(list->size; list->size >=0; list->size--)
        {
            holder = current;
            current = getNext(current);
            free(holder);
        }
        free(list);

        if(current != NULL)
            free(current);
    }
//muhahhahahahaha
// turns a linklist to a dynamiclly allocated array
char** arrayify(List* list)
{
    //next /first, it starts out as current then moves to next
    Node* current = list->head;
    Node* holder = list->head;
    
    char** dynamicArray = malloc(list->size * sizeof(char*));
    
    
    int i = list->size;
    for(i; i >= 0; i--)
    {
        holder = current;
        current = current->next;
        
        char* word = calloc(strlen(holder->word), sizeof(char));
        strcpy(word, holder->word);
    }
    return dynamicArray;
}
//#define </tag> "" //nice try
//#<tag>