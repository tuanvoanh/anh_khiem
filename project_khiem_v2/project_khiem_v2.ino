#include "lib.h"
extern  WebSocketsClient webSocket;
SimpleTimer timer;
DynamicJsonBuffer jsonBuffer(200);
JsonObject& vObj = jsonBuffer.createObject();
String a = "";
uint8_t gFunction = 0;
uint8_t gData = 0;
uint8_t gState = 0;
void stateSend(){
  tP(LED);
  a = "";
  vObj["id"] = "esp8266-01";
  vObj["function"] = "func";
  JsonObject& data = jsonBuffer.createObject();
  data["r1"] = gData & 0x01;
  data["r2"] = (gData >> 1) & 0x01;
  data["r3"] = (gData >> 2) & 0x01;
  data["r4"] = (gData >> 3) & 0x01;
  data["r5"] = (gData >> 4) & 0x01;
  vObj["data"] = data;
  vObj.printTo(a);
  Serial.println(a);
  webSocket.sendTXT(a.c_str()); 
   
}

int gtimeCount = 0;
void fCheckWdt(){
  gtimeCount ++;
  if (gtimeCount == timeReset){
    Serial.println("reset");
    ESP.restart();
  }
}
void setup() {
    WiFi.setAutoReconnect(true);
  // put your setup code here, to run once:
    initPort();
    initSystem();
    //init port after bc of using Rx as pinout 
    //initPort();
    // server address, port and URL
    webSocket.begin(SERVER, PORT);
    
   // event handler
    webSocket.onEvent(webSocketEvent);
    //timer.setInterval(1100,updateObj );
    
    //watch dog reset
    ESP.wdtEnable(500);  
    //dem mot phut
    timer.setInterval(60000,fCheckWdt);  

}

void loop() {
  // put your main code here, to run repeatedly:
  webSocket.loop();
  timer.run();
  switch(gState)
  {
    case NORMAL:{      
      if(rP(BTN) == 0){
        gState = UPDATE_FIRMWARE;
      }
      else if(messageRead()){
        gState = SEND_STATE;
      }
      break;
    }
    case SEND_STATE:{
      gState = NORMAL;
      stateSend();
      break;
    }
    case UPDATE_FIRMWARE:{
      gState = NORMAL;
      firmwareUpdate();
      break;
    }
    default:
      Serial.println("error");
  }
  
  
}
void firmwareUpdate(){
    hP(LEDSYS);
    delay(1000);
    //ESP.wdtDisable();
    updateFirmware();  
  }
uint8_t messageRead(){
  
  if(Serial.available()){
    while(Serial.available()){
      gFunction = Serial.read();
      delay(10);
      gData = Serial.read();
      Serial.println(gData,BIN);
      return 1;
    }
  }
  else{
    return 0;
  }
}

