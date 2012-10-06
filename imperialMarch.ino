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
int noteCount = 22;

void setup() {
  
    // iterate over the notes of the melody:
      int playpin = 11;
  
      for (int thisNote = 0; thisNote < noteCount; thisNote++) {

      // to calculate the note duration, take one second 
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = baseDuration/noteDurations[thisNote];
      tone(playpin, melody[thisNote],noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(playpin);
      
    }
    
    delay(1000);
}

void loop() {
  // no need to repeat the melody.
}
