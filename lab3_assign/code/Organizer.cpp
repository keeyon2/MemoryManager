#include "Organizer.h"

Organizer::Organizer(char* input_file, char* random_file, char* options, char* algorithm,
       int num_of_frames) : MrRandom(random_file, num_of_frames)
{
    SetOptions(options);
    CreateInstructionVector(input_file);       
    // figure out options
    // Need to Create Page Table 
}

void Organizer::SetOptions(char* options){
    option_O = false, option_P = false, option_F = false, 
    option_S = false, option_p = false, option_f = false,
    option_a = false;

    if(options != NULL)
    {
        string all_ops = string(options);
        SetIndivOption(all_ops, 'O', &option_O);
        SetIndivOption(all_ops, 'P', &option_P);
        SetIndivOption(all_ops, 'F', &option_F);
        SetIndivOption(all_ops, 'S', &option_S);
        SetIndivOption(all_ops, 'p', &option_p);
        SetIndivOption(all_ops, 'f', &option_f);
        SetIndivOption(all_ops, 'a', &option_a);
    } 

    cout << "Option_O: " << option_O << endl;
    cout << "Option_P: " << option_P << endl;
    cout << "Option_F: " << option_F << endl;
    cout << "Option_S: " << option_S << endl;
    cout << "Option_p: " << option_p << endl;
    cout << "Option_f: " << option_f << endl;
    cout << "Option_a: " << option_a << endl;

}

void Organizer::SetIndivOption(string all_ops, char c, bool* option)
{
        int pos = all_ops.find(c);
        cout << "POS: " << pos << endl;
        //if (pos != npos)
        if (pos > -1)
        {
            *option = true;
        }
}

void Organizer::CreateInstructionVector(char* input_file) {
    stream.open(input_file);
    ReadUntilInstruction();
    int read_write;
    int v_page;

    while(!PeekEnd())
    {
        read_write = ExtractNumber();
        v_page = ExtractNumber();
        Instruction temp_inst (read_write, v_page);
        instructions.push_back(temp_inst);
    }

    reverse(instructions.begin(), instructions.end());
}

Instruction Organizer::PopNextInstruction()
{
    Instruction i = instructions[0];
    instructions.erase(instructions.begin());
    return i;
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
            ReadUntilNewline();
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
    char c;
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
