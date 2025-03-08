#include <SoftwareSerial.h>

SoftwareSerial bt(10, 11);
extern volatile unsigned long timer0_millis;
const int a = 3;
const int b = A0;
//int count = 200;
//int c2 = 10;
String arr="";
unsigned long past = 0;
int flag = 0;


void setup() {

  pinMode(a, OUTPUT); // 3 pin 은 블루투스 모듈의 RX와 연결되어서 보낼 통로 열기
  pinMode(b, INPUT); // 아날로그 신호 입력 받기 위해 열기
  Serial.begin(9600); // 컴퓨터와 아두이노의 연결, 초당 9600비트의 속도로 데이터 전송
  bt.begin(9600); // 휴대폰과 아두이노의 bt연결, 초당 9600비트의 속도로 데이터 전송
  //bt.println("2");
}

void loop() {
  if(bt.available()>0){
    if(bt.read() == 1){   
      arr = "";
      flag = 0;
      timer0_millis = 0;
    };
  }

  unsigned long now = millis();

  if(flag == 0 && now - past < 7000){
    int val = analogRead(b); //A0 pin에서 데이터 입력 받음 
    
    arr += val;
    
    arr += ",";
    Serial.println(val);
    delay(20); 
  }
  else if(flag == 0 && now - past >= 7000){
    arr += ".";
    flag = 1;
  }else if(flag == 1){
    
    Serial.println(arr);
    bt.println(arr);
    flag = 2;
  }

  
}



