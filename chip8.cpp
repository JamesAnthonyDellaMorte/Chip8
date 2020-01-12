#include <iostream>
#include "CPU.h"
#include <fstream>
using namespace std;
int main()
{

    CPU cpu;

    cpu.initCPU();
    cpu.loadROM("Pong.ch8");
    cpu.cycle(5);
    return 0;
}