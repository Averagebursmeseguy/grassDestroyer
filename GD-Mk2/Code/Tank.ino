// defining pins for control signals
#define en1 14
#define rpwm1 13
#define lpwm1 12

#define en2 25
#define rpwm2 27
#define lpwm2 26

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE

#include <BLEDevice.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "RemoteXY"


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t const PROGMEM RemoteXY_CONF_PROGMEM[] =   // 44 bytes V19 
  { 255,3,0,0,0,37,0,19,0,0,0,0,31,1,200,84,1,1,3,0,
  4,15,12,10,51,48,2,26,4,66,6,67,12,128,2,26,4,172,14,10,
  51,48,2,26 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t leftTill; // from -100 to 100
  int8_t throttle; // from 0 to 100
  int8_t rightTill; // from -100 to 100

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


int scale(int inputThrottle, int scaling){  

  // Does a bunch of math to convert the tiller value to positive, scale it to throttle and maps it to 0-255
  return map(abs(ceil(inputThrottle * scaling)/100), 0, 100, 0, 255);
}


void setup() 
{
  RemoteXY_Init ();  // initialization by macros 
  
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);

  digitalWrite(en1, 0x1);
  digitalWrite(en2, 0x1);

  ledcAttach(lpwm1, 20000, 8); //LEDC PWM definition
  ledcAttach(rpwm1, 20000, 8);

  ledcAttach(lpwm2, 20000, 8); //LEDC PWM but other one
  ledcAttach(rpwm2, 20000, 8);
  
}

void loop() 
{ 
  RemoteXYEngine.handler();

// Checks for bluetooth connection, if connected, reads the tiller variables and turns them into PWM for the motors

  if(RemoteXY.connect_flag == 1){
    if(RemoteXY.leftTill < 0){
      ledcWrite(lpwm1, scale(RemoteXY.leftTill, RemoteXY.throttle));
    }

    else if(RemoteXY.leftTill > 0){
      ledcWrite(rpwm1, scale(RemoteXY.leftTill, RemoteXY.throttle));
    }

    else{
      ledcWrite(lpwm1, 0);
      ledcWrite(rpwm1, 0);
    }

    if(RemoteXY.rightTill < 0){
      ledcWrite(rpwm2, scale(RemoteXY.rightTill, RemoteXY.throttle));
    }

    else if(RemoteXY.rightTill > 0){
      ledcWrite(lpwm2, scale(RemoteXY.rightTill, RemoteXY.throttle));
    }

    else{
      ledcWrite(lpwm2, 0);
      ledcWrite(rpwm2, 0);
    }
  }
  else{

      ledcWrite(lpwm1, 0);
      ledcWrite(rpwm1, 0);

      ledcWrite(lpwm2, 0);
      ledcWrite(rpwm2, 0);
  }

}

