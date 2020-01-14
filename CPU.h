//
// Created by James DellaMorte on 1/13/20.
//

#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

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
#include <algorithm>
using namespace std;


class CPU {
public:
    void initCPU();
    size_t loadROM(const char* filepath);
    void cycle();
private:
    unsigned char hexSprites[0x50]  =
            {
                    0xF0, 0x90, 0x90, 0x90, 0xF0, //0
                    0x20, 0x60, 0x20, 0x20, 0x70, //1
                    0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
                    0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
                    0x90, 0x90, 0xF0, 0x10, 0x10, //4
                    0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
                    0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
                    0xF0, 0x10, 0x20, 0x40, 0x40, //7
                    0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
                    0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
                    0xF0, 0x90, 0xF0, 0x90, 0x90, //A
                    0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
                    0xF0, 0x80, 0x80, 0x80, 0xF0, //C
                    0xE0, 0x90, 0x90, 0x90, 0xE0, //D
                    0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
                    0xF0, 0x80, 0xF0, 0x80, 0x80  //F
            };
    uint8_t V[0x10];
    uint16_t I = 0;
    uint16_t pc = 0;
    uint8_t sp = 0;
    stack <uint16_t> s;
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;
    //MEMORY
    uint8_t memory[0x1000];
    uint8_t key[0xF];
    void CLS(uint16_t op);
    void RET(uint16_t op);
    void JP(uint16_t op);
    void CALL(uint16_t op);
    void SEVX(uint16_t op);
    void SNEVX(uint16_t op);
    void SE(uint16_t op);
    void LDVX(uint16_t op);
    void ADDVX(uint16_t op);
    void SNE(uint16_t op);
    void LD(uint16_t op);
    void OR(uint16_t op);
    void AND(uint16_t op);
    void XOR(uint16_t op);
    void ADD(uint16_t op);
    void SUB(uint16_t op);
    void SHR(uint16_t op);
    void SUBN(uint16_t op);
    void SHL(uint16_t op);
    void LDI(uint16_t op);
    void JPV0(uint16_t op);
    void RND(uint16_t op);
    void SKP(uint16_t op);
    void SKNP(uint16_t op);
    void LDVXDT(uint16_t op);
    void LDKEY(uint16_t op);
    void LDDTVX(uint16_t op);
    void LDSTVX(uint16_t op);
    void ADDI(uint16_t op);
    void LDHEXFT(uint16_t op);
    void LDB(uint16_t op);
    void LDVALL(uint16_t op);
    void LDIALL(uint16_t op);
    typedef void (CPU::*fn)(uint16_t);
    map<uint16_t , fn> fnmap;
    // void (CPU::*fn[0x16])(uint16_t);



};



#endif //CHIP8_CPU_H
