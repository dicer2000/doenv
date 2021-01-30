/********************************************
 * doenv - A env derivation program
 * Brett Huffman
 * CMP SCI 4760 - Project 1
 * Due Feb 9, 2021
 * Main CPP file for project
 ********************************************/
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Forward declarations
static void show_usage(std::string);
void printEnvironment();

// Environmental Extern (gobal)
extern char **environ;

// Main - expecting arguments
int main(int argc, char* argv[])
{
    // Argument processing
    int opt;
    bool bReplaceEnvironmentVars = false;

    // Vectors to hold Vars & Commands
    std::vector<std::string> vecEnvVars;
    std::vector<std::string> vecCommands;

    // Go through each parameter entered and
    // prepare for processing
    while ((opt = getopt(argc, argv, "hi")) != -1) {
        switch (opt) {
            case 'h':
                show_usage(argv[0]);
                return 0;
            case 'i':
                bReplaceEnvironmentVars = true;
                break;
            case '?': // Unknown arguement
                if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                        "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:    // An bad input parameter was entered
                // Show error because a bad option was found
                perror ("doenv: Error: Illegal option found");
                show_usage(argv[0]);
                return 1;
        }
    }

    // Finally, process the non-switch arguements
    for (int index = optind; index < argc; index++)
    {
        std::string strVal = argv[index];
        // Environment Vars will be of the form
        // name=value
        if(strstr(argv[index], "=") != NULL)
            vecEnvVars.push_back(strVal);
        else    // Otherwise, its a Command
            vecCommands.push_back(strVal);

    }

    // DEBUG
    std::cout << "Env Vars" << std::endl;
    for(std::vector<std::string>::const_iterator f = vecEnvVars.begin(); f != vecEnvVars.end(); ++f)
        std::cout << *f << std::endl;
    std::cout << "Commands" << std::endl;
    for(std::vector<std::string>::const_iterator f = vecCommands.begin(); f != vecCommands.end(); ++f)
        std::cout << *f << std::endl;
    
    // If the -i argument added, wipe out all
    // the existing env vars
    if(bReplaceEnvironmentVars)
    {
        // Blow out Env Vars
        #if defined(unix) || defined(__unix__) || defined(__unix)
            // UNIX Variety of OS // printf("UNIX\n");
            clearenv();
        #else
            // MacOS Or Windows Variety of OS // printf("MacOS\n");
            *environ = NULL;
        #endif
        

        /*
        char *strCurrentVal = *environ;
        int nVarIndex = 1;
        // Loop and unset everything in environ
        for (; strCurrentVal; nVarIndex++) {
            // Get the name token the old fashioned way
            char *tName = strtok(strCurrentVal,"=");
            // If found "=", then get name
            if(tName != NULL)
            {
                printf("===>%s\n", tName);
                unsetenv(tName);
            }

            strCurrentVal = *(environ+nVarIndex);
        }
        */
    }

    // If no new Environ Vars specified, 
    // then just print environment
    if(vecEnvVars.size() < 1)
    {
        printEnvironment();
        return 0;
    }

    // If Environ Vars specified Add them
    for(std::vector<std::string>::const_iterator envItem = vecEnvVars.begin(); envItem != vecEnvVars.end(); ++envItem)
    {
        // Split the name/value pairs
        size_t pos = 0;
        std::string nameToken, valueToken;
        if ((pos = envItem->find("=")) != std::string::npos)
        {
            nameToken = envItem->substr(0, pos);
            valueToken = envItem->substr(pos+1);
            if(nameToken.size() > 0 && valueToken.size() > 0)
                setenv(nameToken.c_str(), valueToken.c_str(), true);
        }
    }


        // If no commands, just print the updated environment
        if(vecCommands.size() < 1)
            printEnvironment();
    else
    {
        // Otherwise execute the command in the
        // updated shell
        system("ls");
    }


    return 0;
}

// Print the Environment Variables
void printEnvironment()
{
    // If empty environ, print nothing
    if(environ == NULL)
    {
        return;
    }

    // Get all Current Environment Vars
    // This is a char* pointing to an array of strings
    char *strCurrentVal = *environ;

    int nVarIndex = 1;
    for (; strCurrentVal; nVarIndex++) {
        printf("%s\n", strCurrentVal);
        strCurrentVal = *(environ+nVarIndex);
    }
}


// Handle errors in input arguments by showing usage screen
static void show_usage(std::string name)
{
    std::cerr << std::endl
              << name << " - env tool by Brett Huffman for CMP SCI 4760" << std::endl
              << std::endl
              << "Usage:\t" << name << " [-h\n" << std::endl
              << "\t" << name << " [-i] [var1=value] [var2=value] [...] {command1 [; command2] [; ...]}" << std::endl
              << "Options:" << std::endl
              << "  -h Show this help message" << std::endl
              << "  -i Replace the external environment variable" << std::endl
              << "  Optional environment variables can be defined to add/replace variables" << std::endl
              << "  Commands are utilities to execute after the environment has been changed" << std::endl
              << "  If commands are omitted, the updated environment is printed"
              << std::endl << std::endl;
}