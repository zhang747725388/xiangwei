

#ifndef __74HC595_H

#define __74HC595_H

// 74HC595
#include "rsystem.h"
#include "rtime.h"

#define HC595_PORT  GPIOA

#define HC595_DATA  GPIO_Pin_8    // serial data input, pin14

#define HC595_SCLK  GPIO_Pin_9   // shift register clock input, pin11

#define HC595_RCLK  GPIO_Pin_10     // storage register clock input, pin12

#define HC595_DELAY Timer_Delayms(1);
#define open  1
#define close 2
#define start  3
#define stop   4
#define strong  5
#define door  6
#define mode  7
#define OPENCMD  8
 #define CLOSECMD  9
  #define Delay  10
	  #define AutoConnect  11
extern uint8_t hc595data[8];
extern void hc595_init ( void ) ;

extern void hc595_write_byte ( uint8_t byte ) ;

extern void hc595_latch ( void ) ;

extern void hc595_display ( uint8_t data [ ] ) ;
extern void setMainMode(u8 value);
extern void setMainValue(u8 mode1, u8 value);
extern void setOpenclose(u8 mode1,u8 type1);
extern void SetHCMode(u8 type);
#endif
