
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>

ros::NodeHandle nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound_range", &range_msg);
char frameid[] = "/ultrasound";

// this constant won't change. It's the pin number of the sensor's output:
const int trigPin = 10;
const int echoPin = 9;


void setup() {
  // initialize serial communication:
  nh.initNode();
  nh.advertise(pub_range);

  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.1;  // fake
  range_msg.min_range = 0.002;  // 2 cm
  range_msg.max_range = 0.150;  // 150 cm
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  
  //Serial.begin(9600);
}

long getRange(int trigNumber,int echoNumber){

    // establish variables for duration of the ping, and the distance result
      // in inches and centimeters:
      long duration, distance;
    
      // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
      // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(trigPin, LOW);
      duration=pulseIn(echoPin, HIGH);
      distance=(duration/2)/29.1;
      
      Serial.print(distance);
      Serial.println("cm");
      delay(100);
      return distance;

  
}

void loop() {
  range_msg.range=getRange(trigPin,echoPin);
  range_msg.header.stamp = nh.now();
  pub_range.publish(&range_msg);
  nh.spinOnce();
  delay(100);
}
