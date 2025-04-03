
int MOT_LS = 13;         // the PWM pin the LED is attached to
int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by
int MOT = 38;
# define MOT_LDO 9

void setup() {
  pinMode(MOT, INPUT);
  pinMode(MOT_LDO, OUTPUT);
  pinMode(MOT_LS, OUTPUT);

  

  Serial.begin(9600);

}

void loop() {

  
 Serial.print("MOTOR SWITCH SENSE = ");
int buttonState3 = digitalRead(MOT);

Serial.println(buttonState3);



digitalWrite(MOT_LDO, buttonState3);  


analogWrite(MOT_LS, brightness);
brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);  
    
}
