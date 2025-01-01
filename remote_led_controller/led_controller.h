#ifndef LED_CONTROLLER
#define LED_CONTROLLER

#include <Adafruit_NeoPixel.h>

#define LED_PIN 10
#define LED_NUMBER 60

/**
* @struct Defines a single led on the led strip.
*/
typedef struct Led {
  uint8_t id;
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t white;
};

/**
* @class A class that manage a SK6812 led strip.
*/
class LedController {
  public:
    LedController(void);

    /**
    * Initialize the LED controller.
    */
    void begin(void);

    /**
    * Set the whole led strip brightness.
    * @param brightness The brightness value between 0 and 255.
    */
    void setBrightness(uint8_t brightness);

    /**
    * Clear the whole strip.
    */
    void clear(void);

    /**
    * Turn on the given led.

    * @param led A pointer to the corresponding led to turn on.
    */
    void led(const Led* led);

    /**
    * Turn on the given array of leds.
    * When a led is already on and not present on the given array, the led stay unchanged.
    * @param leds An array containing the leds to turn on.
    */
    void leds(Led leds[]);

    /**
    * Linear interpolate the color of the led from begin to end.
    * 
    * @param bebin A pointer to the begin led data.
    * @param end A pointer to the end led data.
    * @param percent The progress of the interpolation.
    *
    * @note The begin and end id must point to the same led otherwise nothing happens.
    *       The percent must be between O and 1.
    */
    void lerp(const Led* begin, const Led* end, float percent);
  private:
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUMBER, LED_PIN, NEO_GRBW + NEO_KHZ800);

    /**
    * Update the given led color without performing any flush.
    * So, if you want the strip to be updated you need to call `flush` after this method.
    * @param led A pointer pointing to the led data.
    */
    void updateLed(const Led* led);

    /**
    * Flush any changes to the led strip.
    */
    void flush();
};

#endif