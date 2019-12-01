#include <stdio.h>
//TESTING MAIN ONLY
int main()
{
    char userInput;
    while(!(userInput == 'y' || userInput == 'n'))
    {
        printf("Please type \"y\" or \"n\" \r\n");
        scanf("%c", &userInput);

        if(userInput == 'y')
        {
            printf("The suggestion was accepted\r\n");
            return 1;
        }
//else statement was creating a bug
        if(userInput == 'n') //else statement was creating a bug
        {
            printf("The suggestion was not accepted\n");
        }
    }
}
//TESTING ONLY