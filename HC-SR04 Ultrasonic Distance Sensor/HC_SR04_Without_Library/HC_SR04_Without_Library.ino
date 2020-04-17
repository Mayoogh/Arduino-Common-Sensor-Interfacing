int TrigPin = 2;    // Trigger Pin to Digital pin 2
int EchoPin = 3;    // Echo Pin to Digital pin 3
long duration, distance_cm, distance_Inch;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  pinMode(EchoPin, INPUT);      //Setting EchoPin as INPUT pin
  pinMode(TrigPin, OUTPUT);     //Setting TrigPin as OUTPUT pin
}
 
void loop() {
  // A LOW pulse is given at first to ensure a clean HIGH pulse:
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(5);
  // The TrigPin is set to HIGH pulse for 10us (microseconds.)
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
 
  // Read the EchoPin
  // PulseIn return the length of pulse in microsecond. 
  duration = pulseIn(EchoPin, HIGH);
 
  // Convert the time into a distance
  distance_cm = (duration/2) / 29.1;     // Divide by 29.1
  distance_Inch = (duration/2) / 74;   // Divide by 74
  
  Serial.print(distance_cm);
  Serial.print("cm ");
//  Uncomment to show distance in Inch  
//  Serial.print(distance_Inch);
//  Serial.print("Inch");
  Serial.println();
  
  delay(100);
}
