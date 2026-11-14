
#ifndef HMI_DEFINES_H
#define HMI_DEFINES_H

//*********************************************************************
//*                      Definitions                                  *
//*********************************************************************

// HMI ELEMENTS LOCATIONS AND SIZES DEFINITIONS ***********************
#define CLOCK_X                         90
#define CLOCK_Y                         8

#define AMBIENT_TEMP_X                  0
#define AMBIENT_TEMP_Y                  8

#define MSG_ICON_X                      4
#define MSG_ICON_Y                      24
#define MSG_ICON_W                      24
#define MSG_ICON_H                      24

#define MSG_L1_X                        30
#define MSG_L1_Y                        21 //19
#define MSG_L2_X                        30
#define MSG_L2_Y                        35 //31
#define MSG_L3_X                        30
#define MSG_L3_Y                        48 //42
#define MSG_L4_X                        30
#define MSG_L4_Y                        61 //53

#define MSG_FRAME_X                     0
#define MSG_FRAME_Y                     9
#define MSG_FRAME_W                     128
#define MSG_FRAME_H                     55
#define MSG_FRAME_R                     7

//HMI ELEMENTS ********************************************************
#define HMI_CLOCK                       0
#define HMI_AMB_TEMP                    1
#define HMI_PAGE                        2
#define HMI_MESSAGE                     3

#define CLOCK_DISABLED                  0
#define CLOCK_ENABLE                    1

#define AMB_TEMP_DISABLED               0
#define AMB_TEMP_ENABLE                 1

#define NONE_PAGE                       0
#define MAIN_PAGE                       1
#define READING_PAGE                    2
#define HEALTH_TEMP_PAGE                3
#define FEVER_TEMP_PAGE                 4

#define NONE_MESSAGE                    0
#define NON_BODY_TEMP_MESSAGE           1
#define TEMP_SENSOR_SERV_MESSAGE        2
#define GENERAL_SERV_MESSAGE            3

#endif // HMI_DEFINES_H