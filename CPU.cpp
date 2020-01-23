//
// Created by James DellaMorte on 1/13/20.
//

#include "CPU.h"
#include <vector>
void CPU::CLS(uint16_t op)
{
    cout << "clear display" << op << endl;
}
void CPU::RET(uint16_t op)
{
    pc = s.top();
    sp--;
}
void CPU::JP(uint16_t op)
{
    pc = op & 0x0FFF;
}
void CPU::CALL(uint16_t op)
{   sp++;
    s.push(pc);
    pc = op & 0x0FFF;

}
void CPU::SEVX(uint16_t op)
{
    if (V[(op & 0x0F00) >> 8] == (op & 0x00FF))
    {
        pc += 4;
    } else{
        pc += 2;
    }

}
void CPU::SNEVX(uint16_t op)
{
    if (V[(op & 0x0F00) >> 8] != (op & 0x00FF))
    {
        pc += 4;
    } else{
        pc += 2;
    }

}
void CPU::SE(uint16_t op)
{
    if (V[(op & 0x0F00) >> 8] == V[(op & 0x00F0 >> 4)])
    {
        pc += 4;
    } else{
        pc += 2;
    }

}
void CPU::LDVX(uint16_t op)
{
    V[(op & 0x0F00) >> 8] = op & 0x00FF;
    pc += 2;
}
void CPU::ADDVX(uint16_t op)
{
    V[(op & 0x0F00) >> 8] = V[(op & 0x0F00) >> 8] + (op & 0x00FF);
    pc += 2;
}

void CPU::SNE(uint16_t op)
{
    if (V[(op & 0x0F00) >> 8] != (op & 0x00F0) >> 4 )
    {
        pc += 4;
    } else{
        pc += 2;
    }

}
void CPU::LD(uint16_t op)
{
    V[(op & 0x0F00) >> 8] = V[(op & 0x00F0) >> 4];
    pc += 2;
}
void CPU::OR(uint16_t op)
{
    V[(op & 0x0F00) >> 8]=  (V[(op & 0x0F00) >> 8] | V[(op & 0x00F0) >> 4]);
    pc += 2;
}
void CPU::AND(uint16_t op)
{
    V[(op & 0x0F00) >> 8]=  (V[(op & 0x0F00) >> 8] & V[(op & 0x00F0) >> 4]);
    pc += 2;
}
void CPU::XOR(uint16_t op)
{
    V[(op & 0x0F00) >> 8]=  (V[(op & 0x0F00) >> 8] ^ V[(op & 0x00F0) >> 4]);
    pc += 2;
}
void CPU::ADD(uint16_t op)
{
    uint16_t sum = V[(op & 0x0F00) >> 8] + V[(op & 0x00F0) >> 4];
    if (sum > 0xFF)
    {
        V[0xF] = 0x1;
        V[(op & 0x0F00) >> 8] = sum & 0x00FF;
    }
    else
    {
        V[0xF] = 0;
        V[(op & 0x0F00) >> 8] = sum;
    }
    pc += 2;
}

void CPU::SUB(uint16_t op)
{
    if(V[(op & 0x0F00) >> 8] > V[(op & 0x00F0) >> 4])
        V[0xF] = 0x1;
    else{
        V[0xF] = 0x0;
    }
    V[(op & 0x0F00) >> 8] = V[(op & 0x0F00) >> 8] - V[(op & 0x00F0) >> 4];
    pc += 2;
}

