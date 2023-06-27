#include <SoftwareSerial.h>                       // 소프트웨어 시리얼 라이브러리 등록
 
/*------------------------ 아두이노 보드마다 소프트웨어 시리얼로 사용할 수 있는 핀 번호가 다르므로 주의 요망 ---------------------------*/
#define RX 8                                      // 소프트웨어 RX포트로 사용할 핀 번호 정의
#define TX 9  
#define TRIG 2 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO 4 //ECHO 핀 설정 (초음파 받는 핀)                                    // 소프트웨어 TX포트로 사용할 핀 번호 정의
/*------------------------ 아두이노 보드마다 소프트웨어 시리얼로 사용할 수 있는 핀 번호가 다르므로 주의 요망 ---------------------------*/
 
SoftwareSerial Arduino_to_Radar_Serial(RX, TX);   // 소프트웨어 시리얼 객체명 선언(설정 보드의 RX 핀, 설정보드의 TX 핀)
SoftwareSerial BTSerial(0, 1); 
int Radar_Signal_Read_Pin = 7;                    // Radar 모듈 신호선(3번핀)과 아두이노에 연결된 핀번호
 
// 변수
int val = 0;                                      // Read한 Radar 모듈 신호선의 값을 저장할 변수
 
/*------------------------ CLI_Command 종류 ---------------------------*/
// MotionDataEnable 0 : MDR이 측정하고 있는 MotionData를 주기적으로 출력
// MotionDataEnable 1 : MDR이 측정하고 있는 MotionData를 주기적으로 출력
// DetectLevel : 현재 설정되어 있는 DetectLevel 확인
// DetectLevel 11000 : DetectLevel [11000] 설정
// HoldTime : 현재 설정되어 있는 HoldTime 확인
// HoldTime 2000 : HoldTime [2000ms] 설정
/*------------------------ CLI_Command 종류 ---------------------------*/
 
void setup()
{
  // put your setup code here, to run once:
  pinMode(Radar_Signal_Read_Pin, INPUT); // 디지털 7번핀을 GPIO INPUT으로 설정
  pinMode(LED_BUILTIN, OUTPUT); // LED_BUILTIN는 아두이노 보드에 자체적으로 달린 LED이며, 이를 Signal Out핀으로 설정
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
 
  Serial.begin(9600); // Serial 객체는 PC와 Arduino와의 시리얼 통신을 담당하며, Baud Rate = 9600 설정
  BTSerial.begin(38400);
  Arduino_to_Radar_Serial.begin(9600); // Arduino_to_Radar_Serial 객체는 Arduino와 Radar 모듈과의 시리얼 통신을 담당하며, Baud Rate = 9600 설정
}
 
void loop()
{
    if (BTSerial.available())
    Serial.write(BTSerial.read());
  if (Serial.available())
    BTSerial.write(Serial.read());
    long duration, distance;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn (ECHO, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.

  //34000*초음파가 물체로 부터 반사되어 돌아오는시간 /1000000 / 2(왕복값이아니라 편도값이기때문에 나누기2를 해줍니다.)
 //초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식 입니다. 수식이 간단해지도록 적용했습니다.
  distance = duration * 17 / 1000; 
  //PC모니터로 초음파 거리값을 확인 하는 코드 입니다.
  Serial.println(duration ); //초음파가 반사되어 돌아오는 시간을 보여줍니다.
  Serial.print("\nDIstance : ");
  Serial.print(distance); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" Cm");

  delay(100); //1초마다 측정값을 보여줍니다.
  // put your main code here, to run repeatedly:
  val = digitalRead(Radar_Signal_Read_Pin);   // Radar로부터의 움직임 신호를 Read하여 val 변수에 저장
  digitalWrite(LED_BUILTIN, val);  // val 변수의 값에 따른 LED의 High, Low 상태 결정
  
  /*------------------------ 움직임이 있을 경우 수행하고 싶은 코드를 입력하세요 Start ---------------------------*/
  if(val > 0)
  {
    // 움직임이 있을 경우 수행하고 싶은 코드를 입력하세요.
  }
  /*------------------------ 움직임이 있을 경우 수행하고 싶은 코드를 입력하세요 End ---------------------------*/
 
  // 시리얼 모니터 -> 아두이노 -> Radar 모듈
  if(Serial.available())
  {
    // read the incoming byte:
    char Transmit_Char = Serial.read(); // 시리얼 모니터를 통해 전송할 데이터를 1바이트씩 읽고 Transmit_Char 변수에 저장
    Arduino_to_Radar_Serial.write(Transmit_Char); // Transmit_Char 변수에 저장된 1바이트 값을 Radar 모듈로 송신
    Serial.print(Transmit_Char); // 아두이노 사용자가 자신이 전송한 데이터를 알 수 있도록 Transmit_Char 변수에 저장된 1바이트 값을 시리얼 모니터에 표시
  }
 
  // Radar 모듈 -> 아두이노 -> 시리얼 모니터
  if(Arduino_to_Radar_Serial.available())
  {
    // read the incoming byte:
    char Receive_Char = Arduino_to_Radar_Serial.read(); // Radar 모듈이 보낸 데이터를 1바이트씩 읽고 Receive_Char 변수에 저장
    Serial.print(Receive_Char); // Radar 모듈이 보낸 데이터를 아두이노 사용자가 알 수 있도록 Receive_Char 변수에 저장된 1바이트 값을 시리얼 모니터에 표시
  }
}