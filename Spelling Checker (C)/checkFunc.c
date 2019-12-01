#include <stdio.h>

int autoCorrect(char* original, char* suggestion)
{
    if(!(suggestion == '\0'))
    {
        printf("%s", &suggestion);
        original = suggestion;
        return 1;
    }
    return 0;
}

int userCorrect(char* original, char* suggestion)
{
    if(suggestion == '\0')
        return 0;
    char userInput;
    while(!(userInput == 'y' || userInput == 'n'))
    {
        printf("Please type \"y\" or \"n\" \r\n");
        scanf("%c", &userInput);

        if(userInput == 'y')
        {
            printf("The suggestion was accepted\r\n");
            original = suggestion;

            return 1;
        }
//else statement was creating a bug
        if(userInput == 'n') //else statement was creating a bug
        {
            printf("The suggestion was not accepted\n");
            return 0;
        }
    }
}