#include <ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

std_msgs::Float64 Sensor1;
std_msgs::Float64 Sensor2;
std_msgs::String str_msg;

ros::Publisher sensor1("sensor1", &Sensor1);
ros::Publisher sensor2("sensor2", &Sensor2);

ros::Publisher height("height", &str_msg);

char child[13] = "child";
char adult[13] = "adult";

const int trigPin[2] = {50,58};
const int echoPin[2] = {51,59};

long duration[2]={0,0};
float distance[2]={0,0};

float Distance_sensing(int i) {
  
  digitalWrite(trigPin[i], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin[i], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin[i], LOW);
  duration[i] = pulseIn(echoPin[i], HIGH);
  return duration[i] * 0.034 / 2;

}

void setup() {
  nh.initNode();
  nh.advertise(sensor1);
  nh.advertise(sensor2);
  nh.advertise(height);
  pinMode(trigPin[0], OUTPUT);
  pinMode(echoPin[0], INPUT);
  pinMode(trigPin[1], OUTPUT);
  pinMode(echoPin[1], INPUT);
  Serial.begin(57600);
}

void loop() {

  Sensor1.data = Distance_sensing(0);
  Sensor2.data = Distance_sensing(1);

  if (Sensor2.data<20){
    str_msg.data = adult;
    height.publish( &str_msg );
  }
  else if(Sensor1.data<20){
    str_msg.data = child;
    height.publish( &str_msg );
  }

  sensor1.publish(&Sensor1);
  sensor2.publish(&Sensor2); 
  
  nh.spinOnce(); 
  delay(100);
}
