#ifndef RandomNumberGrabber_H
#define RandomNumberGrabber_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;

class RandomNumberGrabber
{
    int ofc;
    int total_numbers;
    int official_random_number;
    string m_input_file;
    char* random_char_file;
    ifstream stream;
    vector<int> random_numbers;
    public:
        RandomNumberGrabber(string filename);
        RandomNumberGrabber(string filename, int constant_random);
        int grab_random();
        int myrandom(int burst);
        void ReadUntilCharacter();
        int ExtractNumber();
        bool PeekEnd();
        void PrintShit();
};

#endif
