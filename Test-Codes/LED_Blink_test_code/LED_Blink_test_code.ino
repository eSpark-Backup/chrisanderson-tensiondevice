

# define UNITLED1 4
# define UNITLED2 5

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(UNITLED1, OUTPUT);
  pinMode(UNITLED2, OUTPUT);



}

// the loop function runs over and over again forever
void loop() {




  digitalWrite(UNITLED1, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100); 

  digitalWrite(UNITLED1, LOW);   // turn the LED off by making the voltage LOW
  delay(100);

  digitalWrite(UNITLED2, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);
  digitalWrite(UNITLED2, LOW);   // turn the LED off by making the voltage LOW
  delay(100); 
}
