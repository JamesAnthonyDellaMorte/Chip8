#include <iostream>
#include "CPU.h"
#include <SFML/Window.hpp>
#include <fstream>
#include <thread>
//#include <ncurses.h>
#include <chrono> 
#include <array>
#include <include/SFML/Graphics.hpp>
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
   sf::RenderWindow window(sf::VideoMode(640, 320), "My window");

   // run the program as long as the window is open
   while (window.isOpen())
   {
       cpu.cycle();
       // check all the window's events that were triggered since the last iteration of the loop
       sf::Event event;
       while (window.pollEvent(event))
       {
           // "close requested" event: we close the window
           if (event.type == sf::Event::Closed)
               window.close();
       }

       // clear the window with black color
       if (cpu.drawFlag == true) {
           auto ypoint = 0;
           auto ycounter = 0;
           for (int i = 0; i < sizeof(cpu.screen); i++) {
               auto xpoint = (i % 64);

               if (cpu.screen[i] == 1) {


                   sf::RectangleShape sprite(sf::Vector2f(10, 10));
                   sprite.setPosition(xpoint * 10, ypoint * 10);
                   sprite.setFillColor(sf::Color::White);
                   window.draw(sprite);

               }
               else {
                   sf::RectangleShape sprite(sf::Vector2f(10, 10));
                   sprite.setPosition(xpoint * 10, ypoint * 10);
                   sprite.setFillColor(sf::Color::Black);
                   window.draw(sprite);
               }


               ycounter++;
               if (ycounter == 64) {
                   ypoint += 1;
                   ycounter = 0;
               }

           }
           cpu.drawFlag = false;
           std::this_thread::sleep_for(std::chrono::microseconds(1200));

       }

       // draw everything here...
       // window.draw(...);

       // end the current frame
       window.display();
   }
   
   
      
      
       
      
 


       
       
    return 0;
}