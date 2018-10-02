#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;

byte left = 3;
byte right = 2;
volatile int pwmValueLeft;
volatile int pwmValueRight;

std_msgs::Int16 msg_CH1;
std_msgs::Int16 msg_CH2;

//ros::Publisher channel1("CH1", &msg_CH1);
//ros::Publisher channel2("CH2", &msg_CH2);

volatile int prev_time_left = 0;
volatile int prev_time_right = 0;

void setup()
{
  Serial.begin(9600);
//  nh.initNode();
//  nh.advertise(channel1);
//  nh.advertise(channel2);
  attachInterrupt(left, risingLeft, RISING);
  attachInterrupt(right, risingRight, RISING);
}

void risingLeft() {
  attachInterrupt(left, fallingLeft, FALLING);
  prev_time_left = micros();
}
void fallingLeft() {
  attachInterrupt(left, risingLeft, RISING);
  pwmValueLeft = micros()-prev_time_left;
}

void risingRight() {
  attachInterrupt(right, fallingRight, FALLING);
  prev_time_right = micros();
}
void fallingRight() {
  attachInterrupt(right, risingRight, RISING);
  pwmValueRight = micros()-prev_time_right;
}

void loop()
{
  
  pwmValueLeft = (pwmValueLeft-964.0)/4.96;
  pwmValueRight = (pwmValueRight-964.0)/4.96;
  msg_CH1.data = pwmValueLeft;
  msg_CH2.data = pwmValueRight;
  Serial.println(pwmValueRight);
//  channel1.publish( &msg_CH1 );
//  channel2.publish( &msg_CH2 );
//  nh.spinOnce();
}
