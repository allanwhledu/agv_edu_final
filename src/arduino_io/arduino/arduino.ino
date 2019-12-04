
#include <string.h>
#include <Servo.h>    // 声明调用Servo.h库


//ros::NodeHandle  nh;/

Servo myservo;        // 创建一个舵机对象
int pos = 0;          // 变量pos用来存储舵机位置

int sensorPin = A0;    // select the input pin for the potentiometer
int outPin = 8;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

float thresholdVoltageValue = 0.8;

int agv_state = 0;
int goal = 0;
String inString = "0";
String stringDwonToUp = "STATEDTU";
String stringUpToDwon = "STATEUTD";
String stringSucked = "GOAL";
String stringOver = "OVER";
String outString = stringDwonToUp + inString + stringDwonToUp;

//true 1
//false 0
int sucked = 0;
bool serialflag = false;

void set_led(int state) {

}

void setup() {
  pinMode(outPin, OUTPUT);
  analogReference(INTERNAL); //调用板载1.1V基准源
  myservo.attach(5);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  float voltageValue = (1.1 * sensorValue) / 1024;//电压
  if (voltageValue > thresholdVoltageValue) {
    //吸上了
    //digitalWrite(outPin, HIGH);
    //    Serial.print("吸上了\n");
    sucked = 1;
  } else {
    //没有吸上
    //digitalWrite(outPin, LOW);
    //    Serial.print("没有吸上\n");
    sucked = 0;
  }

  if (serialflag) {
    char inChar = '\n';
    while (Serial.available() > 0) {
      inChar = Serial.read();

      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char) inChar;
    }
    sscanf(inString.c_str(), "%*s\nSTATEUTD%dSTATEUTD", &agv_state);
    set_led(agv_state);
  }
  serialflag = !serialflag;

  outString = "";
  outString += stringDwonToUp;
  char temp_str[20];
  //outString += itoa((int)myservo.read() * 10 * 1.0, temp_str, 10);  
  outString += itoa((int) agv_state, temp_str, 10);
  //outString += stringDwonToUp;
  outString += stringSucked;
  outString += itoa((int) goal, temp_str, 10);
  outString += stringOver;
  inString = "";


  Serial.println(outString);
  delay(100);
}