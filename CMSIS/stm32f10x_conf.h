/**
  ******************************************************************************
  * @file USART/Printf/stm32f10x_conf.h 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Library configuration file.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment the line below to enable peripheral header file inclusion */
 #include "stm32f10x_adc.h" 
 #include "stm32f10x_bkp.h" 
/* #include "stm32f10x_can.h" */
/* #include "stm32f10x_cec.h" */
/* #include "stm32f10x_crc.h" */
/* #include "stm32f10x_dac.h" */
/* #include "stm32f10x_dbgmcu.h" */
/* #include "stm32f10x_dma.h" */
#include "stm32f10x_exti.h"
#include "stm32f10x_flash.h"
/* #include "stm32f10x_fsmc.h" */
#include "stm32f10x_gpio.h"
/* #include "stm32f10x_i2c.h" */
/* #include "stm32f10x_iwdg.h" */
#include "stm32f10x_pwr.h" 
#include "stm32f10x_rcc.h"
#include "stm32f10x_rtc.h" 
/* #include "stm32f10x_sdio.h" */
/* #include "stm32f10x_spi.h" */
#include "stm32f10x_tim.h" 
#include "stm32f10x_usart.h"
/* #include "stm32f10x_wwdg.h" */
#include "misc.h"  /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define RCC_GPIO_LED                                 RCC_APB2Periph_GPIOD
#define GPIO_LED_PORT                                GPIOD    
#define GPIO_LED1                                    GPIO_Pin_2    
#define GPIO_LED2                                    GPIO_Pin_3    
#define GPIO_LED3                                    GPIO_Pin_4    
#define GPIO_LED4                                    GPIO_Pin_7
#define GPIO_LED_ALL                                 GPIO_LED1 |GPIO_LED2 |GPIO_LED3 |GPIO_LED4 

/* KEY °´¼ü  */
#define RCC_KEY1                                    RCC_APB2Periph_GPIOC
#define GPIO_KEY1_PORT                              GPIOC    
#define GPIO_KEY1                                   GPIO_Pin_2
#define GPIO_KEY1_EXTI_LINE                         EXTI_Line2
#define GPIO_KEY1_EXTI_PORT_SOURCE                  GPIO_PortSourceGPIOC
#define GPIO_KEY1_EXTI_PIN_SOURCE                   GPIO_PinSource2
#define GPIO_KEY1_EXTI_IRQn                         EXTI2_IRQn 

#define RCC_KEY2                                    RCC_APB2Periph_GPIOC
#define GPIO_KEY2_PORT                              GPIOC   
#define GPIO_KEY2                                   GPIO_Pin_3
#define GPIO_KEY2_EXTI_LINE                         EXTI_Line3
#define GPIO_KEY2_EXTI_PORT_SOURCE                  GPIO_PortSourceGPIOC
#define GPIO_KEY2_EXTI_PIN_SOURCE                   GPIO_PinSource3
#define GPIO_KEY2_EXTI_IRQn                         EXTI3_IRQn 

#define RCC_KEY3                                    RCC_APB2Periph_GPIOC
#define GPIO_KEY3_PORT                              GPIOC    
#define GPIO_KEY3                                   GPIO_Pin_4 
#define GPIO_KEY3_EXTI_LINE                         EXTI_Line4
#define GPIO_KEY3_EXTI_PORT_SOURCE                  GPIO_PortSourceGPIOC
#define GPIO_KEY3_EXTI_PIN_SOURCE                   GPIO_PinSource4
#define GPIO_KEY3_EXTI_IRQn                         EXTI4_IRQn 

#define RCC_KEY4                                    RCC_APB2Periph_GPIOC
#define GPIO_KEY4_PORT                              GPIOC   
#define GPIO_KEY4                                   GPIO_Pin_5
#define GPIO_KEY4_EXTI_LINE                         EXTI_Line5
#define GPIO_KEY4_EXTI_PORT_SOURCE                  GPIO_PortSourceGPIOC
#define GPIO_KEY4_EXTI_PIN_SOURCE                   GPIO_PinSource5
#define GPIO_KEY4_EXTI_IRQn                         EXTI9_5_IRQn 

#define GPIO_KEY_ANTI_TAMP                          GPIO_KEY3
#define GPIO_KEY_WEAK_UP                            GPIO_KEY4

/* Values magic to the Board keys */
#define  NOKEY  0
#define  KEY1   1
#define  KEY2   2
#define  KEY3   3
#define  KEY4   4
#define  KEY5   5

/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed. 
  *   If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __STM32F10x_CONF_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
