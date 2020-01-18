#include <iostream>
#include "CPU.h"
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <thread>
#include <conio.h>
#include <chrono> 
#include <array>
using namespace std;
void keyboard_check(uint8_t inp[])
{
       char keymap[0x15] = {'1','2','3','4',
                        'q','w','e','r',
                        'a','s','d','f',
                        'z','x','c','v' };
    
        while (1) {
        if (kbhit)
        {
            char pressed_key = getch();
            for(uint8_t i = 0; i < 16; i++)
            {
                if (keymap[i] == pressed_key)
                {
                    inp[i] = i;
                    cout << "It worked" << endl;
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
    }
}
int main()
{
    //TODO make keymap and graphics array
    CPU cpu;
    cpu.initCPU();
   size_t ret = cpu.loadROM("Pong.ch8");

   if (ret == 0) cout << "Did not load ROM" << endl; 

 
       thread t(keyboard_check, cpu.key);
      
       while (1) {
          
        cpu.cycle();
        std::this_thread::sleep_for(std::chrono::seconds(5));
       
       }
       
      
 


       
       
    return 0;
}