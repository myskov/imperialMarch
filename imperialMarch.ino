/*
  Melody
 
 Plays a melody 
 
 circuit:
 * 8-ohm speaker on digital pin 8
 
 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe 

This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone
 
 */
 #include "pitches.h"
 
 
// structs
// notes in the melody:
int melody[] = {
  NOTE_CS3, NOTE_CS3,NOTE_CS3, NOTE_C3, NOTE_CS4, NOTE_CS3, /*pauses*/0, NOTE_C3, NOTE_CS4 , NOTE_CS3, /*pauses*/0,
  NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_C5, NOTE_CS4, NOTE_CS3, /*pauses*/0, NOTE_C3, NOTE_CS4 , NOTE_CS3, /*pauses*/0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  25, 25, 25, 40, 60, 30, /*pauses*/120, 40, 60, 25, /*pauses*/25,
  25, 25, 25, 40, 60, 30, /*pauses*/120, 40, 60, 25, /*pauses*/25
 };

int baseDuration = 10000;
const int noteCount = 22;
const int ledsCount = 2;

int leds[] = {
  12, 13
};

int ledAccomponement[][noteCount] = {
  /*red*/   { LOW , LOW , LOW , HIGH, LOW , HIGH, LOW, HIGH, LOW , HIGH, LOW,
              LOW , LOW , LOW , HIGH, LOW , HIGH, LOW, HIGH, LOW , HIGH, LOW },
  /*green*/ { HIGH, HIGH, HIGH, LOW,  HIGH, LOW,  LOW, LOW , HIGH, LOW , LOW,
              HIGH, HIGH, HIGH, LOW,  HIGH, LOW,  LOW, LOW , HIGH, LOW , LOW }
};


// definitions
int noteDuration(int noteNumber) {
  return baseDuration/noteDurations[noteNumber];
}

void disableLeds() {
  for(int pinNumber = 0; pinNumber < ledsCount; ++pinNumber) {
    int pin = leds[pinNumber];
    digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  }
}

void flashLeds(int noteNumber) {
  for(int pinNumber = 0; pinNumber < ledsCount; ++pinNumber) {
    int pin = leds[pinNumber];
    int signal = ledAccomponement[pinNumber][noteNumber];
    
    digitalWrite(pin, signal);    // turn the LED off by making the voltage LOW
  }
}


// ======================================================
// main code
// ======================================================
void setup() {
      // iterate over the notes of the melody:  
      for (int thisNote = 0; thisNote < noteCount; thisNote++) {

      // to calculate the note duration, take one second 
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int currentNoteDuration = noteDuration(thisNote);
      
      // flash by led in accomponement to music
      flashLeds(thisNote);
      // play tone note for music
      tone(playpin, melody[thisNote], currentNoteDuration);

      // to distinguish the notes, set a minimum time between them.
      int pauseBeforeStopLed  = currentNoteDuration /* * 1.00*/;
      delay(pauseBeforeStopLed);
      // stop all leds
      disableLeds();
      
      // the note's duration + 30% seems to work well:
      int pauseBeforeStopTone = currentNoteDuration * 0.30;
      delay(pauseBeforeStopTone);
      // stop the tone playing:
      noTone(playpin);
    }
}

void loop() {
  // no need to repeat the melody.
}

