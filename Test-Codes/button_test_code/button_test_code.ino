
int TARE_BUTTON = 1;
int UNIT_TOGGLE = 2;
int MOT = 38;

# define UNITLED1 4
# define UNITLED2 5

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(UNITLED1, OUTPUT);
  pinMode(UNITLED2, OUTPUT);

  pinMode(TARE_BUTTON, INPUT);
  pinMode(UNIT_TOGGLE, INPUT);
    pinMode(MOT, INPUT);


  Serial.begin(9600);

}

// the loop function runs over and over again forever
void loop() {

  Serial.print("TARE BUTTON = ");
   int buttonState = digitalRead(TARE_BUTTON);
  Serial.println(buttonState);

  Serial.print("UNIT TOGGLE = ");
  int buttonState1 = digitalRead(UNIT_TOGGLE);

  Serial.println(buttonState1);


 Serial.print("MOTOR SWITCH SENSE = ");
  int buttonState3 = digitalRead(MOT);

  Serial.println(buttonState3);


if (buttonState3 == 0)
{
digitalWrite(UNITLED1, buttonState);  // turn the LED on (HIGH is the voltage level)
digitalWrite(UNITLED2, buttonState1);  // turn the LED on (HIGH is the voltage level)
}
  


   else if (buttonState3 == 1)
{
   digitalWrite(UNITLED1, MOT);  // turn the LED on (HIGH is the voltage level)
   digitalWrite(UNITLED2, MOT);  // turn the LED on (HIGH is the voltage level)
}
    
}
