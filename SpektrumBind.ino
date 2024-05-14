/*Spektrum Binding Protocol:
 Must send a specified number of falling pulses within 200ms of powering on
 3 Internal DSM2 22ms
 4 External DSM2 22ms
 5 Internal DSM2 11ms
 6 External DSM2 11ms 
 7 Internal DSMx 22ms
 8 External DSMx 22ms
 9 Internal DSMx 11ms (UNIVERSAL INTERNAL)
 10 External DSMx 11ms 
*/

//Pin Assignments
static const uint8_t receiverVcc = 0;
static const uint8_t switchSignal = 9;
static const uint8_t receiverSignal = 10;
static const uint8_t numBindPulses = 9;  //Use Universal


void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(switchSignal, INPUT);   //Switch imput to read when reciever is powered on. Use External 10K Pulldown Resistor
  
  pinMode(receiverVcc, OUTPUT);   //Reciever Power
  pinMode(receiverSignal, OUTPUT);  //Reciever Signal

  Serial.begin(9600);

  digitalWrite(receiverVcc, HIGH);    //Power On
  digitalWrite(receiverSignal, HIGH);   //Allows for falling pulses

  delay(500);

}

void loop() {
  digitalWrite(receiverSignal, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  // Use a physical switch to power on reciever and begin pulses immediately
  while(!digitalRead(switchSignal)){
    delay(10);
  }
  Serial.println("High");
  digitalWrite(receiverSignal, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);   //Ensure reciever powered on before delivering pulses
  
  for(uint8_t pulseCount = 0; pulseCount < numBindPulses; pulseCount++){      //Deliver Falling Pulses
  digitalWrite(receiverSignal, LOW);
  delayMicroseconds(120);
  digitalWrite(receiverSignal, HIGH);
  delayMicroseconds(120);
  }

  Serial.println("Pulses Sent");
  while(digitalRead(switchSignal)){
    //Power on transmitter in bind mode within this delay period
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
  }

}
