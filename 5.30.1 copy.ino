#include <SoftwareSerial.h>

#define GREEN_LED_PIN  5
#define RED_LED_PIN    6
#define SWITCH_PIN     7

//SoftwareSerial bluetooth(10, 11); // 블루투스 모듈 Rx, Tx 핀
int switchPressCount = 0;
bool switchPressed = false;


void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  
  Serial.begin(9600);
  //bluetooth.begin(9600);
  
}

void loop() {
  static unsigned long greenLEDTimer = 0;
  static unsigned long redLEDTimer = 3000;
  static bool greenLEDMessageSent = false; // 초록불 메시지 전송 여부
  //static bool bluetoothConnected = false;

  if (millis() - greenLEDTimer >= 3000) {
    digitalWrite(GREEN_LED_PIN, !digitalRead(GREEN_LED_PIN)); // 초록색 LED 상태 반전
    greenLEDTimer = millis();
    Serial.println("green");

    if (digitalRead(SWITCH_PIN) == LOW) {
      Serial.println("switch2");
      if (!switchPressed) {
        switchPressed = true;
        switchPressCount++;
        if (switchPressCount % 2 == 1) { // 홀수 횟수로 눌림
          Serial.println("Switch is pressed (Odd count)");

        
        
    //     if (!bluetoothConnected) {
    //         bluetooth.begin(9600);
    //         delay(500);
    //         bluetooth.println("Pairing successful!");
    //         bluetoothConnected = true;
    //     }
         if (!greenLEDMessageSent) {
             int remainingTime = (20000 - (millis() - greenLEDTimer)) / 1000; // 초록불이 꺼지기까지 남은 시간 계산
             String message = "Green LED will turn off in " + String(remainingTime) + " seconds.";
             Serial.println(message);
             //bluetooth.println(message);
             //greenLEDMessageSent = true; // 메시지 전송 후 플래그 설정
         }
    }
  }}}
  if (millis() - redLEDTimer >= 3000) {
    digitalWrite(RED_LED_PIN, !digitalRead(RED_LED_PIN)); // 빨간색 LED 상태 반전
    redLEDTimer = millis();
    Serial.println("red");
    if (digitalRead(SWITCH_PIN) == LOW) {
        Serial.println("switch2");
        if (!switchPressed) {
        switchPressed = true;
        switchPressCount++;}
        // if (!bluetoothConnected) {
        //     bluetooth.begin(9600);
        //     delay(500);
        //     bluetooth.println("Pairing successful!");
        //     bluetoothConnected = true;
        // }
    }
  }
}