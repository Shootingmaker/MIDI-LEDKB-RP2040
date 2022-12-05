/**
 * This example demonstrates the use of addressable LEDs that respond to 
 * incoming  MIDI note events. This example uses a custom color mapper to
 * get a rainbow effect across the LED strip.
 * 
 * @boards  AVR, AVR USB, Due, Nano 33 IoT, Teensy 3.x, ESP32
 * 
 * @note    You might lose incoming MIDI data while the LED strip is being 
 *          updated. To avoid this, don't use an Arduino UNO.  
 *          See <https://github.com/FastLED/FastLED/wiki/Interrupt-problems>
 * 
 * Connections  
 * -----------
 * 
 * - 2: Data pin of NeoPixel LED strip with at least 8 pixels.
 * 
 * Behavior
 * --------
 * 
 * If a MIDI Note On event for note 0x3C (C4 or middle C) is sent, the first LED
 * will light up, if a Note Off event for that note is sent, the LED will turn 
 * off.  
 * If a MIDI Note On event for note 0x3D (C#4) is sent, the second LED will 
 * light up, etc.  
 * (A Note On event with a velocity of zero also counts as a Note Off event.)
 * 
 * Mapping
 * -------
 * 
 * Route the MIDI output of a MIDI keyboard to the Arduino's MIDI input. Then
 * play a middle C and some notes above it on the keyboard.
 * 
 * Written by PieterP, 2019-10-15  
 * https://github.com/tttapa/Control-Surface
 */

//FastLED3.5 & manual merge RP2040 PIO support
#include <FastLED.h>
// Must be before Control Surface to enable FastLED features of Control Surface
#include <Control_Surface.h>

//USB Stack >>>> Adafruit Tiny USB


// How many leds in your strip?
Array<CRGB, 88> leds {};
Array<CRGB, 88> ledscopy {};

// Rasberry Pi Pico SPI
#define DATA_PIN D3
#define CLOCK_PIN D2

USBMIDI_Interface midi;

// Create a functor that maps the velocity and the index of a note to a color.
struct RainbowColorMapper {
  CHSV operator()(uint8_t velocity, uint8_t index) const {
    return CHSV(255 * index / leds.length, 255, 255u * velocity / 127u);
  }
};

//DefaultColorMapper or RainbowColorMapper
//NoteRangeFastLED <leds.length, DefaultColorMapper> midiled {leds, {MIDI_Notes::A(0),CHANNEL_1,CABLE_1}};
//NoteRangeFastLED <leds.length, RainbowColorMapper> midiled {leds, {MIDI_Notes::A(0),CHANNEL_1,CABLE_1}};

NoteRangeFastLED <leds.length, RainbowColorMapper> midiled {leds, {MIDI_Notes::A(0),CHANNEL_1,CABLE_1}};


void setup() {
  // See FastLED examples and documentation for more information.
  //FastLED.addLeds<NEOPIXEL, ledpin>(leds.data, leds.length);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds.data, leds.length);
  FastLED.setCorrection(TypicalPixelString);
  midiled.setBrightness(128);
  Control_Surface.begin();
}

void loop() {
  Control_Surface.loop();
  if (midiled.getDirty()) { // If the colors changed
   
    //ここでReverse Arryすると発火タイミングが違うのでダメっぽい
    
    FastLED.show();         // Update the LEDs with the new colors
    midiled.clearDirty();   // Clear the dirty flag
  }
}




//TO DO
/*
1.Reverse Array　LEDS

2.1-16 CHANNEL LISSEN　now only 

3.add Color mode setting

3-1.ColorMode FASTLED Pre-defined color palletes :http://fastled.io/docs/3.1/colorpalettes_8cpp_source.html

3-2.ColorMode RainbowColorMapper

3-3.ColorMode Synthetia :https://github.com/tttapa/Control-Surface/issues/676
 Differentiate that if the note is received on channel 0, it lights up a White LED
 If the note is received on Channel 1-5,11. the LEDS for this light up in Green
 If the note is received on Channel 6-10,12. the LEDS for this light up in Blue
*/


/*[MEMO]
    //reserve Array [88] leds

    /*
    //swap使えないボツ C++17のくせに・・・
    for (int i = 0; i < leds.length ; i++) {
    // CRGB配列を逆転するために、対応する要素を交換します
    std::swap( leds[i] , leds[leds.length-i-1] );
    }
    
    // swap使えないから、reverseも使えないFUCK
    // std::reverse(leds[0], leds[leds.length-1]);
    
    //　配列コピー＆反転再コピーで実装する。

      for (int i = 0; i < leds.length  ; i++) {
    // CRGB配列を逆転するために、対応する要素をコピーします
     ledscopy[i] = leds[i];
    }
      
    for (int i = 0; i < leds.length  ; i++) {
    // CRGB配列を逆転するために、対応する要素をアドレスを逆から再コピーします
     leds[i] = ledscopy[leds.length-1-i];
    }


*/