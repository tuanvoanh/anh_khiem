#include "lib.h"
WebSocketsClient webSocket;
// wifi /////////////////////////////////////////////////////
void p(String str){
  String str1 = String(millis()) + ": " + str;
  Serial.println(str1);  
}

int rP(uint8_t a){
  return digitalRead(a);
}

/* s3 */ void hP(uint8_t a){
  digitalWrite(a, LOW);
}
/* s4 */ void lP(uint8_t a){
  digitalWrite(a, HIGH);
}

/* s5 */ void tP(uint8_t a){
  digitalWrite(a, digitalRead(a) ^ 0x01);
}
void beginSmart(){
  WiFi.beginSmartConfig();
  while(1){
           delay(100);
           tP(LED);
           //Kiểm tra kết nối thành công in thông báo
           if(WiFi.smartConfigDone()){
             p("SmartConfig Success");
             break;
           }
       }
       return;
}

int initWifi(){
  int cnt = 0;
  p("Connecting to Wifi");
  WiFi.mode(WIFI_STA);
//  beginSmart();
  //WiFi.begin("CRETA-VNPT", "yoursolutio");
  delay(1000);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    tP(LED);
    Serial.print(".");
    if(cnt++ >= 30){
       beginSmart();
     }
  }
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}
// init System ///////////////


int initSystem(void){
  /*Serial*/
  Serial.begin(BAUDRATE);
  while(!Serial){
  }
  delay(200);
  /*Status Led*/
  pinMode(LED, OUTPUT);
  for(int i = 0; i < 10; i++){
    lP(LED);
    delay(100);
    p("LED -> OK");
  }

  /*Connect to Wifi*/
  initWifi();

  /**/
}
void initPort(){
    pinMode(LED, OUTPUT);
    pinMode(LEDSYS, OUTPUT);
    lP(LEDSYS);
    pinMode(BTN, INPUT);
}
////////////////////////////////////////////////

// websocket CLient ///////////////////////

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  switch(type) {
    case WStype_DISCONNECTED:
      USE_SERIAL.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED: {
      USE_SERIAL.printf("[WSc] Connected to url: %s\n", payload);

      // send message to server when Connected
      webSocket.sendTXT("Connected");
    }
      break;
    case WStype_TEXT:
      USE_SERIAL.printf("[WSc] get text: %s\n", payload);

      // send message to server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      USE_SERIAL.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
  }

}
/////////////////////////////////////////////////////////////////



// http update /////////////////////////
void updateFirmware() {
        t_httpUpdate_return ret = ESPhttpUpdate.update(URL); // Bạn cần thay đúng địa chỉ web chứa fw của bạn
        //Ví dụ
        //t_httpUpdate_return ret = ESPhttpUpdate.update("http://hocarm.org/BasicOTA.ino.bin"); // Bạn cần thay đúng địa chỉ web chứa fw của bạn
        //t_httpUpdate_return  ret = ESPhttpUpdate.update("https://server/file.bin");

        switch(ret) {
            case HTTP_UPDATE_FAILED:
                USE_SERIAL.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                break;

            case HTTP_UPDATE_NO_UPDATES:
                USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
                break;

            case HTTP_UPDATE_OK:
                USE_SERIAL.println("HTTP_UPDATE_OK");
                break;
        }
}
///////////////////////////
