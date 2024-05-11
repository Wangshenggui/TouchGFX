/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
//����CPUʹ���ʺ�CPU�¶�
typedef struct
{
    unsigned int cpu_usage;
    unsigned int total_count;
    uint8_t CPUtemperature;
}MAIN_FREERTOS_GlobalVariableStructure;
extern MAIN_FREERTOS_GlobalVariableStructure MAIN_FREERTOS_GlobalVariableStruct;


/*
* GUI��Ϣ���ж��� GUI_ControlTaskQueueHandle
*/
#define GUIConTaskQueFanOFF                 0   //���ȿ���
#define GUIConTaskQueFanON                  1
#define GUIConTaskQueNESStart               2   //NES��Ϸ����

/*
* �������GUI��Ϣ���ж��� Task_ControlGUIQueueHandle
*/
#define TaskConGUIQueRenTemp                '0' //�����¶�
#define TaskConGUIQueUpRadio                '1' //�������ߵ�����



//���Ź��¼����־
#define IWDG_Event_1    (0x01<<0)
#define IWDG_Event_2    (0x01<<1)
#define IWDG_Event_3    (0x01<<2)
#define IWDG_Event_4    (0x01<<3)

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define lcd_bl_Pin GPIO_PIN_5
#define lcd_bl_GPIO_Port GPIOB
#define lcd_spi_cs_Pin GPIO_PIN_11
#define lcd_spi_cs_GPIO_Port GPIOG
#define TestGPIO_1_Pin GPIO_PIN_5
#define TestGPIO_1_GPIO_Port GPIOE
#define Radio_M1_Pin GPIO_PIN_4
#define Radio_M1_GPIO_Port GPIOE
#define Radio_M0_Pin GPIO_PIN_3
#define Radio_M0_GPIO_Port GPIOE
#define lcd_spi_sdi_Pin GPIO_PIN_14
#define lcd_spi_sdi_GPIO_Port GPIOG
#define lcd_spi_wr_Pin GPIO_PIN_13
#define lcd_spi_wr_GPIO_Port GPIOG
#define Radio_RX_Pin GPIO_PIN_10
#define Radio_RX_GPIO_Port GPIOA
#define Radio_TX_Pin GPIO_PIN_9
#define Radio_TX_GPIO_Port GPIOA
#define Voice_Rx_Pin GPIO_PIN_7
#define Voice_Rx_GPIO_Port GPIOC
#define Voice_Tx_Pin GPIO_PIN_6
#define Voice_Tx_GPIO_Port GPIOC
#define ctiic_sda_Pin GPIO_PIN_7
#define ctiic_sda_GPIO_Port GPIOG
#define w25qxx_cs_Pin GPIO_PIN_10
#define w25qxx_cs_GPIO_Port GPIOF
#define CH340_TX_Pin GPIO_PIN_2
#define CH340_TX_GPIO_Port GPIOA
#define myiic_scl_Pin GPIO_PIN_4
#define myiic_scl_GPIO_Port GPIOH
#define myiic_sda_Pin GPIO_PIN_5
#define myiic_sda_GPIO_Port GPIOH
#define led_red_Pin GPIO_PIN_1
#define led_red_GPIO_Port GPIOB
#define ctiic_scl_Pin GPIO_PIN_6
#define ctiic_scl_GPIO_Port GPIOH
#define CH340_RX_Pin GPIO_PIN_3
#define CH340_RX_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
