
#include <math.h>
long time = millis();

#define LOW_PRESSURE_LOX A0
#define LOW_PRESSURE_PROP A2
#define LOW_PRESSURE_INJECTOR A4

#define HIGH_PRESSURE_PROP A6
#define HIGH_PRESSURE_LOX A7

int input = 0;
void setup() {
  // put your setup code here, to run once:

  pinMode(LOW_PRESSURE_LOX, INPUT);
  pinMode(LOW_PRESSURE_PROP, INPUT);
  pinMode(LOW_PRESSURE_INJECTOR, INPUT);
  pinMode(HIGH_PRESSURE_PROP, INPUT);
  pinMode(HIGH_PRESSURE_LOX, INPUT);

  Serial.begin(9600);
}

// 0.88V - 4.4V : ?? - 5000 PSI

int lowpressurelox, lowpressureprop, highpressurelox, highpressureprop, lowpressureinjector;
int converted_lox_low, converted_prop_low, converted_high_lox, converted_high_prop, converted_inject_low;

int periodic = 50;
void loop() {
  // put your main code here, to run repeatedly:
  lowpressurelox = analogRead(LOW_PRESSURE_LOX);
  lowpressureprop = analogRead(LOW_PRESSURE_PROP);
  lowpressureinjector = analogRead(LOW_PRESSURE_INJECTOR);
  highpressurelox = analogRead(HIGH_PRESSURE_LOX);
  highpressureprop = analogRead(HIGH_PRESSURE_PROP);
  

  converted_lox_low = lowPressureConversion(lowpressurelox);
  converted_prop_low = lowPressureConversion(lowpressureprop);
  converted_inject_low = lowPressureConversion(lowpressureinjector);

  converted_high_prop = highPressureConversion(highpressureprop);
  converted_high_lox = highPressureConversion(highpressurelox);

  char buffer[25];
 
  time = millis();
  if((time%int(periodic)) == 0){
//  sprintf(buffer, "%d,%d,%d,%d,%d", lowpressurelox, lowpressureprop, highpressurelox, highpressureprop, lowpressureinjector);
//  sprintf(buffer, "%d,%d,%d,%d,%d", converted_lox_low, converted_prop_low, converted_high_lox, converted_high_prop, converted_inject_low);
    //String toWriteRaw = String(lowpressurelox)+','+String(lowpressureprop)+','+String(lowpressureinjector)+','+String(highpressurelox)+','+String(highpressureprop);
    String toWrite = String(converted_lox_low)+','+String(converted_prop_low)+','+String(converted_inject_low)+','+String(converted_high_lox)+','+String(converted_high_prop);
    Serial.println(toWrite);
  }
}

int _lowPressureConversion(int raw){
  return (raw - 123);
}

int _highPressureConversion(int raw){
  return (6*raw - 1237);
}

float lowPressureConversion(int raw){
  return int(1.2258857538273733*raw - 123.89876445934394);
}

float highPressureConversion(int raw){
  return (6.612739309669555*raw - 1237.7612969223858);
}
