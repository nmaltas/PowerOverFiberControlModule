#include <FreqCounter.h>
#include <LiquidCrystal.h>


//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(12, 11, 6, 4, 3, 2);

// VARIABLES SETUP
long int Threshold = 20000;
int SignalPin = 5;
int LEDG = 8;
int LEDR = 9;
int LEDB = 10;
long int Frequency = 0;
float Period = 0;
void setup() {

Serial.begin(9600); 
pinMode(SignalPin, INPUT);
pinMode(LEDG, OUTPUT);
pinMode(LEDR, OUTPUT);
pinMode(LEDB, OUTPUT);
delay(2000);// add to give some time to start the LCD
// set up the LCD's number of columns and rows:
lcd.begin(16, 2); //
lcd.clear();

digitalWrite(LEDG, HIGH);
digitalWrite(LEDR, HIGH);
digitalWrite(LEDB, HIGH);

}
 
void loop() {


FreqCounter::f_comp= 8; 
FreqCounter::start(1000);
while (FreqCounter::f_ready == 0)         // wait until counter ready
 
Frequency = FreqCounter::f_freq;            // read result
Period = (float) Frequency;
Period = (1/Period)*1000000;
lcd.setCursor(0, 0);
lcd.clear();

if (Frequency == 0) {
  lcd.print("No signal");
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDB, HIGH);
}
else if (Frequency <= Threshold){
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDB, HIGH);
  
  lcd.print("Freq: ");
  lcd.print(Frequency);                // print result
  lcd.print(" Hz");
  lcd.setCursor(0, 1);
  lcd.print("Period: ");
  lcd.print(Period, 2);                // print result
  lcd.print(" us");
}
else if (Frequency > Threshold) {
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDB, LOW);
  
  lcd.print("Freq: ");
  lcd.print(Frequency);                // print result
  lcd.print(" Hz");
  lcd.setCursor(0, 1);
  lcd.print("Period: ");
  lcd.print(Period, 2);                // print result
  lcd.print(" us");
}
else {
  lcd.print("Error!");
}

delay(1000);
}
