#include "headers.h"

float get_wpm(float time, int typed){
  float wpm = 0;
  wpm = typed / 5;
  wpm = wpm / time;
  return wpm
}
