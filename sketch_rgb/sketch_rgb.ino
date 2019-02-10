/*
SparkFun Inventor's Kit 
Example sketch 03

RGB LED

Make an RGB LED display a rainbow of colors!

Hardware connections:

An RGB LED is actually three LEDs (red, green, and blue) in
one package. When you run them at different brightnesses,
the red, green and blue mix to form new colors.

Starting at the flattened edge of the flange on the LED,
the pins are ordered RED, COMMON, GREEN, BLUE.

Connect RED to a 330 ohm resistor. Connect the other end
of the resistor to Arduino digital pin 9.

Connect COMMON pin to GND.

Connect GREEN to a 330 ohm resistor. Connect the other end
of the resistor to Arduino digital pin 10.

Connect BLUE to a 330 ohm resistor. Connect the other end
of the resistor to Arduino digital pin 11.

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
Visit http://learn.sparkfun.com/products/2 for SIK information.
Visit http://www.arduino.cc to learn about the Arduino.

Version 2.0 6/2012 MDG
*/

int CLK = 2; // CLK Pin to Pin 2 of Arduino, EXT INT
int DIR = 3; // DT Pin to Pin 3 of Arduino
bool DT; // LOW -> CW, HIGH -> CCW
int count = 0;

// First we'll define the pins by name to make the sketch
// easier to follow.

// Here's a new trick: putting the word "const" in front of a
// variable indicates that this is a "constant" value that will
// never change. (You don't have to do this, but if you do, the
// Arduino will give you a friendly warning if you accidentally
// try to change the value, so it's considered good form.)

const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

// This variable controls how fast we loop through the colors.
// (Try changing this to make the fading faster or slower.)

int DISPLAY_TIME = 10;  // In milliseconds


void setup()
{
// Here we'll configure the Arduino pins we're using to
// drive the LED to be outputs:

pinMode(RED_PIN, OUTPUT);
pinMode(GREEN_PIN, OUTPUT);
pinMode(BLUE_PIN, OUTPUT);

pinMode(DIR, INPUT);
attachInterrupt(digitalPinToInterrupt(CLK),CW_Test,FALLING);
}


void loop()
{
  
}
const int increment = 10; 
void CW_Test(){
  
  bool val = digitalRead(DIR);
  if(val == HIGH)
  {
    DT = LOW;
    count = count + increment;
    if(count>767){
      count = 0;      
    }
  }
  else
  {
    DT = HIGH;
    count = count-increment;
    if(count < 0){
      count = 767;
    }
  }
  showRGB(count);
}

// showRGB()

// This function translates a number between 0 and 767 into a
// specific color on the RGB LED. If you have this number count
// through the whole range (0 to 767), the LED will smoothly
// change color through the entire spectrum.

// The "base" numbers are:
// 0   = pure red
// 255 = pure green
// 511 = pure blue
// 767 = pure red (again)

// Numbers between the above colors will create blends. For
// example, 640 is midway between 512 (pure blue) and 767
// (pure red). It will give you a 50/50 mix of blue and red,
// resulting in purple.

// If you count up from 0 to 767 and pass that number to this
// function, the LED will smoothly fade between all the colors.
// (Because it starts and ends on pure red, you can start over
// at 0 without any break in the spectrum).


void showRGB(int color)
{
int redIntensity;
int greenIntensity;
int blueIntensity;

// Here we'll use an "if / else" statement to determine which
// of the three (R,G,B) zones x falls into. Each of these zones
// spans 255 because analogWrite() wants a number from 0 to 255.

// In each of these zones, we'll calculate the brightness
// for each of the red, green, and blue LEDs within the RGB LED.

if (color <= 255)          // zone 1
{
redIntensity = 255 - color;    // red goes from on to off
greenIntensity = color;        // green goes from off to on
blueIntensity = 0;             // blue is always off
}
else if (color <= 511)     // zone 2
{
redIntensity = 0;                     // red is always off
greenIntensity = 255 - (color - 256); // green on to off
blueIntensity = (color - 256);        // blue off to on
}
else // color >= 512       // zone 3
{
redIntensity = (color - 512);         // red off to on
greenIntensity = 0;                   // green is always off
blueIntensity = 255 - (color - 512);  // blue on to off
}

// Now that the brightness values have been set, command the LED
// to those values

analogWrite(RED_PIN, redIntensity);
analogWrite(BLUE_PIN, blueIntensity);
analogWrite(GREEN_PIN, greenIntensity);
}
