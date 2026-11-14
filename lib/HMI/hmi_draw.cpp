
#include <hmi_draw.h>
#include <hmi_xbmp.h>
#include <hmi_defines.h> 
#include <timer.h>
#include <U8g2lib.h>

// You might need to declare or include the u8g2 object
extern U8G2 u8g2;  // Make sure this matches the declaration in your main.cpp


void HMI_ObjectTemp(String temp) {
  u8g2.setFont(u8g2_font_logisoso16_tf);
  u8g2.drawStr(31,31,temp.c_str());
  u8g2.drawStr(80,31,"C");
}

void HMI_Clock(RTClock clock){
  char clock_str[9]; // Create 12 bytes char array / string

  // Process clock string
  strcpy (clock_str,u8x8_u8toa(clock.hours, 2)); // Copy hours in two digits
  strcat (clock_str,clock.beat?":":"."); // Concatenate ":" or " "
  strcat (clock_str,u8x8_u8toa(clock.minutes, 2)); // Concatenate minutes in two digits
  strcat (clock_str,clock.pm?" PM":" AM"); // Conactenate "" PM" or " AM"

  // Draw clock string
  u8g2.setFont(u8g2_font_nerhoe_tf); // Set string font
  u8g2.setDrawColor(1); // Set to draw pixel
  u8g2.drawStr(CLOCK_X,CLOCK_Y,clock_str);  // Draw clock string
}

void HMI_Battery(void){

}

void HMI_Charger(void){
  
}

void HMI_AmbientTemp(void){
  u8g2.setFont(u8g2_font_nerhoe_tf);
  u8g2.setDrawColor(1);
  u8g2.drawStr(AMBIENT_TEMP_X,AMBIENT_TEMP_Y,"25.5 C");
}

void HMI_Message(u08 MessageIndex){

}

void HMI_Page(u08 PageIndex){

}

void HMI_Message1(void){
  u8g2.setFont(u8g2_font_t0_12_mf);
  //u8g2.setFont(u8g2_font_nerhoe_tf);
  u8g2.setDrawColor(0);
  u8g2.drawBox(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H);
  u8g2.setDrawColor(1);
  u8g2.drawRFrame(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H,MSG_FRAME_R);
  u8g2.drawStr(MSG_L1_X,MSG_L1_Y,"This message is");
  u8g2.drawStr(MSG_L2_X,MSG_L2_Y,"info type with");
  u8g2.drawStr(MSG_L3_X,MSG_L3_Y,"icon represent");
  u8g2.drawStr(MSG_L4_X,MSG_L4_Y,"and four lines");
  u8g2.setBitmapMode(0); // Non-Transparent BMP
  u8g2.drawXBM(MSG_ICON_X,MSG_ICON_Y,MSG_ICON_W,MSG_ICON_H, bmp_info);

}

void HMI_Message2(void){
  u8g2.setFont(u8g2_font_t0_12_mf);
  //u8g2.setFont(u8g2_font_nerhoe_tf);
  u8g2.setDrawColor(0);
  u8g2.drawBox(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H);
  u8g2.setDrawColor(1);
  u8g2.drawRFrame(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H,MSG_FRAME_R);
  u8g2.drawStr(MSG_L1_X,MSG_L1_Y,"This message is");
  u8g2.drawStr(MSG_L2_X,MSG_L2_Y,"warn type with");
  u8g2.drawStr(MSG_L3_X,MSG_L3_Y,"icon represent");
  u8g2.drawStr(MSG_L4_X,MSG_L4_Y,"and four lines");
  u8g2.setBitmapMode(0); // Transparent BMP
  u8g2.drawXBM(MSG_ICON_X,MSG_ICON_Y,MSG_ICON_W,MSG_ICON_H, bmp_warn);
}

void HMI_Message3(void){
  //u8g2.setFont(u8g2_font_t0_12_mf);
  u8g2.setFont(u8g2_font_nerhoe_tf);
  u8g2.setDrawColor(0);
  u8g2.drawBox(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H);
  u8g2.setDrawColor(1);
  u8g2.drawRFrame(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H,MSG_FRAME_R);
  u8g2.drawStr(MSG_L1_X,MSG_L1_Y,"This message is");
  u8g2.drawStr(MSG_L2_X,MSG_L2_Y,"check type with");
  u8g2.drawStr(MSG_L3_X,MSG_L3_Y,"icon represent");
  u8g2.drawStr(MSG_L4_X,MSG_L4_Y,"and four lines");
  u8g2.setBitmapMode(0); // Solid BMP
  u8g2.drawXBM(MSG_ICON_X,MSG_ICON_Y,MSG_ICON_W,MSG_ICON_H, bmp_check);
}

