#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "RandomNumberGrabber.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

ofstream random_file;
ofstream input_file;

int main(int argc, char **argv)
{
    int c;
    char *options = NULL;
    
    // We are setting the default values for when no args
    int num_of_frames = 0;    
    char *algorithm = NULL;

    bool option_O = false, option_P = false, option_F = false,
         option_S = false, option_p = false, option_f = false,
         option_a = false, is_o = false;

    while ((c = getopt (argc, argv, "aof:")) != -1)
    {
        switch(c)
        {
            case 'a':
                algorithm = optarg;
                break;
            case 'o':
                is_o = true;
                options = optarg;   
                break;
            case 'f':
                num_of_frames = atoi (optarg); 
                break;
            case '?':
                if (optopt == 'a' || optopt == 'f' || optopt == 'o')
                {
                    cout << "Option -" << optopt << " requires an argument" << endl;
                    abourt ();
                }
                else
                {
                    cout << "Unknown option character -" << optopt << endl;
                    abort ();
                }
                // Exit Prog
                return 1;
                abort();
            default:
                num_of_frames = 32;
                algorithm = 'l';
        }
    }
    char* input_file = argv[argc - 2];
    char* random_file = argv[argc - 1];


    Organizer (input_file, random_file, options, algorithm, num_of_frames);

    // Set Algorithm
    switch(algorithm)
    {
        case 'N':
            // Create NRU
            break;
        case 'l':
            // Create LRU
            break;
        case 'r':
            // Creat Random
            break;
        case 'f':
            // Create FIFO
            break;
        case 's':
            // Create Second Chance
            break;
        case 'c':
            // Create Physical Clock
            break;
        case 'X':
            // Create Virtual Clock
            break;
        case 'a':
            // Create Aging
            break;
        case 'Y':
            // Create Aging
            break;
        default:
            cout << "Error:  not understandable algorithm selection" << endl;


    }
    // Printing out to test
}

void ReadUntilInstruction() {
    char c;
    int instruct;
    int read_write;

    ReadUntilCharacter();

    if (PeekEnd())
    {
        // Error
    }

    while(!PeekEnd())
    {
        c = stream.peek();
        if (c == '#')
        {
            ReadUntilNewLine();
            ReadUntilCharacter();
        }

        else if(isdigit(c))
        {
            return;
        }
    }
}


int ExtractNumber() {
    string number;
    char c;
    ReadUntilCharacter();

    // If we have readed End of the file Expect Number
    if (PeekEnd())
    {
        //Error
    }

    while (!PeekEnd())
    {
        stream.get(c);
        if ((c != ' ') && (c != '\t') && (c != '\n'))
        {
            if (!isdigit(c))
            {

                cout << "SHOULD BE DIGIT" << endl;
            }

            number += c;
        }
        else
            break;
    }
    return atoi(number.c_str());
}

void ReadUntilCharacter(){
    char c;
    while(!PeekEnd())
    {
        c = stream.peek();
        if ((c == ' ') || (c == '\t') || (c == '\n'))
        {
            stream.get(c);
        }
        else
            return;
    }
    if (PeekEnd())
    {
        //Reset to the start of the file
        return;
    }
}

bool Scheduler::PeekEnd() {
    return (stream.peek(), stream.eof());
}

void ReadUntilNewline() {
    char c:
    while(!PeekEnd())
    {
        c = stream.get(c);
        if (c != '\n')
        {
            stream.get(c);
        }
        else
            return;
    }
    if(PeekEnd())
    {
        return;
    }
}
