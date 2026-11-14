
#ifndef HMI_DRAW_H
#define HMI_DRAW_H

#include <U8g2lib.h>
#include <typedefs.h>

void HMI_Message1(void);
void HMI_Message2(void);
void HMI_Message3(void);
void HMI_Message4(void);
void HMI_MainPage(void);

void HMI_ReadingPage(void);
void HMI_HealthTemp(void);
void HMI_FeverTemp(void);
void HMI_Draw(void(*fun)());


void HMI_ObjectTemp(void);
void HMI_Clock(void);
void HMI_Battery(void);
void HMI_Charger(void);
void HMI_AmbientTemp(void);
void HMI_Message(u08 MessageIndex);
void HMI_Page(u08 PageIndex);


#endif // HMI_DRAW_H