void HMI_Message4(void){
  //u8g2.setFont(u8g2_font_t0_12_mf);
  u8g2.setFont(u8g2_font_nerhoe_tf);
  u8g2.setDrawColor(0);
  u8g2.drawBox(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H);
  u8g2.setDrawColor(1);
  u8g2.drawRFrame(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H,MSG_FRAME_R);
  u8g2.drawStr(MSG_L1_X,MSG_L1_Y,"This message is");
  u8g2.drawStr(MSG_L2_X,MSG_L2_Y,"error type with");
  u8g2.drawStr(MSG_L3_X,MSG_L3_Y,"icon represent");
  u8g2.drawStr(MSG_L4_X,MSG_L4_Y,"and four lines");
  u8g2.setBitmapMode(0); // Solid BMP
  u8g2.drawXBM(MSG_ICON_X,MSG_ICON_Y,MSG_ICON_W,MSG_ICON_H, bmp_error);
}

void HMI_MainPage(void){
  /*
  u8g2.setFont(u8g2_font_nerhoe_tf); // Select font
  u8g2.setDrawColor(0); // Erase pixel
  u8g2.drawBox(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H); // Clear message area
  u8g2.setDrawColor(1); // Print pixel
  u8g2.drawBox(44,24,2,15); // Draw sensor cabinet
  u8g2.drawLine(35,24,44,30);
  u8g2.drawLine(35,38,44,30);
  u8g2.setBitmapMode(0); // Print solid BMP
  u8g2.drawXBM(2,24,30,36, head_left); //Draw head_left graphic
  u8g2.drawStr(50,MSG_L2_Y,"To start get closer"); // Text 1
  u8g2.drawStr(50,MSG_L3_Y,"to the sensor"); // Text 2
  */
  u8g2.setFont(u8g2_font_nerhoe_tf); // Select font
  u8g2.setDrawColor(0); // Erase pixel
  u8g2.drawBox(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H); // Clear message area
  u8g2.setDrawColor(1); // Print pixel
  u8g2.drawStr(11,20,"Come closer to sensor"); // Text 1
  //u8g2.setFont(u8x8_font_open_iconic_arrow_2x2); // Select font
  
  //u8g2.drawUTF8(35+40,24+5,(char *)({0x52,0x00;})); // Draw
  u8g2.drawBox(44+40,24+5,2,15); // Draw sensor cabinet
  //u8g2.drawLine(35+40,24+5,44+40,30+5);
  //u8g2.drawLine(35+40,38+5,44+40,30+5);
  u8g2.setBitmapMode(0); // Print solid BMP
  u8g2.drawXBM(2+40,24+5,30,36, head_left); //Draw graphic
}

void HMI_ReadingPage(void){
  u8g2.setFont(u8g2_font_nerhoe_tf); // Select font
  u8g2.setDrawColor(0); // Erase pixel
  u8g2.drawBox(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H); // Clear message area
  u8g2.setDrawColor(1); // Print pixel
  //u8g2.drawStr(11,35,"Reading temperature..."); // Text 1
  u8g2.drawStr(11,20,"Reading temperature..."); // Text 1
  u8g2.drawRFrame(10,50,100,8,3);
}

void HMI_HealthTemp(void){
  u8g2.setFont(u8g2_font_nerhoe_tf); // Select font
  u8g2.setDrawColor(0); // Erase pixel
  u8g2.drawBox(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H); // Clear message area
  u8g2.setDrawColor(1); // Print pixel
  u8g2.drawStr(11,20,"Healthy temperature"); // Text 1
  u8g2.setBitmapMode(0); // Print solid BMP
  u8g2.drawXBM(12,29,30,36, head_left); //Draw graphic
  u8g2.drawXBM(45,29,12,30, thermo); //Draw graphic
  u8g2.setFont(u8g2_font_prospero_bold_nbp_tr); // Select font
  u8g2.drawStr(75,40,"85 F"); // Text 1
}

void HMI_FeverTemp(void){
  u8g2.setFont(u8g2_font_nerhoe_tf); // Select font
  u8g2.setDrawColor(0); // Erase pixel
  u8g2.drawBox(MSG_FRAME_X,MSG_FRAME_Y,MSG_FRAME_W,MSG_FRAME_H); // Clear message area
  u8g2.setDrawColor(1); // Print pixel
  u8g2.drawStr(11,20,"Fever temperature"); // Text 1
  u8g2.setBitmapMode(0); // Print solid BMP
  u8g2.drawXBM(12,29,30,36, head_left); //Draw graphic
  u8g2.drawXBM(45,29,12,30, thermo); //Draw graphic
  u8g2.drawBox(49,35,2,5); // Draw high thermo scale
  u8g2.setDrawColor(0); // Erase pixel
  u8g2.drawXBM(25,32,5,7, sweat); //Draw graphic
  u8g2.setDrawColor(1); // Print pixel
  u8g2.setFont(u8g2_font_prospero_bold_nbp_tr); // Select font
  u8g2.drawStr(75,40,"100 F"); // Text 1
}

void HMI_Draw(void(*fun)()){
  u8g2.firstPage();  
  do {
    HMI_Clock();
    fun();
  } while( u8g2.nextPage() );
}


