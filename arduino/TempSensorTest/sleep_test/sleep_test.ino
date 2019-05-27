#include <avr/power.h>
#include <avr/sleep.h>
#include <Adafruit_SleepyDog.h>
#include <util/atomic.h>

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.println("Begin setup");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Setup finished");
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Begin loop");
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.flush();
  doSleep(10000);
  
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

void doSleep(uint32_t time) {
  ADCSRA &= ~(1 << ADEN);
  power_adc_disable();

  while (time > 0) {
    uint16_t slept;
    Serial.flush(); //Flush before sleeping to avoid corrupting serial data
    if (time < 8000) {
      slept = Watchdog.sleep(time);
    } else {
      slept = Watchdog.sleep(8000);
    }


    // Update the millis() and micros() counters, so duty cycle
    // calculations remain correct. This is a hack, fiddling with
    // Arduino's internal variables, which is needed until
    // https://github.com/arduino/Arduino/issues/5087 is fixed.
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      extern volatile unsigned long timer0_millis;
      extern volatile unsigned long timer0_overflow_count;
      timer0_millis += slept;
      // timer0 uses a /64 prescaler and overflows every 256 timer ticks
      timer0_overflow_count += microsecondsToClockCycles((uint32_t)slept * 1000) / (64 * 256);
    }

    if (slept >= time) {
      break;
    }
    time -= slept;
  
  }

  power_adc_enable();
  power_all_enable();
  ADCSRA |= (1 << ADEN);
}

