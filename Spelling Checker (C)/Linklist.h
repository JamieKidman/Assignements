//This is a struct that defines what a node/link is in a link list.
//It stores a word and a pointer to the next node
#ifndef LINKLIST_h
typedef struct Node
{
    char* word;
    struct Node* next;
}  Node;
//This is a struct that defines what a list is
//It stores its size, what the start of the list (the first node) is and the end of the list (the last node)
// essentail it stores a list of words

typedef struct
{
    int size;
    Node* head;
    Node* tail;
} List;

#define LINKLIST_h

#endif

List* createList();
void addNode(List*, char*);
Node* getNext(Node*);
void deleteList(List*);
char** arrayify(List*);
