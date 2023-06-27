#include <SoftwareSerial.h>                       // 소프트웨어 시리얼 라이브러리 등록
 
/*------------------------ 아두이노 보드마다 소프트웨어 시리얼로 사용할 수 있는 핀 번호가 다르므로 주의 요망 ---------------------------*/
#define RX 8                                      // 소프트웨어 RX포트로 사용할 핀 번호 정의
#define TX 9                                      // 소프트웨어 TX포트로 사용할 핀 번호 정의
/*------------------------ 아두이노 보드마다 소프트웨어 시리얼로 사용할 수 있는 핀 번호가 다르므로 주의 요망 ---------------------------*/
 
SoftwareSerial Arduino_to_Radar_Serial(RX, TX);   // 소프트웨어 시리얼 객체명 선언(설정 보드의 RX 핀, 설정보드의 TX 핀)
 
int Radar_Signal_Read_Pin = 7;                    // Radar 모듈 신호선(3번핀)과 아두이노에 연결된 핀번호
 
// 변수
int val = 0;  
bool speed = false;                                    // Read한 Radar 모듈 신호선의 값을 저장할 변수

void setup()
{
  // put your setup code here, to run once:
  pinMode(Radar_Signal_Read_Pin, INPUT); // 디지털 7번핀을 GPIO INPUT으로 설정
  pinMode(LED_BUILTIN, OUTPUT); // LED_BUILTIN는 아두이노 보드에 자체적으로 달린 LED이며, 이를 Signal Out핀으로 설정
 
  Serial.begin(9600); // Serial 객체는 PC와 Arduino와의 시리얼 통신을 담당하며, Baud Rate = 9600 설정
  Arduino_to_Radar_Serial.begin(9600); // Arduino_to_Radar_Serial 객체는 Arduino와 Radar 모듈과의 시리얼 통신을 담당하며, Baud Rate = 9600 설정
}
 
void loop()
{
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


  // put your main code here, to run repeatedly:
  val = digitalRead(Radar_Signal_Read_Pin);   // Radar로부터의 움직임 신호를 Read하여 val 변수에 저장
  digitalWrite(LED_BUILTIN, val);  // val 변수의 값에 따른 LED의 High, Low 상태 결정
 //움직임이 없다면
 speed=false;

 for(i=0;i<100;i++){
  if(val){//움직임이 생기면 반복적으로 확인하는 작업에서 빠져나옴
    i=100
  }
  if(i=99){
    speed=true;
  }
 }
//반복적으로 속도가 0이라는것이 참일때
  if(speed){
    bool accross = false;
    // 차량이 있는지 없는지 확인
    if(distance>20){//초음파 확인, 20이라는 숫자는 그냥 임의로 설정한거
      bluetooth1.write("건너라는 메세지보내기")
    }else{ // 차량이 없다면
      for(i=0;i<100;i++){
        if(val){//움직임이 생기면 반복적으로 확인하는 작업에서 빠져나옴
        i=100
        }
        //
        if(i=99){
          accross=true;
        }
      }
      if(accross){
        bluetooth1.write("건너라는 메세지보내기")
      }
          
    }
  }



 
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