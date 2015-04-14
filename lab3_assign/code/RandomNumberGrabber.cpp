#include "RandomNumberGrabber.h"

RandomNumberGrabber::RandomNumberGrabber(char* filename)
{
    m_input_file = filename;
    stream.open(filename); 
    total_numbers = ExtractNumber();
    ofc = 0;
    official_random_number = 0;

    for (int i = 0; i < total_numbers; i++)
    {
        random_numbers.push_back(ExtractNumber());
    }
}

RandomNumberGrabber::RandomNumberGrabber(char* filename, int constant_random)
{
    m_input_file = filename;
    stream.open(filename); 
    total_numbers = ExtractNumber();
    ofc = 0;
    official_random_number = constant_random;

    for (int i = 0; i < total_numbers; i++)
    {
        random_numbers.push_back(ExtractNumber());
    }
}

int RandomNumberGrabber::grab_random()
{
    if (official_random_number == 0)
    {
        cout << "Error: mod# has to be greater than 0" << endl;
    }

    else
    {
        int return_value = (random_numbers[ofc] % official_random_number);
        ofc = ofc + 1;
        if (ofc == total_numbers)
            ofc = 0;
        return return_value;
    }
}

int RandomNumberGrabber::myrandom(int burst)
{
    int return_value = (random_numbers[ofc] % burst);
    ofc = ofc + 1;
    if (ofc == total_numbers)
        ofc = 0;
    return return_value;
}

void RandomNumberGrabber::ReadUntilCharacter(){
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
    }
}

int RandomNumberGrabber::ExtractNumber() {
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

bool RandomNumberGrabber::PeekEnd() {
    return (stream.peek(), stream.eof());
}

void RandomNumberGrabber::PrintShit() {
    cout << "The fifth number of this random shit is: " << random_numbers[4] << endl;
    for (int i = 0; i < total_numbers + 5; i++)
    {
        cout << myrandom(100) << endl; 
    }
}
