#include "Organizer.h"

Organizer::Organizer(char* input_file, char* random_file, char* options, char* algorithm,
       int num_of_frames) : MrRandom(random_file, num_of_frames)
{
    // Initializations
    current_inst = -1;
    frame_table_size = num_of_frames;
    SetOptions(options);
    SetAlgorithm(algorithm);
    CreateInstructionVector(input_file);       
    CreateTables();    
    
    // Logic
    RunThroughInstructions();

    // PrintFinalResults
    PrintResults();
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

void Organizer::SetAlgorithm(char* algorithm){
    // Set all the frame tables
    fifo_alg.SetFrameTable(&frame_table);
    sc_alg.SetFrameTable(&frame_table);

    // Determine which one it should be
    if (algorithm != NULL)
    {
        string alg = string(algorithm);
        // 'l' should be something else but it is ok for now
        if (alg == "l")
        {
            replacement_alg = &fifo_alg;
        }

        else if (alg == "f")
        {
            replacement_alg = &fifo_alg;
        }

        else if (alg == "s" || alg == "c")
        {
            replacement_alg = &sc_alg;
        }

    }   

    else
    {
        // Do the same as 'l'
        replacement_alg = &fifo_alg;
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
    char c;
    char d_me[256];

    while(!PeekEnd())
    {
        c = stream.peek();
        if (c == '#')
        {
            stream.getline(d_me, 256);
            continue;
        }
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
        Instruction inst = GetInstruction();

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
        
        // // If Present in RAM
        // if (page_table[v_index].present)
        // {
        //     int phys_frame = page_table[v_index].page_index;
        //     ACCESS(inst, phys_frame); 
        // } 

        // // Inst Not Present in RAM (Pagefault)
        // else

        // Inst Not Present in RAM (Pagefault)
        if (!page_table[v_index].present)
        {
            int avail_fr = -1;
            for (int i = 0; i < frame_table_size; i++)
            {
                if (!frame_table.entries[i])
                {
                    avail_fr = i;
                    break;
                }
            }

            // Have Available Spot in Ram at avail_fr
            if (avail_fr >= 0)
            {
                BringInstToRam(inst, avail_fr);
            }

            // Need to replace Element from Ram  
            else
            {
                int delete_phys_frame = replacement_alg->GetReplacement();
                int deleting_v_frame = FindDeletingVPage(delete_phys_frame);

                // Take element of RAM
                UNMAP(inst, delete_phys_frame, deleting_v_frame);

                // Check if it was dirty or not
                if (page_table[deleting_v_frame].mod)
                {
                    OUT(inst, delete_phys_frame, deleting_v_frame);
                }

                // Replace with new inst
                BringInstToRam(inst, delete_phys_frame); 
            }
        }

        int p_frame = page_table[v_index].page_index;
        ACCESS(inst, p_frame); 

        if (option_p)
            PrintPageTable();

        if (option_f)
            PrintFrameTable();
    }

}


void Organizer::PrintResults(){
    if (option_P)
    {
        PrintPageTable();
    }

    if (option_F)
    {
        PrintFrameTable();
    }

    if (option_S)
    {

        int inst_count = current_inst + 1;
        printf("SUM %d U=%d M=%d I=%d O=%d Z=%d ===> %llu\n",
            inst_count, total_unmap, total_map, total_in, total_out, 
            total_zero, total_cycles);
    }
}

void Organizer::PrintFrameTable(){

    for (int i = 0; i < frame_table_size; i++)
    {
        if (frame_table.entries[i] == false)
        {
            cout << "* ";
        }    
        else
        {
            int v_page = FindDeletingVPage(i);
            cout << v_page << " ";
        }
    }

    cout << endl;
}

void Organizer::PrintPageTable(){

    for (int i = 0; i < 64; i++)
    {
        if (page_table[i].present)
        {
            int r,m,s;
            char rc, mc, sc;
            r = page_table[i].ref;
            m = page_table[i].mod;
            s = page_table[i].p_out; 
            
            if (r == 1)
            {
                rc = 'R';
            }
            else
            {
                rc = '-';
            }

            if (m == 1)
            {
                mc = 'M';
            }
            else
            {
                mc = '-';
            }

            if (s == 1)
            {
                sc = 'S';
            }
            else
            {
                sc = '-';
            }
            cout << i << ":" << rc << mc << sc << " ";
        } 
        
        else
        {
            if (page_table[i].p_out)
            {
                cout << "# ";
            }
            else
            {
                cout << "* ";
            }
        }
    }

    cout << endl;
}

void Organizer::BringInstToRam(Instruction inst, int phys_frame_location) {

    // if true IN operation 
    if (page_table[inst.virtual_frame].p_out)
    {
        IN(inst, phys_frame_location);
    }

    // else do a ZERO
    else
    {
        ZERO(inst, phys_frame_location);
    }

    MAP(inst, phys_frame_location);
}

int Organizer::FindDeletingVPage(int phys_frame){
    int return_frame;
    for (int i = 0; i < 64; i++)
    {
        if (page_table[i].present == 1 && page_table[i].page_index == phys_frame)
            return i;
    }
    cout << "Never found entry in Page entry with present and correct phy frame" << endl;
    return -1;
}


Instruction Organizer::GetInstruction() {
    Instruction temp = instructions.back();
    instructions.pop_back();
    return temp;
}

// Remove from Frame Table
void Organizer::UNMAP(Instruction inst, int phys_frame, int prev_v_frame) {

    total_unmap += 1;
    total_cycles += 400;

    // Update Frame Table
    frame_table.entries[phys_frame] = false;

    
    // Update Page Table Present field
    page_table[prev_v_frame].present = false;

    if (option_O)
    {
        cout << current_inst << ": UNMAP   " << prev_v_frame << 
            "   " << phys_frame << endl;
    } 

    replacement_alg->UNMAP_Called(inst, phys_frame, prev_v_frame);
}

void Organizer::MAP(Instruction inst, int phys_frame) {
    total_map += 1;
    total_cycles += 400;

    frame_table.entries[phys_frame] = true; 
    page_table[inst.virtual_frame].present = true;
    page_table[inst.virtual_frame].page_index = phys_frame;

    if (option_O)
    {
        cout << current_inst << ": MAP     " << inst.virtual_frame << 
            "   " << phys_frame << endl;
    } 

    replacement_alg->MAP_Called(inst, phys_frame);
}

void Organizer::IN(Instruction inst, int phys_frame) {
    total_in += 1;
    total_cycles += 3000;

    // This is done on IN and ZERO
    page_table[inst.virtual_frame].ref = 0;
    page_table[inst.virtual_frame].mod = 0;

    if (option_O)
    {
        cout << current_inst << ": IN      " << inst.virtual_frame << 
            "   " << phys_frame << endl;
    } 

    replacement_alg->IN_Called(inst, phys_frame);
}

void Organizer::OUT(Instruction inst, int phys_frame, int prev_v_frame) {
    total_out += 1;
    total_cycles += 3000;

    // Set paged out to true
    page_table[prev_v_frame].p_out = 1;

    if (option_O)
    {
        cout << current_inst << ": OUT     " << prev_v_frame << 
            "   " << phys_frame << endl;
    }

    replacement_alg->OUT_Called(inst, phys_frame, prev_v_frame);
}

void Organizer::ZERO(Instruction inst, int phys_frame) {
    total_zero += 1;
    total_cycles += 150;
    int v_index = inst.virtual_frame;

    // This is done on IN and ZERO
    page_table[v_index].ref = 0;
    page_table[v_index].mod = 0;

    page_table[v_index].present = 0;
    page_table[v_index].p_out = 0;

    if (option_O)
    {
        cout << current_inst << ": ZERO        " << phys_frame << endl;
    }

    replacement_alg->ZERO_Called(inst, phys_frame);
}

void Organizer::ACCESS(Instruction inst, int phys_frame) {
    total_cycles += 1;

    int v_index = inst.virtual_frame;
    if(inst.write)
    {
        page_table[v_index].mod = 1;
    }
    page_table[v_index].ref = 1;

    replacement_alg->ACCESS_Called(inst, phys_frame);
}

/****************
**   Reading  **
*****************/

void Organizer::ReadUntilInstruction() {
    char c;
    char d_me[256];
    int instruct;
    int read_write;

    //ReadUntilCharacter();

    if (PeekEnd())
    {
        // Error
    }

    while(!PeekEnd())
    {
        c = stream.peek();
        if (c == '#')
        {
            //stream.ignore(256, '\n');
            stream.getline(d_me, 256);
            //c = stream.peek();
            //cout << d_me << endl;
            //cout << "Peek: " << c << endl;
            //ReadUntilNewline();
            //ReadUntilCharacter();
        }

        // else if(isdigit(c))
        // {
        //     return;
        // }
        else
            return;
    }
}


int Organizer::ExtractNumber() {
    string number;
    char c;
    char d_me[256];
    ReadUntilCharacter();
    // Check if commented line
    ReadUntilInstruction();
    // If we have readed End of the file Expect Number
    if (PeekEnd())
    {
        //Error
    }

    while (!PeekEnd())
    {
        stream.get(c);
        if (c == '#')
        {

        }
        if ((c != ' ') && (c != '\t') && (c != '\n'))
        {
            if (!isdigit(c))
            {

                cout << "SHOULD BE DIGIT: " << c << endl;
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
