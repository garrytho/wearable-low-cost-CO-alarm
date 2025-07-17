/*
Thomas Garry
*/

const int ledPin = 9;
const int buzzPin = 7;
int gracePeriod = 10; //allows the sensor to output 10 values and warm up before warnings will be thrown
int dangerThreshold = 500; // MQ7 Value of CO considered "dangerous". Will be used to trigger warnings and start the buzzer



void setup() {
  Serial.begin(9600);
  Serial.println("=================== START OF RUNTIME =======================");
  pinMode(ledPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);

  // A simple startup test sequence. Checks that both the buzzer and LED are working
  digitalWrite(ledPin, HIGH);
  for(int i = 0; i<3; i++){
    digitalWrite(buzzPin, HIGH); delay(250);
    digitalWrite(buzzPin, LOW);  delay(250);
  }
  digitalWrite(ledPin, LOW);
}



// a simple function that toggles the LED
void toggleLed(){
  if(digitalRead(ledPin) == HIGH){
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }
}

// a simple function that toggles the Buzzer
void toggleBuzzer(){
  if(digitalRead(buzzPin) == HIGH){
    digitalWrite(buzzPin, LOW);
  } else {
    digitalWrite(buzzPin, HIGH);
  }
}

void loop() {
  if (gracePeriod>0){
  gracePeriod--; // Subtract one from the grace period counter
  }; 

  int CO = analogRead(A1);
  bool dangerBuzz = false;

  // Establish a pulse frequency (amount of delay between pulses. Indicates danger level) based on the MQ7 output
  int wait = 100; // catches anything above 900. Most intense output possible
  if(CO < 900){
    wait = map(CO, 100, 900, 2000, 100); // Scale intensity. Higher values = less delay time = faster blink
  }
  Serial.println("CO: " + String(CO) + " | GRACE PERIOD: " + String(gracePeriod));

  
  // If the sensor has warmed up, Start alerting the user if CO values cross a threshold 
  if(CO > dangerThreshold && gracePeriod == 0){
    dangerBuzz = true;
  }

  // Enable peripherals based on the determined delay time
  toggleLed();
  if(dangerBuzz) {toggleBuzzer();};
  delay(wait);
  toggleLed();
  if(dangerBuzz) {toggleBuzzer();};
  delay(wait);
}


