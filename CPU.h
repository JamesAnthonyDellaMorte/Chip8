/*
* CPU.h
        *
        *  Created on: Dec 29, 2019
*      Author: root
*/
#include <iostream>
#include <cstdint>
#include <string>
#include <stack>
#include <fstream>
#include <map>
using namespace std;


class CPU {
public:
    uint8_t V[0x10];
    uint16_t I = 0;
    uint16_t pc = 0;
    uint8_t sp = 0;
    stack <uint16_t> s;
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;
    //MEMORY
    uint8_t memory[0x1000];
    void CLS(u_int16_t op)
    {
        cout << "clear display" << op << endl;
    }
    void RET(u_int16_t op)
    {
        pc = s.top();
        sp--;
    }
    void JP(u_int16_t op)
    {
        pc = op & 0x0FFF;
    }
    void CALL(u_int16_t op)
    {   sp++;
        s.push(pc);
        pc = op & 0x0FFF;

    }
    void SEVX(u_int16_t op)
    {
        if (V[(op & 0x0F00) >> 8] == (op & 0x00FF))
        {
            pc += 4;
        } else{
            pc += 2;
        }

    }
    void SNEVX(u_int16_t op)
    {
        if (V[(op & 0x0F00) >> 8] != (op & 0x00FF))
        {
            pc += 4;
        } else{
            pc += 2;
        }

    }
    void SE(u_int16_t op)
    {
        if (V[(op & 0x0F00) >> 8] == V[(op & 0x00F0 >> 4)])
        {
            pc += 4;
        } else{
            pc += 2;
        }

    }
    void LDVX(u_int16_t op)
    {
        V[(op & 0x0F00) >> 8] = op & 0x00FF;
        pc += 2;
    }
    void ADDVX(u_int16_t op)
    {
        V[(op & 0x0F00) >> 8] = V[(op & 0x0F00) >> 8] + (op & 0x00FF);
        pc += 2;
    }

    void SNE(u_int16_t op)
    {
        if (V[(op & 0x0F00) >> 8] != (op & 0x00F0) >> 4 )
        {
            pc += 4;
        } else{
            pc += 2;
        }

    }
    void LD(u_int16_t op)
    {
        V[(op & 0x0F00) >> 8] = V[(op & 0x00F0) >> 4];
        pc += 2;
    }
    void OR(u_int16_t op)
    {
        V[(op & 0x0F00) >> 8]=  (V[(op & 0x0F00) >> 8] | V[(op & 0x00F0) >> 4]);
        pc += 2;
    }
    void AND(u_int16_t op)
    {
        V[(op & 0x0F00) >> 8]=  (V[(op & 0x0F00) >> 8] & V[(op & 0x00F0) >> 4]);
        pc += 2;
    }
    void XOR(u_int16_t op)
    {
        V[(op & 0x0F00) >> 8]=  (V[(op & 0x0F00) >> 8] ^ V[(op & 0x00F0) >> 4]);
        pc += 2;
    }
    void ADD(u_int16_t op)
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

    void SUB(u_int16_t op)
    {
        if(V[(op & 0x0F00) >> 8] > V[(op & 0x00F0) >> 4])
            V[0xF] = 0x1;
        else{
            V[0xF] = 0x0;
        }
        V[(op & 0x0F00) >> 8] = V[(op & 0x0F00) >> 8] - V[(op & 0x00F0) >> 4];
        pc += 2;
    }

    void SHR(u_int16_t op)
    {
        if ((V[(op & 0x0F00) >> 8] & 0x1) == 1)
            V[0xF] = 0x1;
        else
            V[0xF] = 0x0;
        V[(op & 0x0F00) >> 8] = V[(op & 0x0F00) >> 8] >> 1;
        pc += 2;
    }
    void SUBN(u_int16_t op)
    {
        if(V[(op & 0x0F00) >> 8] < V[(op & 0x00F0) >> 4])
            V[0xF] = 0x1;

        else
            V[0xF] = 0x0;


        V[(op & 0x0F00) >> 8] = V[(op & 0x00F0) >> 4] - V[(op & 0x0F00) >> 8];
        pc += 2;
    }
    void SHL(u_int16_t op)
    {
        if(((V[(op & 0x0F00) >> 8]) >> 7) == 1)
            V[0xF] = 0x1;
        else V[0xF] = 0x0;


        V[(op & 0x0F00) >> 8] = V[(op & 0x0F00) >> 8] << 1;
        pc += 2;
    }

    void LDI(u_int16_t op)
    {
        I = op & 0x0FFF;
        pc += 2;
    }
    void JPV0(u_int16_t op)
    {
        pc = op & 0x0FFF + V[0];
    }
    void RND(u_int16_t op)
    {
        uint8_t randNumber = (rand() % 255) + 1;
        V[(op & 0x0F00) >> 8] = (randNumber & (op & 0x00FF));
        pc += 2;

    }
    typedef void (CPU::*fn)(u_int16_t);
    map<uint16_t , fn> fnmap;
   // void (CPU::*fn[0x16])(u_int16_t);


    void initCPU()
    {
        memset(V, 0, sizeof(V));
        memset(memory, 0, sizeof(memory));
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


    }
    void loadROM(const char* filepath)
    {
        int  i = 0;
        ifstream rom(filepath, ios::ate | ios::binary);
        size_t rom_size = rom.tellg();
        rom.seekg(0, ios::beg);
        while (!rom.eof()) {
            rom.read(reinterpret_cast<char*> (&memory[i + 0x200]), sizeof(uint8_t));
            i++;
        }
    }

    void cycle(int num)
    {

        while (num != 0) {
            uint16_t  opcode = memory[pc] << 8 | memory[pc + 1];
            auto a = (opcode)-(opcode & 0x0FF0);
            if (((opcode & 0xF000) >> 12) == 0) {
                (this->*fnmap[opcode])(opcode);
            }
            else if (((opcode & 0xF000) >> 12) == 0x8)
            {
                (this->*fnmap[(opcode)-(opcode & 0x0FF0)])(opcode);
            }
            else {
                (this->*fnmap[(opcode & 0xF000) >> 12])(opcode);
                num--;
            }
        }
    }

};