void CPU::SHR(uint16_t op)
{
    if ((V[(op & 0x0F00) >> 8] & 0x1) == 1)
        V[0xF] = 0x1;
    else
        V[0xF] = 0x0;
    V[(op & 0x0F00) >> 8] = V[(op & 0x0F00) >> 8] >> 1;
    pc += 2;
}
void CPU::SUBN(uint16_t op)
{
    if(V[(op & 0x0F00) >> 8] < V[(op & 0x00F0) >> 4])
        V[0xF] = 0x1;

    else
        V[0xF] = 0x0;


    V[(op & 0x0F00) >> 8] = V[(op & 0x00F0) >> 4] - V[(op & 0x0F00) >> 8];
    pc += 2;
}
void CPU::SHL(uint16_t op)
{
    if(((V[(op & 0x0F00) >> 8]) >> 7) == 1)
        V[0xF] = 0x1;
    else V[0xF] = 0x0;


    V[(op & 0x0F00) >> 8] = V[(op & 0x0F00) >> 8] << 1;
    pc += 2;
}

void CPU::LDI(uint16_t op)
{
    I = op & 0x0FFF;
    pc += 2;
}
void CPU::JPV0(uint16_t op)
{
    pc = op & 0x0FFF + V[0];
}
void CPU::RND(uint16_t op)
{
    uint8_t randNumber = (rand() % 255) + 1;
    V[(op & 0x0F00) >> 8] = (randNumber & (op & 0x00FF));
    pc += 2;

}
void CPU::DRW(uint16_t op)
{
    uint8_t x = V[(op & 0x0F00) >> 8];
    uint8_t y = V[(op & 0x00F0) >> 4];
    uint8_t height = op & 0x000F;
    uint16_t pixel;

    V[0xF] = 0;
    for (int yline = 0; yline < height; yline++)
    {
        pixel = memory[I + yline];
        for (int xline = 0; xline < 8; xline++)
        {
            if ((pixel & (0x80 >> xline)) != 0)
            {
                if (screen[(x + xline + ((y + yline) * 64)) % 0x800] == 1)
                    V[0xF] = 1;
                screen[x + xline + ((y + yline) * 64) % 0x800] ^= 1;
            }
        }
    }
    drawFlag = true;
    pc += 2;
}

void CPU::SKP(uint16_t op)
{
    if (key[V[(op & 0x0F00) >> 8]] != 0)
    {
        pc += 4;
        memset(key, 0, sizeof(key));
    }
    else
    {
        pc += 2;
    }
}
void CPU::SKNP(uint16_t op)
{
    if (key[V[(op & 0x0F00) >> 8]] == 0)
    {
        pc += 4;
        memset(key, 0, sizeof(key));
    }
    else
    {
        pc += 2;
    }
}
void CPU::LDVXDT(uint16_t op)
{
    V[(op & 0x0F00) >> 8] = delay_timer;
    pc += 2;
}
void CPU::LDKEY(uint16_t op)
{
    bool key_pressed = false;
    while(key_pressed == false)
    {
        uint8_t key_val = *max_element(begin(key), end(key));
        if (key_val != 0)
        {
            V[(op & 0x0F00) >> 8] = key_val;
            bool key_pressed = true;
        }


    }
    memset(key, 0, sizeof(key));
    pc += 2;
}


void CPU::LDDTVX(uint16_t op)
{
    delay_timer = V[(op & 0x0F00) >> 8];
    pc += 2;
}
void CPU::LDSTVX(uint16_t op)
{
    sound_timer = V[(op & 0x0F00) >> 8];
    pc += 2;
}
void CPU::ADDI(uint16_t op)
{
    I = V[(op & 0x0F00) >> 8] + I;
    pc += 2;

}
void CPU::LDHEXFT(uint16_t op)
{
    I = ((op & 0x0F00) >> 8) * 0x5;
    pc += 2;
}
void CPU::LDB(uint16_t op)
{
    memory[I] = V[(op & 0x0F00) >> 8] / 100;
    memory[I + 1] = (V[(op & 0x0F00) >> 8] / 10) % 10;
    memory[I + 2] = (V[(op & 0x0F00) >> 8]) % 10;
    pc += 2;


}
void CPU::LDVALL(uint16_t op)
{
    for (int i = 0; i <= ((op & 0x0F00) >> 8); i++)
        memory[I + i] = V[i];

    pc += 2;
}
void CPU::LDIALL(uint16_t op)
{
    for (int i = 0; i <= ((op & 0x0F00) >> 8); i++)
        V[i] = memory[I + i] ;

    pc += 2;
}



