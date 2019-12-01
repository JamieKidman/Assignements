#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "Linklist.h"
#define null NULL //this caused an error and this was the easiest fix, yes i could have done find and replace, then again in check.h you define true and false

void openUFile(char* fileName, List* userList)
{
    FILE* ufp; 
    ufp = fopen("user.txt", "r");
    if(ufp==null)
        printf(" +------------------------------------------------------------+\r\n |                Failed to open user document                |\r\n +------------------------------------------------------------+\r\n");

    else
    {
        int i = 0;
        char holder[64];
        printf("HELP");
        while(fgets(holder,64,ufp))
        {
    
            addNode(userList, holder);

            if(holder =="\0")
                return;
                i++;
        }
    }
}

void openConfig(char* configName, Settings *inSettings)
{
    
    FILE* cfp;
    cfp = fopen(configName, "r");
    if(cfp==null)
    printf(" +------------------------------------------------------------+\r\n |                Failed to open config file                  |\r\n +------------------------------------------------------------+\r\n");    
    
    else
    {
        char holder[18];
        fscanf(cfp, "%18s", holder);

            fscanf(cfp, "%18s", holder);//there is a space then = the space so to get the variable i just go to the next one
            fscanf(cfp, "%18s", holder);

            inSettings->dict = holder;
        
        fscanf(cfp, "%18s", holder);
        
            fscanf(cfp, "%18s", holder);
            fscanf(cfp, "%18s", holder);

            inSettings->maxDiff = atoi(holder);
        

        fscanf(cfp, "%18s", holder);
        
            fscanf(cfp, "%18s", holder);
            fscanf(cfp, "%18s", holder);

            inSettings->autoCorrect = holder[0];
        printf("%s", &holder);
    }
}

void openDict(char* inDict, List* dictList)
{
    FILE* dfp;
    dfp = fopen("mydict.txt", "r");
    if(dfp==null)
    {
        printf(" +------------------------------------------------------------+\r\n |              Failed to open dictionary file                |\r\n +------------------------------------------------------------+\r\n");
        return;
    }
    else
    {
        char holder[64];
        while((fscanf(dfp, "%64s" , holder) !=0))
        {
            addNode(dictList, holder);
        }
    }
}