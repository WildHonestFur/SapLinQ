#include "SoftwareSerial.h"
SoftwareSerial serial_connection(10, 11);
#define BUFFER_SIZE 64
char inData[BUFFER_SIZE];
char inChar=-1;
int dat = 0;
int prev = 0;
int i=0;
String humidity = "68";
String temp_humidity = "";
String add = "0";
String temp_add = "";
String crop = "Apple";
String temp_crop = "";
map<string, integer> section;
section["Apple"]=-5;
section["Orange"]=10;
section["Banana"]=0;
section["Rice"]=50;
section["Wheat"]=20;
section["Mango"]=10;
section["Potato"]=-5;
section["Tomato"]=15;
section["Corn"]=-10;
section["Pumpkin"]=10;
section["Coconut"]=-15;
section["Drumstick"]=-20;
section["Coffee"]=30;
section["Tea"]=14;
section["Sugarcane"]=15;
section["Cotton"]=40;
void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A5, INPUT);
  Serial.begin(9600);
  serial_connection.begin(9600);
  serial_connection.println("Ready!!!");
}
String spaces(String str) {
  String word = "";
  for (auto x : temp_humidity)
  {
      if (x == ' ')
      {
          word = "";
      }
      else {
          word = word + x;
      }
  }
  return word;
}
void loop()
{
  if(dat==1) {
    digitalWrite(A0, HIGH);
  }
  else if (dat==0){
    digitalWrite(A0, LOW);
  }
  else if (dat==2){
    if ((1000-analogRead(A5))-add.toInt() < 475-(humidity.toInt()/4)+) {
      serial_connection.println("low");
      Serial.println("low");
    }
    else if ((1000-analogRead(A5))-add.toInt() > 663-(humidity.toInt()/4)) {
      serial_connection.println("high");
      Serial.println("high");
    }
    else {
      serial_connection.println("right");
      Serial.println("right");
    }
    
    dat = prev;
  }
  else if (dat==3){
    humidity = spaces(temp_humidity);
    dat = prev;
  }
  if ((1000-analogRead(A5))-add.toInt() <= ((475+650)/2-50)-(humidity.toInt()/4) && humidity.toInt()<90) {
    digitalWrite(A0, HIGH);
  }
  else if ((1000-analogRead(A5))-add.toInt() > ((650+475)/2-50)-(humidity.toInt()/4) || humidity.toInt()>=90) {
    digitalWrite(A0, LOW);
  }
byte byte_count=serial_connection.available();
  {
    int first_bytes=byte_count;
    int remaining_bytes=0;
    if(first_bytes>=BUFFER_SIZE-1)
    {
      remaining_bytes=byte_count-(BUFFER_SIZE-1);
    }
    for(i=0;i<first_bytes;i++)
    {
      inChar=serial_connection.read();
      inData[i]=inChar;
    }
    inData[i]='\0';
    if(String(inData)=="On")
    {
      dat = 1;
    }
    else if(String(inData)=="Off")
    {
      dat = 0;
    }
    else if(String(inData)=="Send")
    {
      prev = dat;
      dat = 2;
    }
    else if (String(inData).indexOf("humidity") != -1){
      prev = dat;
      temp_humidity = String(inData);
      dat = 3;
    }
    else if (String(inData).indexOf("init") != -1){
      temp_add = String(inData);
      temp_add.remove(0,4);
      add = temp_add;
    }
    else if (String(inData).indexOf("crop") != -1){
      for (auto element :section)
      {
        if (element.first == crop) {
          add = String(add.toInt-element.second)
        }
      }
      temp_add = String(inData);
      temp_crop.remove(0,4);
      crop = temp_crop;
      for (auto element :section)
      {
        if (element.first == crop) {
          add = String(add.toInt+element.second)
        }
      }
   } 
    else {
      add = String(add.toInt()+String(inData).toInt());
    }
    for(i=0;i<remaining_bytes;i++)
    {
      inChar=serial_connection.read();
    }
  }
  delay(100);
}
