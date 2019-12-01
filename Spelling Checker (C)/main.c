#include <stdio.h>
#include <stdlib.h>
#include "Linklist.h"
#include "config.h"
#include "checkFunc.h"
#include "check.h"

int main(int argc, char* argv[])
{
    Settings a;
    List b;
    List c;
    Settings* settings = &a;
    List* dictList = createList();
    List* userList = createList();


    printf("+----------------------------------------+\r\n");
    printf("|      Awesome Autocorrect Program       |\r\n");
    printf("+----------------------------------------+\r\n");


    //The spec sheet is ambigous, if argv is null ill error here but in the case that the file doesnt exist the FileIO function with pick that up
    if((argv[1] == NULL || argc != 2))
    {
        printf("\r\n");
        printf("+------------------------------------------------------------+\r\n");
        printf("|       Sorry, there was an error opening the Document       |\r\n");
        printf("|                      Please try again                      |\r\n");
        printf("+------------------------------------------------------------+\r\n");
    }
    

    else
    {
        //ill create the structs either here or start of the program 
        openConfig("spellconf", settings);
        
        openDict("mydict.txt",dictList);
        
        openUFile(argv[1], userList);
        printf("+--------------Help--------------------------+\r\n");


        if(settings->autoCorrect == 'y')
        {
            check(arrayify(userList), userList->size, arrayify(dictList), dictList->size, settings->maxDiff, &autoCorrect);
        }

        else
        {
            check(arrayify(userList), userList->size, arrayify(dictList), dictList->size, settings->maxDiff, &userCorrect);
        }
    }
}