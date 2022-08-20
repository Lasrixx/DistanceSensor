#include<LiquidCrystal.h>
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

int trigPin = 5;
int echoPin = 6;
int pingTravelTime;
float pingTravelDistance = 0;
float distanceToTarget;
int measurementAmount = 50;
float totalDistToTarget;
float avgDistToTarget;

int buttonPin = 2;
int oldState = 1;
int newState;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buttonPin,INPUT);
  digitalWrite(buttonPin,HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  newState = digitalRead(buttonPin);
  if(oldState == 1 && newState == 0){
    lcd.clear();
    totalDistToTarget = 0;
    for(int i = 0; i < measurementAmount; i++){
      digitalWrite(trigPin,LOW);
      delayMicroseconds(10);
      digitalWrite(trigPin,HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin,LOW);
      pingTravelTime = pulseIn(echoPin,HIGH);
      delay(25);
      pingTravelDistance = (pingTravelTime *  765. * 2580. * 12.) / (3600. * 1000000.);
      distanceToTarget = (pingTravelDistance / 2) * 2.5;
      totalDistToTarget = totalDistToTarget + distanceToTarget;
    }

    avgDistToTarget = totalDistToTarget / measurementAmount;
    
    //Go Tools>SerialPlotter to get a real time graph up
    lcd.setCursor(0,0);
    lcd.print("Distance:");
    lcd.setCursor(0,1);
    lcd.print(avgDistToTarget);
    lcd.print(" in");
  }
  oldState = newState;
}
