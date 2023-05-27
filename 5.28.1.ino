#include <SoftwareSerial.h>

SoftwareSerial bluetooth1(2, 3);

const int switchPin = 4;  // 신호등 스위치 핀
const int ledPin = 5;     // 신호등 LED 핀

bool isBluetoothConnected = false;
bool isLedOn = false;
unsigned long greenLightStartTime;
const unsigned long greenLightDuration = 15000; // 초록불 유지 시간 (밀리초)

void setup() {
  Serial.begin(9600);
  bluetooth1.begin(9600);
  pinMode(switchPin, INPUT_PULLUP); // 신호등 스위치 핀을 입력으로 설정
  pinMode(ledPin, OUTPUT);          // 신호등 LED 핀을 출력으로 설정
}

void loop() {
    
  if (digitalRead(switchPin) == LOW) { // 신호등 스위치가 눌렸을 때
    Serial.println("Switch is pressed");
    bluetooth1.begin(9600); // 블루투스 모듈 1 켜기

    if (bluetooth1.connected()) { // 블루투스 모듈 1이 연결되었다면
      Serial.println("Bluetooth module 1 is connected");
      bluetooth1.write("Bluetooth module 1 is connected"); // 지팡이에서는 이 메세지를 받으면 진동 울리기

      if (isLedOn) {
        unsigned long elapsedTime = millis() - greenLightStartTime;
        if (elapsedTime <= 5000) { // 초록불이 유지되는 동안
          bluetooth1.write(String(5000 - elapsedTime)); // 초록불 남은 시간 전달
        } else {
          // 초록불이 끝나고 빨간불이 되었을 때
          bluetooth1.write("Red light"); // 빨간불임을 전달
        }
      }
    }
  } else { // 신호등 스위치가 눌리지 않았을 때
    if (isBluetoothConnected) { // 연결된 적이 있었다면
      bluetooth1.end(); // 블루투스 모듈 1 끄기
      isBluetoothConnected = false;
    }
  }

  // 신호등 상태 제어
  if (isLedOn) {
    unsigned long elapsedTime = millis() - greenLightStartTime;
    if (elapsedTime >= greenLightDuration) {
      digitalWrite(ledPin, LOW); // 빨간불로 변경
      isLedOn = false;
    }
  } else {
    digitalWrite(ledPin, HIGH); // 초록불로 변경
    isLedOn = true;
    greenLightStartTime = millis();
  }
}
