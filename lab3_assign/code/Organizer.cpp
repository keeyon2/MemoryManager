#include "Organizer.h"

Organizer::Organizer(char* input_file, char* random_file, char* options, char* algorithm,
       int num_of_frames)
{
   MrRandom = new RandomNumberGrabber(random_file);
   stream.open(input_file);
   CreateInstructionVector();       

}

void Organizer::CreateInstructionVector() {
    ReadUntilInstruction();
    int read_write;
    int v_page;
    while(!PeekEnd())
    {
        read_write = ExtractNumber();
        v_page = ExtractNumber();
        Instruction temp_inst = new Instruction(read_write, v_page);
        instruction.push_back(temp_inst);
    }
}


/****************
**   Reading  **
*****************/

void Organizer::ReadUntilInstruction() {
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


int Organizer::ExtractNumber() {
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

void Organizer::ReadUntilCharacter(){
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

bool Organizer::PeekEnd() {
    return (stream.peek(), stream.eof());
}

void Organizer::ReadUntilNewline() {
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
