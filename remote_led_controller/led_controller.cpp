#include "led_controller.h"

LedController::LedController() {

}

void LedController::begin() {
  // Initialize the strip and turn all the led off.
  strip.begin();
  strip.show();
}

void LedController::setBrightness(uint8_t brightness) {
  strip.setBrightness(brightness);
}

void LedController::led(const Led* led) {
  updateLed(led);
  flush();
}

void LedController::clear(void) {
  strip.clear();
}

void LedController::leds(Led leds[]) {
  int length = sizeof(leds) / sizeof(Led);

  for (int i=0; i < length; i++) {
    updateLed(&leds[i]);
  }

  flush();
}

void LedController::lerp(const Led* begin, const Led* end, float percent) {
  // Ensure that we are using the same led.
  if (begin->id != end->id) {
    return;
  }

  // Ensure that the percent is between O and 1.
  if (percent < 0 || percent > 1) {
    return;
  }

  int red, green, blue, white = 0;

  red = end->red * percent + begin->red * (1 - percent);
  green = end->green * percent + begin->green * (1 - percent);
  blue = end->blue * percent + begin->blue * (1 - percent);
  white = end->white * percent + begin->white * (1 - percent);

  const Led led = {
    .id  = begin->id,
    .red = red,
    .green = green,
    .blue = blue,
    .white = white
  };

  updateLed(&led);
  flush();
}

////////////////////////////
///// Internal methods /////
////////////////////////////
void LedController::updateLed(const Led* led) {
  strip.setPixelColor(
    led->id, 
    strip.Color(
      led->red, 
      led->green, 
      led->blue, 
      led->white
    )
  );
}

void LedController::flush() {
  strip.show();
}