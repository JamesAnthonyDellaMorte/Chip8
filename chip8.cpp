#include <iostream>
#include "CPU.h"
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <thread>
//#include <ncurses.h>
#include <chrono> 
#include <array>
using namespace std;
void keyboard_check(uint8_t inp[]) {
    sf::Keyboard::Key keymap[16] = {sf::Keyboard::Num1, sf::Keyboard::Num2, sf::Keyboard::Num3, sf::Keyboard::Num4,
                                      sf::Keyboard::Q, sf::Keyboard::W, sf::Keyboard::E, sf::Keyboard::R,
                                      sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::F,
                                      sf::Keyboard::Z, sf::Keyboard::X, sf::Keyboard::C, sf::Keyboard::V};

    while (1) {
        for(auto i = 0; i < 16; i++ ) {
            if (sf::Keyboard::isKeyPressed(keymap[i])) {
                inp[i] = i;
            }
        }
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        /*
             char pressed_key = getch();
             for(uint8_t i = 0; i < 16; i++)
             {
                 if (keymap[i] == pressed_key)
                 {
                     inp[i] = i;
                     cout << "It worked" << endl;
                 }
             }
 */

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
        std::this_thread::sleep_for(std::chrono::seconds(25));
       
       }
       
      
 


       
       
    return 0;
}