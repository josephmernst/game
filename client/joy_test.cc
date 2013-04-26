#include <stdio.h>

#include <SDL/SDL.h>
#include <sstream>
#include <fstream>

#include "joystick/joystick.h"

//jp can be in polar units (r, theta) or rectangular (x, y)

int main(int argc, char** argv){
  cJoystick js;
  joystick_position jp[3];
  
  bool button_check;
  
  while(1){
    button_check=js.buttonPressed(0);
    
    if(button_check){
      jp[0] = js.joystickPosition(0); //left analog stick
      jp[1] = js.joystickPosition(1); //right analog stick
      jp[2] = js.joystickPosition(2); //control pad
      
      printf("%f\t%f\t%f\n", jp[0].theta, jp[1].theta, jp[2].theta);
    }
  }
  
  return 0;
}
