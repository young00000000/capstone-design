#include <SoftwareSerial.h>
//HC-05 AT MODE
SoftwareSerial BTSerial(9, 10); 
#define GREEN_LED_PIN  5
#define RED_LED_PIN    6
#define SWITCH_PIN     7
#define AMP_PIN 3

int redTime = 3;
int greenTime = 8;

bool green = false; //
bool start = true;
bool redStart = true;
bool blu = false;
bool bluetoothConnected = false;
bool bluetoothOn = false;
int n = 0;
unsigned long running;
unsigned long bluetoothTimming;  //bluetooth module Tx:Digital 2 Rx:Digital 3

void setup() {
    pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
 
  Serial.begin(9600);
  BTSerial.begin(38400);
 
}

void loop() {
  if (BTSerial.available())
    Serial.write(BTSerial.read());
  if (Serial.available())
    BTSerial.write(Serial.read());

    // 1. 초록불 if문
  if (green) {
    digitalWrite(GREEN_LED_PIN,HIGH);
    if (start) {
      running = millis(); // 초록불 켜진지 몇초인지
      start = false;
      n = greenTime - 1;
      Serial.println("green start");
    }
    //Serial.println((millis() - running) / 1000 );

    if (n + 1 == greenTime - (millis() - running) / 1000) {
      Serial.print(n + 1);
      Serial.println("초 남았습니다.");
      n -= 1;
    }
     if (BTSerial.available()){

      if(!blu){ //초록불이 된후 알림을 보낸적이 없다면
          if(greenTime - (millis() - running) / 1000>=greenTime-3){
          BTSerial.write(greenTime - (millis() - running) / 1000); //남은시간 보내줌
          }
          blu= true;
        }
     }
      

    //Serial.println(n+1);

    if ((millis() - running) / 1000 >= greenTime) { // 초록불로 변한지 7초 이상이라면, led off/ green false /start true
      Serial.println("green time");
      green = false;
      start = true;
      digitalWrite(GREEN_LED_PIN, LOW);
      running = 0;
      blu = false;
    }
  }

  // 2. 빨간불 if문
  if (!green) {
    digitalWrite(RED_LED_PIN, HIGH);

    if (redStart) {
      running = millis(); // 현재 시간 확인
      redStart = false;
      Serial.println("red start");
    }
    //Serial.println((millis() - running) / 1000 );
    if ((millis() - running) / 1000 >= redTime) {
      green = true;
      redStart = true;
      running = 0;
      digitalWrite(RED_LED_PIN,LOW);
      Serial.println("red off");
    }
  }

  if (digitalRead(SWITCH_PIN) == HIGH) { // 신호등 스위치가 눌렸을 때

    Serial.println("Switch is pressed");
    bluetooth.begin(38400); // 블루투스 모듈 1 켜기 (=초기화)
    bluetoothOn = true;
  }

  if(bluetoothOn){
    if(!bluetoothConnected){ //처음 연결 된거라면
      if (bluetooth.available()) { // 블루투스 모듈 1이 연결되었다면
        Serial.println("Bluetooth module 1 is connected");
        bluetooth.write("connected"); // 지팡이에서는 이 메세지를 받으면 진동 울리기
        bluetoothConnected = true; //이거는 뒤에 일정 시간이 지나면 false로 바꾸는거 추가해야함!!!!!!!!!!!!!!!!!!!!!!
        bluetoothTimming = millis(); //이거가지고 블투 시간 체크해서 할듯
        }
        if (green) {
            if(!blu) { //초록불이 된후 알림을 보낸적이 없다면
                if(greenTime - (millis() - running) / 1000>=greenTime-3){
                    bluetooth.write(greenTime - (millis() - running) / 1000); //남은시간 보내줌
                }
            blu= true;
        }
      }
        
    }

  }


}