#include <AddicoreRFID.h>
#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(3, 2); //블루투스 모듈 HC-06 모듈 핀 설정 (TX, RX)

AddicoreRFID myRFID; // create AddicoreRFID object to control the RFID module

#define NUM 10 //상수 num의 값을 10으로 지정해서 배열의 크기를 10으로 설정
#define NUM2 10//상수 num2의 값을 10으로 지정해서 배열의 크기를 10으로 설정
#define NUM3 10//상수 num3의 값을 10으로 지정해서 배열의 크기를 10으로 설정
#define NUM4 10//상수 num4의 값을 10으로 지정해서 배열의 크기를 10으로 설정

long key[NUM] = {13486}; //회원1 카드 시리얼 넘버

long key2[NUM2] = {14162}; //회원2 카드 시리얼 넘버

long key3[NUM3] = {5212}; //회원3 카드 시리얼 넘버(양준혁 카드키)

long key4[NUM4] = {14774};

//set the pins
#define PIN_chipSelectPin 10
#define PIN_NRSTPD 9


//Maximum length of the array
#define MAX_LEN 16

int speakerpin = 8; //스피커가 연결된 디지털핀 설정

void setup() {               
  Serial.begin(9600); //pc와 연결
  
  // spi라이브러리를 시작합니다.
  SPI.begin();

  

  BTSerial.begin(9600);//블루투스 연결
   
  pinMode(PIN_chipSelectPin,OUTPUT);            // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin
  digitalWrite(PIN_chipSelectPin, LOW);         // Activate the RFID reader
  pinMode(PIN_NRSTPD,OUTPUT);                   // Set digital pin 10 , Not Reset and Power-down
  digitalWrite(PIN_NRSTPD, HIGH);
  
  myRFID.AddicoreRFID_Init(); 
}
 
void loop() {
  
  //delay(500);
  
  unsigned char status;
  unsigned char str[MAX_LEN];

  unsigned int i;
  
  //Find tags, return tag type
  status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);

  //Anti-collision, return tag serial number 4 bytes
  status = myRFID.AddicoreRFID_Anticoll(str);
  if (status == MI_OK)
  {
    long num = str[0] * str[1] + str[2] * str[3] + str[4]; // nfc의 고유값을 하나로 정리해주는 코드
    bool enabled = false;
    //이 밑으로는 카드 시리얼 넘버를 출력해줌
    Serial.print("tagnum  : ");
    
    //Serial.print(2);
    Serial.print(str[0]);
    Serial.print(" , ");
    Serial.print(str[1]);
    Serial.print(" , ");
    Serial.print(str[2]);
    Serial.print(" , ");
    Serial.print(str[3]);
    Serial.print(" , ");
    Serial.print(str[4]);
    Serial.print(" , ");
    Serial.print(str[5]);
    Serial.print(" , ");
    Serial.print(str[6]);
    Serial.print(" , ");
    Serial.print(str[7]);
    Serial.print(" , ");
    Serial.print(str[8]);
    Serial.print(" , ");
    Serial.print(str[9]);
    Serial.print(" , ");
    Serial.println(num);
     
    // nfc 값 전송
//회원 1의 카드
    for(i=0;i<NUM;i++) { //nfc값 비교
      if(num == key[i]){  //nfc값이 설정한 값과 같다면 안드로이드로 10을 블루투스로 전달
        //BTSerial.println(10);
        BTSerial.println(20);
        tone(speakerpin,800,50);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)  
        delay(1000);
      }
    }
//회원 2의 카드

    //아두이노 마다 다르게 값을 보냄
    for(i=0;i<NUM2;i++) { //nfc값 비교
      if(num == key2[i]){  //nfc값이 설정한 값과 같다면 안드로이드로 20을 블루투스로 전달
        //BTSerial.println(10);
        BTSerial.println(20);
        tone(speakerpin,800,50);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
        delay(1000);
      }
    }

//회원 3의 카드
      for(i=0;i<NUM3;i++) { //nfc값 비교
        if(num == key3[i]) { //nfc값이 설정한 값과 같다면 안드로이드로 20을 블루투스로 전달
          //BTSerial.println(10);
          BTSerial.println(20);
          tone(speakerpin,800,50);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
          delay(1000);
        }
      }
      
//회원 4의 카드
      for(i=0;i<NUM4;i++) { //nfc값 비교
        if(num == key4[i]) { //nfc값이 설정한 값과 같다면 안드로이드로 20을 블루투스로 전달
          //BTSerial.println(10);
          BTSerial.println(20);
          tone(speakerpin,800,50);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
          delay(1000);
        }
      }
    
    
  }
  myRFID.AddicoreRFID_Halt();        //Command tag into hibernation             
 
}
