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
 
 #include <EEPROM.h>

#define EN1 6//pin for run the right motor 
#define IN1 7//pin for control right motor direction
#define EN2 5//pin for run the left motor 
#define IN2 4//pin for control left motor direction

#define FORW 1
#define BACK 0
#define BUZZER 11//buzzer io pin
#define Vr   5
 
 void Motor_Control(int M1_DIR,int M1_EN,int M2_DIR,int M2_EN)//control motor
{
  //////////M1////////////////////////
  if(M1_DIR==FORW)//M1 motor direction
    digitalWrite(IN1,FORW);//forward
  else
    digitalWrite(IN1,BACK);//back
  if(M1_EN==0)//M1з”µжњєйЂџеє¦ 
    analogWrite(EN1,LOW);//stop
  else
    analogWrite(EN1,M1_EN);//set speed

  ///////////M2//////////////////////
  if(M2_DIR==FORW)
    digitalWrite(IN2,FORW);
  else
    digitalWrite(IN2,BACK);
  if(M2_EN==0)
    analogWrite(EN2,LOW);
  else
    analogWrite(EN2,M2_EN);
}

 
// structs
// notes in the melody:
int melody[] = {
  NOTE_CS3, NOTE_CS3,NOTE_CS3, NOTE_C3, NOTE_CS4, NOTE_CS3, /*pauses*/0, NOTE_C3, NOTE_CS4 , NOTE_CS3, /*pauses*/0, 
  NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_C5, NOTE_CS4, NOTE_CS3, /*pauses*/0, NOTE_C3, NOTE_CS4 , NOTE_CS3, /*pauses*/0,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  25, 25, 25, 40, 60, 30, /*pauses*/120, 40, 60, 25, /*pauses*/25, 
  25, 25, 25, 40, 60, 30, /*pauses*/120, 40, 60, 25, /*pauses*/25,
 };

int baseDuration = 10000;
const int noteCount = 22;
const int ledsCount = 2;
const int playpin = 11;

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
      unsigned char j;
      for(j=4;j<=7;j++)
    pinMode(j,OUTPUT);
    int turn = 1;
      
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
      
      if(currentNoteDuration == 10000 / 25 && melody[thisNote] != 0)
      {
         if(turn % 2 == 0)
           Motor_Control(FORW,0,FORW,80);
         else
           Motor_Control(FORW,80,FORW,0);
           
           turn++;
      }
       
      // the note's duration + 30% seems to work well:
      int pauseBeforeStopTone = currentNoteDuration * 0.30;
      delay(pauseBeforeStopTone);
      // stop the tone playing:
      noTone(playpin);
      Motor_Control(FORW,0,FORW,0);
    }
}

void loop() {
  // no need to repeat the melody.
}

