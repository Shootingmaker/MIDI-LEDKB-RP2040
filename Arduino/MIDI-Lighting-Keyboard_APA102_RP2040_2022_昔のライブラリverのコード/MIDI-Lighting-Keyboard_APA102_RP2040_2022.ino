/* -----------------------------------------------------------------------------
[MIDI Lighting Keyboard Project.]
Kotohiro Masdua. 
2019/02/14  first release 
2022/06/11  add RP2040 Support
-----------------------------------------------------------------------------*/
/*
[Library needs]
FastLED-rp2040 (based on Ver 3.4)
https://github.com/somewhatlurker/FastLED/tree/rp2040

tttapa/Control-Surface
https://github.com/tttapa/Control-Surface

 [Setting] 
 Board Raspberry Pi Pico Arduino >> [[Seedstudio XIAO RP2040]]
 2MB no FS 
 CPU:133Mhz
 stack:Tiny USB

[Wireing to LED(APA102)]
 5V    Almost needs 1000mA with Capacitor 100uF is Better.
 GND   Wide line.
 MOSI is  D3
 CLK  is  D2

-----------------------------------------------------------------------------*/

#include <Control_Surface.h>
// Instantiate a MIDI Interface to use
USBMIDI_Interface midi;
// -----------------------------------------------------------------------------
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 88
CRGB leds[NUM_LEDS];
#define DATA_PIN D3
#define CLOCK_PIN D2

// Define the array of leds
CRGB leds[NUM_LEDS];

int delayval = 2; // delay for test
int FastLEDSet_Ch[88];          // Map of Who(channel) use LED?

// Create a MIDI input element that listens to all notes in the range C4 - G4
// (the range starts at C4 and has a length equal to `leds.length` == 8).
NoteRangeFastLED<NUM_LEDS> midiled {leds, MIDI_Notes::C(4)};

/*
// -----------------------------------------------------------------------------



/*
// -----------------------------------------------------------------------------
// LED Blink control. 

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  if (velocity == 0) {  // 　Note ON "Velocity = 0" is NOTE Off.
    leds[pitch].setRGB( 0, 0, 0);
  } else {
    switch (channel) {  //  Select Ch       //　Blink velocity power!
      case 16:
        leds[pitch] = 0x008000;
        FastLEDSet_Ch[pitch]=1;
        break;
      case 15:
        leds[pitch] = 0x0000FF;
        FastLEDSet_Ch[pitch]=2;
        break;
      case 14:
        leds[pitch] = 0xFF0000;
        FastLEDSet_Ch[pitch]=3;
        break;
      case 13:
        leds[pitch] = 0xFFFF00;
        FastLEDSet_Ch[pitch]=4;
        break;
      case 12:
        leds[pitch] = 0xFFA500;
        FastLEDSet_Ch[pitch]=5;
        break;
      case 11:
        leds[pitch] = 0xFF00FF;
        FastLEDSet_Ch[pitch]=6;
        break;
      case 10:
        leds[pitch] = 0x00BFFF;
        FastLEDSet_Ch[pitch]=7;
        break;
      case 9:
        leds[pitch] = 0xFFE4E1;
        FastLEDSet_Ch[pitch]=8;
        break; 
      case 8:
        leds[pitch] = 0xADFF2F;
        FastLEDSet_Ch[pitch]=9;
        break;
      case 7:
        leds[pitch] = 0x00008B;
        FastLEDSet_Ch[pitch]=10;
        break;
      case 6:
        leds[pitch] = 0x00FFFF;
        FastLEDSet_Ch[pitch]=11;
        break;
      case 5:
        leds[pitch] = 0xF08080;
        FastLEDSet_Ch[pitch]=12;
        break;
      case 4:
        leds[pitch] = 0x800080;
        FastLEDSet_Ch[pitch]=13;
        break;
      case 3:
        leds[pitch] = 0xB22222;
        FastLEDSet_Ch[pitch]=14;
        break;
      case 2:
        leds[pitch] = 0x00BFFF;
        FastLEDSet_Ch[pitch]=15;
        break;
      case 1:
        leds[pitch] = 0xF5F5F5;
        FastLEDSet_Ch[pitch]=16;
        break;        
    }

  }
      FastLED.show();
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  switch (channel) {
    case 1: 
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
      leds[pitch].setRGB( 0, 0, 0); FastLEDSet_Ch[pitch]=0;
      FastLED.show();
      break;
  }
}

void handleControlChange(byte channel , byte number , byte value )
{

  switch (number) {
    case 120: for(int i=0;i<NUM_LEDS;i++){leds[i].setRGB( 0, 0, 0);}  break;  // 120 is All sound Off      : All LED OFF
    case 121: for(int i=0;i<NUM_LEDS;i++){leds[i].setRGB( 0, 0, 0);}  break;  // 121 Reset All controller  : All LED OFF
    case 123: for(int i=0;i<NUM_LEDS;i++){leds[i].setRGB( 0, 0, 0);}  break;  // 123 All Note Off         : All LED OFF
   }
  
  FastLED.show();  
}
*/

// -----------------------------------------------------------------------------

void setup()
{
  // See FastLED examples and documentation for more information.
  //FastLED.addLeds<NEOPIXEL, ledpin>(leds.data, leds.length);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
  FastLED.setCorrection(TypicalPixelString);
  //midiled.setBrightness(128);
  Control_Surface.begin();
    
    //LED test All On! after OFF
    // -----------------------------------------------------------------------------
    FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    //FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 20, 0, 0);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }

    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 0, 20, 0);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }
               
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 0, 0, 20);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }
            
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 0, 0, 0);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }

}


void loop()
{
  Control_Surface.loop();
  if (midiled.getDirty()) { // If the colors changed
    FastLED.show();         // Update the LEDs with the new colors
    midiled.clearDirty();   // Clear the dirty flag
  }
}
