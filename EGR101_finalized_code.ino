#include <SoftwareSerial.h>

// ArduinoBlue library: https://sites.google.com/stonybrook.edu/arduinoble/
#include <ArduinoBlue.h>

const int BLUETOOTH_TX_PIN = 8;
const int BLUETOOTH_RX_PIN = 7;

SoftwareSerial bluetooth(BLUETOOTH_TX_PIN, BLUETOOTH_RX_PIN);
ArduinoBlue phone(bluetooth); // pass reference of bluetooth object to ArduinoBlue constructor.

int button;
int buttonState;
int Mode;
const int echoPin1 = 3;
const int trigPin1 = 4;
const int echoPin2 = 5;
const int trigPin2 = 6;
const int speakerPin = 2;
const int switchPin = 9;
long duration1;
long duration2;
int distance1;
int distance2;
bool close = false;
int switchState = 0;

int val = 0;                      // variable for reading the pin status

void setup() {
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 pinMode(speakerPin, OUTPUT);
 pinMode(switchPin, INPUT);
     pinMode(13, OUTPUT);   //left motors forward
    pinMode(12, OUTPUT);   //left motors reverse
    pinMode(11, OUTPUT);   //right  motors reverse
    pinMode(10, OUTPUT);   //right motors forward
    buttonState = phone.getButton();   // read the initial state
    // Start serial monitor at 9600 bps.
    Serial.begin(9600);

    // Start bluetooth serial at 9600 bps.
    bluetooth.begin(9600);

    // delay just in case bluetooth module needs time to "get ready".
    delay(100);
switchState = digitalRead(switchPin);   // read the initial state

}


long microsecondsToInches(long microseconds) {
// According to Parallax's datasheet for the PING))), there are 73.746
// microseconds per inch (i.e. sound travels at 1130 feet per second).
// This gives the distance travelled by the ping, outbound and return,
// so divide by 2 to get the distance of the obstacle.
// See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the object
// take half of the distance travelled.
return microseconds / 29 / 2;
}


void loop() {
      val = digitalRead(switchPin);      // read input value and store it in val


   // Clears the trigPin
 digitalWrite(trigPin1, LOW);
 delayMicroseconds(2);
 // Sets the trigPin on HIGH state for 10 micro seconds
 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin1, LOW);
 // Reads the echoPin, returns the sound wave travel time in microseconds
 duration1 = pulseIn(echoPin1, HIGH);
 // Calculating the distance in cm
 distance1 = duration1 * 0.034 / 2;
 
 //Second ultrasonic sensor:
 digitalWrite(trigPin2, LOW);
 delayMicroseconds(2);

 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10);

 digitalWrite(trigPin2, LOW);
 duration2 = pulseIn(echoPin2, HIGH);

 distance2 = duration2 * 0.034 / 2;

 // Prints the distances on the Serial Monitor
 Serial.print("Distance 1: ");
 Serial.print(distance1);
 Serial.print("cm     Distance 2: ");
 Serial.print(distance2);
 Serial.println("cm");

 delay (100);

//Boolean true if both distances <= 10 cm
 if (val == HIGH){
 if(distance1 <=10 || distance2 <=10){
    close=true;
 } else {
   close=false;
 }

//Speaker sounds if boolean true
 if(close==true){
   digitalWrite(speakerPin, HIGH);
 } else {
   digitalWrite(speakerPin, LOW);
 }
 }
  else {
    digitalWrite(speakerPin, LOW);
  }

  //Motor 4-directional code:
  button = phone.getButton(); // read input value and store it in button
  //Serial.println(button);        
  delay(10);                         
    if (button != buttonState){          // the button state has changed
        if (button == 1){
          if (Mode != 1){// if in Mode 0, switch to Mode 1 when button pressed
          (Mode = 1);}}
        if (button == 2){
          if (Mode != 2){
          (Mode = 2);}}
        if (button == 3){
          if (Mode != 3){
          (Mode = 3);}}
        if (button == 4){
          if (Mode != 4){
          (Mode = 4);}}
        if (button == 5){
          if (Mode != 5){
          (Mode = 5);}}
        }
Serial.println(Mode);
buttonState = button; 

  //Forward  
  if (Mode == 1) {
    digitalWrite(13, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
  }

  //Reverse 
  else if (Mode == 2) {
    digitalWrite(12, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(13, LOW);
    digitalWrite(11, HIGH);
  }

  //Left
  else if (Mode == 3) {
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(13, LOW);
  }

  //Right
  else if (Mode == 4) {
    digitalWrite(13, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(10, LOW);
  }

  //Stop
  else if (Mode == 5) {
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
  }
  delay(100);


// save the new state in our variable
}
