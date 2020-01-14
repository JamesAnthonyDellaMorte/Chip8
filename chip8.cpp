#include <iostream>
#include "CPU.h"
#include <fstream>

using namespace std;
int main()
{
    //TODO make keymap and graphics array
    CPU cpu;
    cpu.initCPU();
   size_t ret = cpu.loadROM("Pong.ch8");
   if (ret == 0) cout << "Did not load ROM" << endl; 
   else
       while (1)
       {
           cpu.cycle();
       }
    return 0;
}