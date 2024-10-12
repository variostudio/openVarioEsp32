#include "durations.h"

#define SOUND_OUT 25

/**
  Play tone and return duration
*/
int playTone(float vario) {
  if (vario >= 0.1) {
    int freq = 700 + int(10 * vario / 0.1);
    int dur = durations[durations_len-1];
    int dur_index = int(vario * 10);
    if (dur_index < durations_len) {
      dur = durations[durations_len - 1];
    }    

    tone(SOUND_OUT, freq, dur);
    return dur;
  }
  return 0;
}
