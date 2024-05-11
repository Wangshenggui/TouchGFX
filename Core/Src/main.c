/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "crc.h"
#include "dma.h"
#include "dma2d.h"
#include "iwdg.h"
#include "ltdc.h"
#include "ramecc.h"
#include "rng.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sys.h"
#include "delay.h"
#include "Radio.h"
#include "w25qxx.h"
#include "Voice.h"
#include "24cxx.h"
#include "Backlight.h"
#include "Voice.h"
#include "malloc.h"

#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "usbd_storage.h" 
 
#include "tim_it.h"

#include "ff.h"
#include "myFatFs.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "usmart_cmd_input.h"
#include "usmart.h"

#include "arm_math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
MAIN_FREERTOS_GlobalVariableStructure MAIN_FREERTOS_GlobalVariableStruct={0};
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t g_osRuntimeCounter = 0;

char g_tasks_buf[512]; //用于存放显示数据
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
////浣胯兘STM32H7鐨凩1-Cache,鍚屾椂寮?鍚疍 cache鐨勫己鍒�??忓啓
//void Cache_Enable(void)
//{
//    SCB_EnableICache();	//浣胯兘I-Cache,鍑芥暟鍦╟ore_cm7.h閲岄潰�?�氫�?
//    SCB_EnableDCache();	//浣胯兘D-Cache,鍑芥暟鍦╟ore_cm7.h閲岄潰�?�氫�? 
//	SCB->CACR|=1<<2;	//寮哄埗D-Cache閫忓�?,濡備笉寮?鍚?忓啓,瀹為檯浣跨敤涓彲鑳介亣鍒板悇绉嶉棶�??
//}

//瑁佸�?瀛楃涓?
static char* substring(char* dst, char* src, int start, int len)
{
    int length = 100;//�??澶ч暱�??
    if (start >= length || start < 0)
        return NULL;
    if (len > length)
        len = length - start;
    src += start;
    while (len--)
    {
        *(dst++) = *(src++);
    }
    *(dst++) = '\0';
    return dst;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */


//      /* Enable I-Cache---------------------------------------------------------*/
//    SCB_EnableICache();

//    /* Enable D-Cache---------------------------------------------------------*/
//    SCB_EnableDCache();
  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
    QSPI_Enable_Memmapmode();
    Cache_Enable();
    delay_init(480);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DMA2D_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_USART6_UART_Init();
  MX_SPI2_Init();
  MX_ADC3_Init();
  MX_TIM6_Init();
  MX_LTDC_Init();
  MX_FMC_Init();
  MX_USART2_UART_Init();
  MX_TIM15_Init();
  MX_TIM12_Init();
  MX_TIM16_Init();
  MX_IWDG1_Init();
  MX_RTC_Init();
  MX_RNG_Init();
  MX_CRC_Init();
  MX_RAMECC_Init();
  MX_TouchGFX_Init();
  /* Call PreOsInit function */
  MX_TouchGFX_PreOSInit();
  /* USER CODE BEGIN 2 */
  /*鍦∕X_FMC_Init();鍚庢坊鍔�?
  Lcd_Initialize();   \
  鍒濆鍖?*/
  
    delay_ms(1000);//绛夊緟鏌愪簺鍣ㄤ欢涓婄數

//    delay_ms(5000);

    //鍚姩鏃犵嚎鐢垫帴鏀?
    HAL_UART_Receive_IT(&huart1, &RadioRTxStru.Receive, 1);
    HAL_UART_Transmit_DMA(&huart1, (uint8_t*)"Read", 1);//鍏堝彂閫佺�??涓暟鎹紝涓嬩竴甯ц兘澶熷彂閫佹垚鍔?

    HAL_UART_Receive_IT(&huart6, &VoiceRTxStru.Receive, 1);
    
    //�?启串口接收中�?
    HAL_UART_Receive_IT(&huart2, &UART_USMART_Struct.Receive, 1);
    //__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
    
    //�?启定时器中断，用于判断串口空闲中�?
    HAL_TIM_Base_Start_IT(&htim15);

    //�?启定时器中断，用做定时任务处理（osDelay不准确）
    HAL_TIM_Base_Start_IT(&htim12);

    HAL_TIM_Base_Start_IT(&htim16); //�?启freeRtos系统计数定时器，要求中断时间至少�?100us
    
    usmart_dev.init(0);	//执行usmart初始�?
    

    W25QXX_Init();					//W25QXX鍒濆鍖?
    while (W25QXX_ReadID() != W25Q256);
    AT24CXX_Init();					//IIC鍒濆鍖?
    while (AT24CXX_Check());//�??娴嬩笉鍒?24c02

    my_mem_init(SRAMIN);			//鍒濆鍖栧唴閮ㄥ唴�?�樻�?(AXI)
    my_mem_init(SRAMEX);


      //璇煶鍒濆�??
    SetVoiceVolume(GetVoiceVolume());
    delay_ms(50);
    SetVoiceVolume(GetVoiceVolume());
    delay_ms(50);
    SetVoiceVolume(GetVoiceVolume());
    delay_ms(50);
    VoicePlayback(1);
    delay_ms(50);
    VoicePlayback(1);
    delay_ms(50);
    VoicePlayback(1);
    delay_ms(50);

    //SaveBacklight(560);
    SetBacklight(AT24CXX_ReadOneByte(0) * 10);//�??鍚儗鍏?
    //鏍�?�噯ADC
    HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
    //  //�??鍚畾鏃跺櫒
    //  HAL_TIM_Base_Start_IT(&htim6);

    uint8_t FatFs_temp;

    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:POWER ON.ini", FA_READ);

    char read_buff[50];
    char dst[10];

    f_lseek(&FIL_GlobalVariableStruct.file, f_size(&FIL_GlobalVariableStruct.file) - 22);

    f_read(&FIL_GlobalVariableStruct.file, read_buff, sizeof read_buff, NULL);

    printf("%s", read_buff);

    for (uint8_t i = 0; i < 34 - 2; i++)
    {
        if (read_buff[i] == ' ' && read_buff[i + 1] == ':' && read_buff[i + 2] == ' ')
        {
            substring(dst, read_buff, i + 4, 3);
            FatFs_temp = atoi((const char*)dst);
        }
    }
    printf("�?机次�?:%d", FatFs_temp);
    /* 鍏抽棴鏂囦欢 */
    f_close(&FIL_GlobalVariableStruct.file);


    f_open(&FIL_GlobalVariableStruct.file, (char*)"1:POWER ON.ini", FA_WRITE);
    /* 杩藉姞鍒版枃浠剁殑缁撳熬 */
    f_lseek(&FIL_GlobalVariableStruct.file, f_size(&FIL_GlobalVariableStruct.file));
    f_printf(&FIL_GlobalVariableStruct.file, "系统�?机次�? : <%03d>\r\n", ++FatFs_temp);
    /* 鍏抽棴鏂囦欢 */
    f_close(&FIL_GlobalVariableStruct.file);
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in cmsis_os2.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
    if (htim->Instance == TIM6)
        HAL_TIM6_PeriodElapsedCallback(htim);
    if (htim->Instance == TIM15)
        HAL_TIM15_PeriodElapsedCallback(htim);
    if (htim->Instance == TIM12)
        HAL_TIM12_PeriodElapsedCallback(htim);
    if (htim->Instance == TIM16)
        g_osRuntimeCounter++;
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
