#include <SPI.h>

#include <SparkFunDS3234RTC.h>
#define cash_in_pin (4)  // The pin on the arduino where CREDIT (+) [Common] is connected
#define cash_out_pin (5) // The pin on the arduino where CREDIT (-) [Common] is connected
#define PWPIN (8) // 5V Power Pin on the arduino
#define DS13074_CS_PIN 10  // SS Pin from RTC

int min_pulse_width; // the minimum pulse width to acccept
int max_pulse_width; // the maximum pulse width to accept
int debounce_speed; // ignore changes in input line state that happen faster than this
int pulse_state_in;
int pulse_state_out;
int post_pulse_pause; // how long to wait after last pulse before sending pulse count


unsigned int dollar_received;
unsigned int dollar_per_pulse;

int pulse_count = 0; // how many pulses have been received so far in this pulse train
int amount_received = 0; // Counts how many cents have been received
unsigned long pulse_duration ; // how long was the last pulse
unsigned long pulse_begin ; // when did the last pulse begin
unsigned long pulse_end ; // if they pulse was within min and max pulse width, when did it end
unsigned long curtime = 0; // what is the current time
unsigned long t=millis();


int pulse_state; // what is the current input line state (1 for high, 0 for low)
int last_state; // what was the last input line state



void setup() {


  //Pulse Decoder
  pinMode(cash_in_pin, INPUT);
  pinMode(cash_out_pin, INPUT);
  pinMode(PWPIN, INPUT);
  Serial.begin(115200);
  pulse_begin = 0;
  last_state = 1;
  min_pulse_width = 48;
  max_pulse_width = 100;
  debounce_speed = 4;
  post_pulse_pause = 1500;
  pulse_end = 0;
  pulse_count = 0;

  dollar_per_pulse = 1;
  dollar_received = 0;
  Serial.println("Starting");
}

void loop() {
  if (digitalRead(PWPIN))
  {
    //delay(5000);
    Serial.println("Enter while");
    while (digitalRead(PWPIN))
    {

      pulse_state_in = digitalRead(cash_in_pin);//read state of cash in pin
      pulse_state_out = digitalRead(cash_out_pin); //read state of cash out pin


      if (pulse_state_in == 0)
      {
        Serial.println("in");
        t=millis();
        while (digitalRead(PWPIN) and millis()-t<5000)
        {
          pulse_state = digitalRead(cash_in_pin);
          //Serial.println(pulse_state);
          curtime = millis();
          if ((pulse_state == 1) && (last_state == 0))
          { // this means we entered a new pulse
            pulse_begin = curtime; // save the begin time of the pulse
            last_state = 1; // set the previous state
            t=millis();
          }
          else if ((pulse_state == 0) && (last_state == 1))
          { // this means a pulse just ended
            pulse_duration = curtime - pulse_begin; // calculate pulse duration
            if (pulse_duration > debounce_speed)

            { // ensure that we don't change state for very short (false) pulses (this is called debouncing)
              last_state = 0;
            }
            if ((pulse_duration > min_pulse_width) && (pulse_duration < max_pulse_width))
            { // check if the pulse width is between the minimum and maximum
              pulse_end = curtime; // save the end time of the pulse
              pulse_count++; // increment the pulse counter
            }
            else if (pulse_duration > max_pulse_width && pulse_count == 0)
            {
              pulse_end = curtime; // save the end time of the pulse
              pulse_count++; // increment the pulse counter
            }
            t=millis();

          }

          if ((pulse_end > 0) && (curtime - pulse_end > post_pulse_pause))// check if we've waited long enough that we don't expect any further pulses to be forthcoming

          { 
            dollar_received += pulse_count * dollar_per_pulse; // count the cents



            //Keyboard.print(out_str); // Write the dollar amount
            Serial.print("Cashed in:$");
            Serial.println(dollar_received);
            dollar_received = 0; // reset cents_received so it's ready for next payment

            pulse_end = 0;
            pulse_count = 0;

            //Serial.println(pulse_state);
            //Serial.println(last_state);
            break;
          }
          


        }

      }

      else if (pulse_state_out == 0)
      {
        Serial.println("out");
        while (digitalRead(PWPIN))
        {
          pulse_state = digitalRead(cash_out_pin);
          curtime = millis();
          if ((pulse_state == 1) && (last_state == 0)) { // this means we entered a new pulse
            pulse_begin = curtime; // save the begin time of the pulse
            last_state = 1; // set the previous state
          } else if ((pulse_state == 0) && (last_state == 1)) { // this means a pulse just ended
            pulse_duration = curtime - pulse_begin; // calculate pulse duration
            if (pulse_duration > debounce_speed) { // ensure that we don't change state for very short (false) pulses (this is called debouncing)
              last_state = 0;
            }
            if ((pulse_duration > min_pulse_width) && (pulse_duration < max_pulse_width)) { // check if the pulse width is between the minimum and maximum
              pulse_end = curtime; // save the end time of the pulse
              pulse_count++; // increment the pulse counter
            }
            else if (pulse_duration > max_pulse_width && pulse_count == 0)
            {
              pulse_end = curtime; // save the end time of the pulse
              pulse_count++; // increment the pulse counter
            }

          }

          if ((pulse_end > 0) && (curtime - pulse_end > post_pulse_pause)) { // check if we've waited long enough that we don't expect any further pulses to be forthcoming

            dollar_received += pulse_count * dollar_per_pulse; // count the cents



            //Keyboard.print(out_str); // Write the dollar amount
            Serial.print("Cashed out:$");
            Serial.println(dollar_received);
            dollar_received = 0; // reset cents_received so it's ready for next payment

            pulse_end = 0;
            pulse_count = 0;

            //Serial.println(pulse_state);
            //Serial.println(last_state);

            break;
          }


        }

      }


    }
  }

}
