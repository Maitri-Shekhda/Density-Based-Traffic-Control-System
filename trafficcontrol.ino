#include <TimerOne.h>

#define RR 0
#define GR 1
#define YY 2
#define RG 3

#define RED 0
#define GREEN 1
#define YELLOW 2

#define RELEASE 1
#define BLOCK 0


int signal1[] = {10, 9, 8};  // Signal for lane 1 (direction 1)
int signal2[] = {13, 12, 11};  // Signal for lane 2 (direction 2)
// int redDelay = 200;           // Red light duration
int yellowDelay = 500;        // Yellow light duration

int irSensorPin1 = 3;  // Analog pin for IR sensor in lane 1
int irSensorPin2 = 4;  // Analog pin for IR sensor in lane 2

volatile int T1 = 0;  // IR sensor value for lane 1
volatile int T2 = 0;  // IR sensor value for lane 2



int slanes = 0;

// int threshold = 800;  // IR sensor reading threshold for vehicle detection

void setup() {
  Serial.begin(9600);
  Timer1.initialize(50000);  // Initialize Timer1 for interrupt every 50ms
  Timer1.attachInterrupt(softInterr); // Attach interrupt function to Timer1

  // Set LED pins as OUTPUT
  for (int i = 0; i < 3; i++) {
    pinMode(signal1[i], OUTPUT);
    pinMode(signal2[i], OUTPUT);
  }

  // Set IR sensor pins as INPUT
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);

  setColor(signal1, RED);
  setColor(signal2, RED);
}

void loop() {
  switch(slanes) {
    case RR: {
      if(T1 == BLOCK) {
        setColor(signal1, GREEN);
        setColor(signal2, RED);
        slanes = GR;
      } else if(T2 == BLOCK) {
        setColor(signal1, RED);
        setColor(signal2, GREEN);
        slanes = RG;
      }
      break;
    }
    case GR: { 
      if(T1 == RELEASE) {
        setColor(signal1, YELLOW);
        setColor(signal2, RED);
        slanes = YY;
        delay(yellowDelay);
      }
      break;
    }
    case YY: { 
      setColor(signal1, RED);
      setColor(signal2, RED);
      slanes = RR;
      break;
    }
    case RG: { 
      if(T2 == RELEASE) {
        setColor(signal1, RED);
        setColor(signal2, YELLOW);
        slanes = YY;
        delay(yellowDelay);
      }
      break;
    }
  }
}

void softInterr() {
  // Read IR sensor value for Lane 1
  T1 = digitalRead(irSensorPin1);
  // Read IR sensor value for Lane 2
  T2 = digitalRead(irSensorPin2);
}

void setColor(int signal[], int what) {
  digitalWrite(signal[0], LOW); // RED LED OFF
  digitalWrite(signal[1], LOW); // YELLOW LED OFF
  digitalWrite(signal[2], LOW); // GREEN LED OFF
  switch(what) {
    case RED: {
      digitalWrite(signal[0], HIGH);
      break;
    }
    case YELLOW: {
      digitalWrite(signal[1], HIGH);
      break;
    }
    case GREEN: {
      digitalWrite(signal[2], HIGH);
      break;
    }
  }
}