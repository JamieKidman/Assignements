//This struct is for the config file .spellconf
// it stores the name of the dictionary file, the maximum allowed difference before correction, and it stores a boolean char for yes or no for auto or user correct
#ifndef CONFIG_h
typedef struct
{
    char* dict;
    int maxDiff;//how many letters are allowed to be different
    char autoCorrect; // im just storing the first letter tbh im tempted to store it as an int because its just a boolean
} Settings;

#define CONFIG_h

#endif