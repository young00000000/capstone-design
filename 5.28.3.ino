#include <SoftwareSerial.h>
#include <Talkie.h>

SoftwareSerial bluetooth1(2, 3);
Talkie voice;

const int switchPin = 4;  // 신호등 스위치 핀
const int ledPin = 5;     // 신호등 LED 핀
const int ampPin = 3;     // 앰프 모듈 핀

bool isBluetoothConnected = false;
bool isLedOn = false;
unsigned long greenLightStartTime;
const unsigned long greenLightDuration = 15000; // 초록불 유지 시간 (밀리초)
int switchPressCount = 0;
bool switchPressed = false;

void setup() {
  Serial.begin(9600);
  bluetooth1.begin(9600);
  pinMode(switchPin, INPUT_PULLUP); // 신호등 스위치 핀을 입력으로 설정
  pinMode(ledPin, OUTPUT);          // 신호등 LED 핀을 출력으로 설정
  pinMode(ampPin, OUTPUT);          // 앰프 모듈 핀을 출력으로 설정

  // Talkie 초기화
  voice.begin();
}

void loop() {
  if (digitalRead(switchPin) == LOW) { // 신호등 스위치가 눌렸을 때
    if (!switchPressed) {
      switchPressed = true;
      switchPressCount++;

      if (switchPressCount % 2 == 1) { // 홀수 횟수로 눌림
        Serial.println("Switch is pressed (Odd count)");
        bluetooth1.begin(9600); // 블루투스 모듈 1 켜기

        if (bluetooth1.connected()) { // 블루투스 모듈 1이 연결되었다면
          Serial.println("Bluetooth module 1 is connected");
          bluetooth1.write("Bluetooth module 1 is connected"); // 지팡이에서는 이 메세지를 받으면 진동 울리기

          if (isLedOn) {
            unsigned long elapsedTime = millis() - greenLightStartTime;
            int remainingTime = (greenLightDuration - elapsedTime) / 1000;
            Serial.print("Remaining Time: ");
            Serial.println(remainingTime);

            if (remainingTime > (greenLightDuration / 1000 - 7)) {
              String message = "Remaining Time: " + String(remainingTime);
              bluetooth1.write(message);
            }

            while (remainingTime > 0) {
              // 앰프 모듈 제어
              digitalWrite(ampPin, HIGH); // 앰프 모듈 활성화
              delay(1000); // 1초 대기
              digitalWrite(ampPin, LOW); // 앰프 모듈 비활성화
              delay(1000); // 1초 대기

              // Talkie로 남은 시간을 음성으로 출력
              voice.sayNumber(remainingTime);
              delay(1000); // 1초 대기

              remainingTime--;
            }
          }
        }
      }
    }
  } else {
    if (switchPressed) {
      switchPressed = false;
    }
  }
}
