
//*********************************************************************
//*                      Libraires                                    *
//*********************************************************************
#include <Arduino.h>
#include <U8g2lib.h>
#include <Adafruit_MLX90614.h>
#include <DS3231.h>
#include <hmi_xbmp.h>
#include <hmi_defines.h>
#include <hmi_draw.h>
#include <timer_typedefs.h>
#include <typedefs.h>

//*********************************************************************
//*                      Definitions                                  *
//*********************************************************************

// APPLICATION CONSTANTS DEFINITIONS **********************************
#define TEMP_FACE_DISTANCE_MAX         float(5.0)     // Temp sensor max distance (cm)
#define TEMP_FACE_DISTANCE_MIN         float(10.0)    // Temp sensor min distance (cm)

#define PERSON_AWAY_DISTANCE            float(10.0)   // Distance that person is away from sensor

#define BODY_HIGH_FEVER_TEMP_BOUND      float(41.0)   // Body Hypertermic (Fever) Medical Emergency Temp Emergeny 
#define BODY_FEVER_TEMP_BOUND           float(38.0)   // Body Hypertermic (Fever) Temp
#define BODY_HEALTH_TEMP_MAX            float(37.5)   // Body Healthy Temp Max Bound
#define BODY_HEALTH_TEMP_MIN            float(36.5)   // Body Healthy Temp Min Bound
#define BODY_HYPO_TEMP_BOUND            float(35.0)   // Body Hypotermic Temp
#define BODY_LOW_HYPO_TEMP_BOUND        float(32.0)   // Body Hypertermic Medical Emergency Temp Emergeny 

#define ECHO_TIMEOUT                    26000         // Timeout that ultrasonic echo will be waited (ms)
#define TIME_TO_DIST_CONST              float(0.01712)// Conversion time (ms) -> distance (cm)

// CONTROLLER PIN DEFINITIONS *****************************************
#define PIN_HCSR04_TRGR                 13
#define PIN_HCSR04_ECHO                 12

//*********************************************************************
//*               Typedef Structures                                  *
//*********************************************************************
//*********************************************************************
//*                   Global Constants                                *
//*********************************************************************
//*********************************************************************
//*                   Global Variables                                *
//*********************************************************************

//U8G2_SSD1309_128X64_NONAME0_1_2ND_HW_I2C u8g2 (U8G2_R0,23);
U8G2_SSD1309_128X64_NONAME0_1_HW_I2C u8g2 (U8G2_R0, 23,22,21);
//U8G2_SSD1309_128X64_NONAME2_1_4W_HW_SPI u8g2 (U8G2_R0, SS, 16 ,17);
//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2 (U8G2_R2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

DS3231 RTClock;
rtclock MainClock;
String txtObjectTemp;



u08 HMI_Elements[4] = {
  CLOCK_ENABLE,
  AMB_TEMP_ENABLE,
  MAIN_PAGE,
  NONE_MESSAGE
};

bool tsk_workflow[5];
bool tsk_face_distance_sensing[2];
bool tsk_hmi_display[2];

timer TimerA;

timer tmrTsk_ClockUpdate;
timer tmrTsk_AmbientTempSense;

//*********************************************************************
//*                   Functions                                       *
//*********************************************************************

u08 isTimedout(timer *tmr){
  u08 result = false;
  
  if(millis()>tmr->timer){
    result = true;
    if((tmr->time>0) && (tmr->reset)) tmr->timer = tmr->time + millis();
  }
  return result;
}

void setTimer(timer *tmr){
  tmr->timer = tmr->time + millis();
}

float getDistance(void){

  u32 duration;
  float distance;

  //Sense distance from sensor A
  //Activate Trigger signal for HCSR04 sensor
  digitalWrite(PIN_HCSR04_TRGR,LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_HCSR04_TRGR, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_HCSR04_TRGR,LOW);
  
  //Measure Echo pulse signal width and calculate distance
  distance = pulseIn(PIN_HCSR04_ECHO, HIGH, ECHO_TIMEOUT)*TIME_TO_DIST_CONST;

  return distance;
}

uint16_t getMLXData(uint8_t reg){
  uint16_t result;
  Wire.setClock(100000);

  Wire.beginTransmission(0x5A); // start transmission to device
  Wire.write(reg);                 // sends register address to read from
  Wire.endTransmission(false);   // end transmission

  Wire.requestFrom(0x5A, (size_t)3); // send data n-bytes read
  result = Wire.read();                  // receive DATA
  result |= Wire.read() << 8;            // receive DATA

  Wire.read();

  //uint8_t pec = Wire.read();

  return result;
}

double getAmbientTempC(void){
  return getMLXData(0x06)*0.02-273.15;
}

double getObjectTempC(void){
  return getMLXData(0x07)*0.02-273.15;
}

