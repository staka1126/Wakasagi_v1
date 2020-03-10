#include "Wksg.h"

//==============================================================================
//
//==============================================================================
void wksg_Dispatcher(){
  //-----------------------------------------------------
  // KEY EVENT
  //-----------------------------------------------------
  for (int i = 0; i < sizeof(sw)/sizeof(SWITCH); i++) {
    switch(sw[i].id){
    case KEY_NULL:
      break;
    case KEY_SPEED:
      wksg_SpeedControllerStateMachine(sw[i].event);
      break;
    case KEY_COUNTER:
      wksg_CounterStateMachine(sw[i].event);
      break;
    case KEY_MOTOR:
      wksg_MotorStateMachine(sw[i].event);
      break;
    case KEY_STOP:
      if (sw[i].event == EVENT_FALLING_EDGE) {
        wksg_MotorStateMachine(EVENT_MOTOR_STOP);
      }
    default:
      break;
    };
    if (sw[i].event != EVENT_NULL) {
      sw[i].event = EVENT_NULL;
      dirty = true;
    }
  }
}
