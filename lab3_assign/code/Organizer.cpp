#include "Organizer.h"

Organizer::Organizer(char* input_file, char* random_file, char* options, char* algorithm,
       int num_of_frames) : MrRandom(random_file, num_of_frames)
{
    // Initializations
    frame_table_size = num_of_frames;
    SetOptions(options);
    CreateInstructionVector(input_file);       
    CreateTables();    

    // Logic
    RunThroughInstructions();
}

void Organizer::CreateTables()
{
    for (int i = 0; i < 64; i++)
    {
        page_table[i].ref = 0;
        page_table[i].mod = 0;
        page_table[i].present = 0;
        page_table[i].p_out = 0;
        page_table[i].page_index = 0;
    }
    
    frame_table.SetTable(frame_table_size, page_table);
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

}

void Organizer::SetIndivOption(string all_ops, char c, bool* option)
{
        int pos = all_ops.find(c);
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

void Organizer::RunThroughInstructions() {
    int v_index;
    while (!instructions.empty())
    {
        current_inst += 1;
        Intrunction inst = GetInstruction();

        //Print O
        if (option_O)
        {
            int t;
            if (inst.read)
               t = 0;
            else
               t = 1; 
            cout << "==> inst: " << t << " " << inst.virtual_frame << endl;
        }

        
        v_index = inst.virtual_frame;
        
        // If Present in RAM
        if (page_table[v_index].present)
        {
            ACCESS(inst); 
        } 

        // Not Present
        else
        {
            int avail_fr = -1;
            for (int i = 0; i < frame_table_size.size(); i++)
            {
                if (!frame_table.entries)
                {
                    avail_fr = i;
                    break;
                }
            }

            // Have Available Spot in Ram at avail_fr
            if (avail_fr >= 0)
            {
                ZERO(inst, avail_fr);
                MAP(inst, avail_fr);
            }

        }
    }
}

Instruction Organizer::GetInstruction() {
    Instruction temp = instructions.back();
    instructions.pop_back();
    return temp;
}

void Organizer::UNMAP(Instruction inst) {

    total_unmap += 1;
    total_cycles += 400;
}

void Organizer::MAP(Instruction inst, int phys_frame) {
    total_map += 1;
    total_cycles += 400;

    frame_table.entries[phys_frame] = true; 
    page_table[inst.virtual_frame].present = true;
    page_table[inst.virtual_frame].page_index = phys_frame;

    if (option_O)
    {
        cout << current_inst << ": MAP      " << phys_frame << endl; 
    } 
}

void Organizer::IN(Instruction inst) {
    total_in += 1;
    total_cycles += 3000;
}

void Organizer::OUT(Instruction inst) {
    total_out += 1;
    total_cycles += 3000;
}

void Organizer::ZERO(Instruction inst, int phys_frame) {
    total_zero += 1;
    total_cycles += 150;
    v_index = inst.virtual_frame;

    page_table[v_index].present = 0;
    page_table[v_index].p_out = 0;

    if (option_O)
    {
        cout << current_inst << ": ZERO        " << phys_frame << endl;
    }

}

void Organizer::ACCESS(Instruction inst) {
    total_cycles += 1;

    v_index = inst.virtual_frame;
    if(inst.write)
    {
        page_table[v_index].write = 1;
    }
    page_table[v_index].read = 1;
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
