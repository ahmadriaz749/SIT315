// C++ code
//
const byte METER_PIN = A4;
const byte LED_PIN = 13;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
      
  Serial.begin(9600);
  
  startTimer(METER_PIN);
}

void loop()
{ 
  
}

void startTimer(double timerFrequency){
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  // led 13 qill blink at every 2 seconds interval 
  timerFrequency = analogRead(METER_PIN);
  //Setting the timer comparison
  OCR1A = timerFrequency;
  // here is Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Output will Compare match a Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);

  TCCR1B |= (1 << WGM12);
  
  
  interrupts();
}

ISR(TIMER1_COMPA_vect){
   digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}

