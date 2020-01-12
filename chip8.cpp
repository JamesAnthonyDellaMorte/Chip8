#include <iostream>
#include "CPU.h"
#include <fstream>
using namespace std;
int main()
{
    CPU cpu;
    cpu.initCPU();
   size_t ret = cpu.loadROM("Pong.ch8");
   if (ret == 0) cout << "Did not load ROM" << endl; 
   else
    cpu.cycle(5);
    return 0;
}