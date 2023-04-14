#include "SoftwareStack.h"

SoftwareStack ss;

int CashInPin = 2;
int CashOutPin = 3;
volatile int CashInPulses = 0;  // counting the pulses
volatile int CashOutPulses = 0; // counting the pulses
int checked1 = false;
int checked2 = false;

void sendData()
{
  String data = String(CashInPulses) + String(';') + String(CashOutPulses);
  Serial.println(data);
}
void count_cashIn_pulses()
{
  int val = digitalRead(CashInPin);
  checked1 = true;
  if (val == HIGH)
  {
    CashInPulses += 1;
  }
}
void count_cashOut_pulses()
{
  int val = digitalRead(CashOutPin);
  checked2 = true;
  if (val == HIGH)
  {
    CashOutPulses += 1;
  }
}

int checkCashInPulse()
{
  if (checked1)
  {
    checked1 = false;
    // Serial.println("CashInPulse Detected!");
    // Serial.print("CashInPulse Count: ");
    // Serial.println(CashInPulses);
    sendData();
    delay(500);
  }
}

int checkCashOutPulse()
{
  if (checked2)
  {
    checked2 = false;
    // Serial.println("CashOutPulse Detected!");
    // Serial.print("CashOutPulse Count: ");
    // Serial.println(CashOutPin);
    sendData();
    delay(500);
  }
}

void setup()
{

  Serial.begin(9600);                                                               // setup the serial port for communications with the host computer
  pinMode(CashInPin, INPUT_PULLUP);                                                 // for making pulses noise-less
  pinMode(CashOutPin, INPUT_PULLUP);                                                // for making pulses noise-less
  attachInterrupt(digitalPinToInterrupt(CashInPin), count_cashIn_pulses, RISING);   // pinNumber 2
  attachInterrupt(digitalPinToInterrupt(CashOutPin), count_cashOut_pulses, RISING); // pinNumber 3
}

void loop()
{

  checkCashInPulse();
  checkCashOutPulse();
}