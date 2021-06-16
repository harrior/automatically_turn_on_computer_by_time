#include <iarduino_RTC.h>

#define RST_PIN 8
#define CLK_PIN 6
#define DAT_PIN 7
#define RELAY_PIN 12
#define PRESS_DURATION 2000
#define DELAY_AFTER_PUSHED 70000
#define DEBUG false

//ON TIME 9:45
const int turn_on_hours = 9;
const int turn_on_minutes = 45;


iarduino_RTC time(RTC_DS1302,RST_PIN, CLK_PIN, DAT_PIN);

void setup() {
  if (DEBUG) Serial.begin(9600);
  
  time.begin();
  //time.settime(00,57,13); //One time for setup current time (settime( SECONDS [, MINUTES [, HOURS [, DAY [, MONTH [, YEAT [, WEEKDAY ]]]]]] );)
  
  pinMode(RELAY_PIN,OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  if (millis()%30000 == 0){
    time.gettime();
    if (DEBUG) Serial.println(time.gettime("H-i-s"));
    if ( (time.Hours == turn_on_hours) and (time.minutes == turn_on_minutes) ){
      if (DEBUG) Serial.println(String(time.Hours) + " " + String(time.minutes)+" BOOM!");
      digitalWrite(RELAY_PIN, HIGH);
      delay(PRESS_DURATION);
      digitalWrite(RELAY_PIN, LOW);
      delay(DELAY_AFTER_PUSHED);

    }
  }

}
