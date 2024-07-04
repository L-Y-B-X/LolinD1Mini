#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    14
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
void ChangePalettePeriodically();
void FillLEDsFromPaletteColors(uint8_t colorIndex);
void SetupPurpleAndGreenPalette();
void SetupTotallyRandomPalette();
void SetupBlackAndWhiteStripedPalette();
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}


void loop()
{
    ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};
// #include <FastLED.h>

// #define LED_PIN     5
// #define NUM_LEDS    14
// #define BRIGHTNESS  64
// #define LED_TYPE    WS2811
// #define COLOR_ORDER GRB
// CRGB leds[NUM_LEDS];

// #define UPDATES_PER_SECOND 100

// // Function declarations
// void loop();
// void setup();
// uint8_t calculateBreathBrightness(uint8_t breath, bool increasing);
// void fillLEDsWithRotatingBreathColor(uint8_t start, uint8_t brightness);
// void updateBreathIndex(uint8_t &breath, bool &increasing);

// void setup() {
//     delay(3000); // power-up safety delay
//     FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
//     FastLED.setBrightness(BRIGHTNESS);
// }

// void loop() {
//     static uint8_t startIndex = 0;
//     static uint8_t breath = 0;
//     static bool increasing = true;

//     uint8_t breathBrightness = calculateBreathBrightness(breath, increasing);
//     fillLEDsWithRotatingBreathColor(startIndex, breathBrightness);
//     FastLED.show();
//     FastLED.delay(1000 / UPDATES_PER_SECOND);

//     updateBreathIndex(breath, increasing);
    
//     // Slow down the rotation speed
//     static uint8_t tick = 0;
//     tick++;
//     if (tick >= 5) { // Update startIndex every 5 ticks
//         startIndex++;
//         tick = 0;
//     }
// }

// uint8_t calculateBreathBrightness(uint8_t breath, bool increasing) {
//     // Create a wider range of brightness variation
//     return map(sin8(breath), 0, 255, 50, 255); // Adjust minimum brightness to 50 for more dramatic effect
// }

// void fillLEDsWithRotatingBreathColor(uint8_t start, uint8_t brightness) {
//     CHSV color = CHSV(160, 255, brightness); // 160 is a hue value for light blue
//     for (int i = 0; i < NUM_LEDS; i++) {
//         leds[(start + i) % NUM_LEDS] = color;
//     }
// }

// void updateBreathIndex(uint8_t &breath, bool &increasing) {
//     if (increasing) {
//         if (breath < 255) {
//             breath++;
//         } else {
//             increasing = false;
//             breath--;
//         }
//     } else {
//         if (breath > 0) {
//             breath--;
//         } else {
//             increasing = true;
//             breath++;
//         }
//     }
// }
