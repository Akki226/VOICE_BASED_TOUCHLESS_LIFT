#include "VoiceRecognitionV3.h"

#include <Servo.h>
Servo door; 
 

 


VR myVR(10,11);   
 
uint8_t records[7]; 
uint8_t buf[64];
int led=0;
int i=0;
int motorPin1 = 2; 
int motorPin2 = 3; 
int motorPin3 = 4; 
int motorPin4 = 5;




 
 
 
#define zero    (0)
#define one  (1) 
#define two (2)
#define on (3)
 
#define three (4)
 

void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}
 

void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");
 
  Serial.print(buf[2], DEC);
  Serial.print("\t\t");
 
  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");
 
  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}
 
void setup()
{
  pinMode(motorPin1, OUTPUT); 
  pinMode(motorPin2, OUTPUT); 
  pinMode(motorPin3, OUTPUT); 
  pinMode(motorPin4, OUTPUT); 
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  int delayTime = 50;
  myVR.begin(9600);
  
  
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");
  
  pinMode(led, OUTPUT);
  door.attach(9);
 
 
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)zero) >= 0){
    Serial.println("ground");
 
  }
  
  if(myVR.load((uint8_t)one) >= 0){
    Serial.println("first");
 
  }
 
    if(myVR.load((uint8_t)two) >= 0){
    Serial.println("second");
 
  }
 
      if(myVR.load((uint8_t)on) >= 0){
    Serial.println("on");
 
  }
 
        if(myVR.load((uint8_t)three) >= 0){
    Serial.println("third");
 
  }
}
void show(int num, boolean dp)
{
  digitalWrite(39, !dp);
  if(num == 0)
  {
    digitalWrite(32, 0);
    digitalWrite(33, 0);
    digitalWrite(34, 0);
    digitalWrite(35, 0);
    digitalWrite(36, 0);
    digitalWrite(37, 0);
    digitalWrite(38, 1);
  } else if(num == 1) {
    digitalWrite(32, 1);
    digitalWrite(33, 0);
    digitalWrite(34, 0);
    digitalWrite(35, 1);
    digitalWrite(36, 1);
    digitalWrite(37, 1);
    digitalWrite(38, 1);
  } else if(num == 2) {
    digitalWrite(32, 0);
    digitalWrite(33, 0);
    digitalWrite(34, 1);
    digitalWrite(35, 0);
    digitalWrite(36, 0);
    digitalWrite(37, 1);
    digitalWrite(38, 0);
  } else if(num == 3) {
    digitalWrite(32, 0);
    digitalWrite(33, 0);
    digitalWrite(34, 0);
    digitalWrite(35, 0);
    digitalWrite(36, 1);
    digitalWrite(37, 1);
    digitalWrite(38, 0);
  } else if(num == 4) {
    digitalWrite(32, 1);
    digitalWrite(33, 0);
    digitalWrite(34, 0);
    digitalWrite(35, 1);
    digitalWrite(36, 1);
    digitalWrite(37, 0);
    digitalWrite(38, 0);
  } 
}
 
void loop()
{
  int ret;
  ret = myVR.recognize(buf, 50);
 
  if(ret>0){
    if(buf[1]==zero)
    {
      if(i>0){
      while(i>0){
      
      i--;
      down();
    
    show(i,true); 
    
    }
    }
    i=0;       
   show(i,true); 
    Serial.print("You are on the ");
        Serial.print(i);
        Serial.println("floor");
    delay(1000);
    Door();
      
    }
    if(buf[1]==one)
    {
      if(i>1){
      while(i>1)
      {
       i--;
       down();
       
       show(i,true); 
      }  
    i=1;   
    }
      if(i<1){
      while(i<1){
        i++;
        up();
    
  show(i,true); 
  
      }
      i=1;
        
   show(i,true); 
      delay(1000);
    }
      Serial.print("You are on the ");
        Serial.print(i);
        Serial.println("floor");
      Door();
      Serial.println("first");
    }
    if( buf[1]==two)
    {
      if(i>2){
      while(i>2) {
      i--;
      down();
   
   show(i,true); 
      }
    }
    if(i<2){ 
      while(i<2){
        i++;
        up();
      
    show(i,true); 
    }
    }
      i=2; 
      Serial.print("You are on the ");
        Serial.print(i);
        Serial.println("floor");
   show(i,true); 
      delay(1000);
      Door();
      Serial.println("second");
    }
    
    if( buf[1]==on)
    {
      Serial.println("ground");
    }
    if( buf[1]==three)
    {
      while(i<3){   
        i++;
        up();
        
   show(i,true); 
      }
      Serial.print("You are on the ");
        Serial.print(i);
        Serial.println("floor");
      
     i=3;
 show(i,true); 
     Door();
      Serial.println("third");
    }
    
    printVR(buf);
  }
}
void down() { 

  for(int j=0;j<=512;j++){
  for(int b=0; b<8; b++){
  
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(3);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(3);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(3);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);  
  delay(3);
  }
  }
}
void up() { 
 
 for(int j=0;j<=512;j++){
 for(int a=0;a<8;a++){
 digitalWrite(motorPin1, HIGH); 
 digitalWrite(motorPin2, LOW); 
 digitalWrite(motorPin3, LOW); 
 digitalWrite(motorPin4, LOW); 
 delay(3);
 digitalWrite(motorPin1, LOW); 
 digitalWrite(motorPin2, HIGH); 
 digitalWrite(motorPin3, LOW); 
 digitalWrite(motorPin4, LOW); 
 delay(3);
 digitalWrite(motorPin1, LOW); 
 digitalWrite(motorPin2, LOW); 
 digitalWrite(motorPin3, HIGH); 
 digitalWrite(motorPin4, LOW); 
 delay(3);
 digitalWrite(motorPin1, LOW); 
 digitalWrite(motorPin2, LOW); 
 digitalWrite(motorPin3, LOW); 
 digitalWrite(motorPin4, HIGH); 
 delay(3);
 
 }
 }
}
void Door()
{
door.write(0); delay(2000); 
door.write(90); delay(2000); 
}
