
#ifndef TIMER_TYPEDEFS_H
#define TIMER_TYPEDEFS_H

#include <typedefs.h>

 typedef struct Timer{
  u32 timer;
  u32 time;
  u08 type;
  u08 reset;
} timer;

typedef struct RTClock{
  u08 seconds;
  u08 minutes;
  u08 hours;
  u08 day;
  u08 month;
  u08 year;
  u01 century;
  u01 h12;
  u01 pm;
  u01 beat;
} rtclock;

#endif