void Application_Run(void){
  
  if(isTimedout(&TimerA)){
    tsk_hmi_display[0] = true;
  }

  /*
  if(tsk_workflow[0]==true){
    HMI_Elements.mainPage = true;
    tsk_workflow[0]=false;
    tsk_workflow[1]=false;
  }
  if(tsk_workflow[1]==true && isTimedout(&tmr_face_distance)){
    float face_distance = getDistance();

    if((face_distance >= TEMP_FACE_DISTANCE_MIN) && (face_distance <= TEMP_FACE_DISTANCE_MAX)){
      tsk_workflow[1]==false;
      tsk_workflow[2]==true;
    }
    else
      setTimer(&tmr_face_distance);
  }
  */
}

void Temp_Sense_Run(void){
  if(isTimedout(&tmrTsk_AmbientTempSense)){

  }
}

void Clock_Update_Run(void){
  if(isTimedout(&tmrTsk_ClockUpdate)){
    MainClock.year = RTClock.getYear();
    MainClock.month = RTClock.getMonth(MainClock.century);
    MainClock.hours = RTClock.getHour(MainClock.h12, MainClock.pm);
    MainClock.minutes = RTClock.getMinute();
    MainClock.seconds = RTClock.getSecond();
    MainClock.beat = !MainClock.beat;
    //RTClock.getTemperature() // Temperature not needed
  }
}

void HMI_Draw_Elements(void){
  if(HMI_Elements[HMI_CLOCK])        HMI_Clock();
  if(HMI_Elements[HMI_AMB_TEMP])     HMI_AmbientTemp();
  if(HMI_Elements[HMI_PAGE])         HMI_Page(HMI_Elements[HMI_PAGE]);
  if(HMI_Elements[HMI_MESSAGE])      HMI_Message(HMI_Elements[HMI_MESSAGE]);
}

void HMI_Display_Run(void){

  if(tsk_hmi_display[0] == true){
    u8g2.firstPage(); 
    HMI_Draw_Elements();
    tsk_hmi_display[0] = false;
    tsk_hmi_display[1] = true;
  }
  if(tsk_hmi_display[1] == true){
    if(u8g2.nextPage()){
      HMI_Draw_Elements();
    }
    else{
      tsk_hmi_display[1] = false;
      //if(HMI_Elements.clock)        HMI_Elements.clock = false;
      //if(HMI_Elements.mainPage)     HMI_Elements.mainPage = false;
      //if(HMI_Elements.readingPage)  HMI_Elements.readingPage = false;
    }   
  }
}

void loop(void) {
  Application_Run();
  HMI_Display_Run();
  Clock_Update_Run();

  //txtObjectTemp = String(getObjectTempC(),2);
  
  //strcpy(sec_str, u8x8_u8toa(second, 2));		/* convert m to a string with two digits */
  //strcpy(min_str, u8x8_u8toa(minute, 1));

  
  /*
  HMI_Draw(HMI_Message1);
  delay(1500);
  
  HMI_Draw(HMI_Message2);
  delay(1500);

  HMI_Draw(HMI_Message3);
  delay(1500);

  HMI_Draw(HMI_Message4);
  delay(1500);
  
  HMI_Draw(HMI_MainPage);
  delay(1500);

  HMI_Draw(HMI_ReadingPage);
  delay(1500);

  HMI_Draw(HMI_HealthTemp);
  delay(1500);
  
  HMI_Draw(HMI_FeverTemp);
  delay(1500);
  */
  //txtObjectTemp = String(getObjectTempC(),2);

  //Disp_Draw(HMI_ObjectTemp);

  //Serial.printf("Object Temp: %lf Ambient Temp: %lf\n\r", getObjectTempC(), getAmbientTempC());
  //Serial.printf("Date %d %d %d Time %d:%d:%d Temp: %f\n\r",RTClock.getYear(), RTClock.getMonth(Century), RTClock.getYear(), RTClock.getHour(h12, PM), RTClock.getMinute(), RTClock.getSecond(), RTClock.getTemperature());
  //Serial.printf("Distance %f\n\r",getDistance());
}

void setup(void) {
  Serial.begin(115200);
  Serial.printf("Serial Ready 115200 baud\n\r");

  u8g2.begin();
  Serial.printf("Display Ready\n\r");

  mlx.begin();
  Serial.printf("MLX Sensor Ready\n\r");

  pinMode(PIN_HCSR04_TRGR, OUTPUT);
  pinMode(PIN_HCSR04_ECHO, INPUT);
  digitalWrite(PIN_HCSR04_TRGR,LOW);
  Serial.printf("GPIO Ready\n\r");

  TimerA.time = 1000;
  TimerA.reset = true;

  tmrTsk_ClockUpdate.time = 1000;
  tmrTsk_ClockUpdate.reset = true;

  tmrTsk_AmbientTempSense.time = 1000;
  tmrTsk_AmbientTempSense.reset = true;

  MainClock.century = false;
}