void CPU::initCPU()
{
    memset(screen, 0, sizeof(screen));
    memset(V, 0, sizeof(V));
    memset(memory, 0, sizeof(memory));
    memset(key, 0, sizeof(key));
    memcpy(memory, hexSprites, (sizeof(hexSprites[0]) * 0x50 ));
    drawFlag = false;
    s=stack<uint16_t>();
    I = 0;
    pc = 0x200;
    sp = 0;
    delay_timer, sound_timer = 0;
    fnmap[0xE0] = &CPU::CLS;
    fnmap[0xEE] = &CPU::RET;
    fnmap[0x1] = &CPU::JP;
    fnmap[0x2] = &CPU::CALL;
    fnmap[0x3] = &CPU::SEVX;
    fnmap[0x4] = &CPU::SNEVX;
    fnmap[0x5] = &CPU::SE;
    fnmap[0x6] = &CPU::LDVX;
    fnmap[0x7] = &CPU::ADDVX;
    fnmap[0x8000] = &CPU::LD;
    fnmap[0x8001] = &CPU::OR;
    fnmap[0x8002] = &CPU::AND;
    fnmap[0x8003] = &CPU::XOR;
    fnmap[0x8004] = &CPU::ADD;
    fnmap[0x8005] = &CPU::SUB;
    fnmap[0x8006] = &CPU::SHR;
    fnmap[0x8007] = &CPU::SUBN;
    fnmap[0x800E] = &CPU::SHL;
    fnmap[0x9] = &CPU::SNE;
    fnmap[0xA] = &CPU::LDI;
    fnmap[0xB] = &CPU::JPV0;
    fnmap[0xC] = &CPU::RND;
    fnmap[0xD] = &CPU::DRW;
    fnmap[0xE00E] = &CPU::SKP;
    fnmap[0xE001] = &CPU::SKNP;
    fnmap[0xF007] = &CPU::LDVXDT;
    fnmap[0xF00A] = &CPU::LDKEY;
    fnmap[0xF015] = &CPU::LDDTVX;
    fnmap[0xF018] = &CPU::LDSTVX;
    fnmap[0xF01E] = &CPU::ADDI;
    fnmap[0xF029] = &CPU::LDHEXFT;
    fnmap[0xF033] = &CPU::LDB;
    fnmap[0xF055] = &CPU::LDIALL;
    fnmap[0xF065] = &CPU::LDVALL;



}
size_t CPU::loadROM(const char* filepath)
{
    int  i = 0;
    ifstream rom(filepath, ios::ate | ios::binary);
    size_t rom_size = rom.tellg();
    if ((bool)rom == false)
        return 0;
    rom.seekg(0, ios::beg);
    while (!rom.eof()) {
        rom.read(reinterpret_cast<char*> (&memory[i + 0x200]), sizeof(uint8_t));
        i++;
    }
    return rom.tellg();
}

void CPU::cycle()
{


        uint16_t  opcode = memory[pc] << 8 | memory[pc + 1];
        auto a = (opcode)-(opcode & 0x0FF0);
        if (((opcode & 0xF000) >> 12) == 0) {
            (this->*fnmap[opcode])(opcode);
        }
        else if (((opcode & 0xF000) >> 12) == (0x8 | 0xE))
        {
            (this->*fnmap[(opcode)-(opcode & 0x0FF0)])(opcode);
        }
        else if (((opcode & 0xF000) >> 12) == 0xF)
        {
            (this->*fnmap[(opcode)-(opcode & 0x0F00)])(opcode);
        }
        else {
            (this->*fnmap[(opcode & 0xF000) >> 12])(opcode);
            
        }
        
}


