#include "SoftwareStack.h"

SoftwareStack ss;



String data="";
String cb="";
void setup(){
    

    Serial.begin(9600); // setup the serial port for communications with the host computer
    pinMode(13,OUTPUT);
  
}

void loop(){
  if (Serial.available() > 0) {
    data=Serial.readString();
    if(data.indexOf(String("on"))>=1){
      digitalWrite(13,1);
    }
    else{
      digitalWrite(13,0);
    }
  }
  cb=data+String("ArduinoNano");
Serial.println(cb);
}