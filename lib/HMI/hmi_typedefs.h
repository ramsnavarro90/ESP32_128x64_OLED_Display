#ifndef HMI_DEFINES_H
#define HMI_DEFINES_H

#include <typedefs.h>

 typedef struct Message{
  char TextL1[16];
  char TextL2[16];
  char TextL3[16];
  char TextL4[16];
  u08 time;
  u08 type;
  u08 *font;
  u08 *bitmap;
} message;

#endif