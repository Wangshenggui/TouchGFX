/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ltdc.c
  * @brief   This file provides code for the configuration
  *          of the LTDC instances.
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
#include "ltdc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

LTDC_HandleTypeDef hltdc;

/* LTDC init function */
void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 95;
  hltdc.Init.VerticalSync = 14;
  hltdc.Init.AccumulatedHBP = 183;
  hltdc.Init.AccumulatedVBP = 17;
  hltdc.Init.AccumulatedActiveW = 663;
  hltdc.Init.AccumulatedActiveH = 817;
  hltdc.Init.TotalWidth = 711;
  hltdc.Init.TotalHeigh = 819;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 480;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 800;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0xC0000000;
  pLayerCfg.ImageWidth = 480;
  pLayerCfg.ImageHeight = 800;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */
    Lcd_Initialize();
  /* USER CODE END LTDC_Init 2 */

}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLL3.PLL3M = 2;
    PeriphClkInitStruct.PLL3.PLL3N = 18;
    PeriphClkInitStruct.PLL3.PLL3P = 2;
    PeriphClkInitStruct.PLL3.PLL3Q = 2;
    PeriphClkInitStruct.PLL3.PLL3R = 6;
    PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_3;
    PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
    PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOK_CLK_ENABLE();
    __HAL_RCC_GPIOJ_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PK5     ------> LTDC_B6
    PK4     ------> LTDC_B5
    PJ15     ------> LTDC_B3
    PK6     ------> LTDC_B7
    PK3     ------> LTDC_B4
    PK7     ------> LTDC_DE
    PI12     ------> LTDC_HSYNC
    PI13     ------> LTDC_VSYNC
    PI14     ------> LTDC_CLK
    PK2     ------> LTDC_G7
    PK0     ------> LTDC_G5
    PK1     ------> LTDC_G6
    PJ11     ------> LTDC_G4
    PJ10     ------> LTDC_G3
    PJ9     ------> LTDC_G2
    PJ6     ------> LTDC_R7
    PJ5     ------> LTDC_R6
    PJ2     ------> LTDC_R3
    PJ3     ------> LTDC_R4
    PJ4     ------> LTDC_R5
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3
                          |GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9
                          |GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 9, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PK5     ------> LTDC_B6
    PK4     ------> LTDC_B5
    PJ15     ------> LTDC_B3
    PK6     ------> LTDC_B7
    PK3     ------> LTDC_B4
    PK7     ------> LTDC_DE
    PI12     ------> LTDC_HSYNC
    PI13     ------> LTDC_VSYNC
    PI14     ------> LTDC_CLK
    PK2     ------> LTDC_G7
    PK0     ------> LTDC_G5
    PK1     ------> LTDC_G6
    PJ11     ------> LTDC_G4
    PJ10     ------> LTDC_G3
    PJ9     ------> LTDC_G2
    PJ6     ------> LTDC_R7
    PJ5     ------> LTDC_R6
    PJ2     ------> LTDC_R3
    PJ3     ------> LTDC_R4
    PJ4     ------> LTDC_R5
    */
    HAL_GPIO_DeInit(GPIOK, GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3
                          |GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_1);

    HAL_GPIO_DeInit(GPIOJ, GPIO_PIN_15|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9
                          |GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4);

    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14);

    /* LTDC interrupt Deinit */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
#include "delay.h"
//static void LCD_Reset(void)
//{
////注意，现在科学发达，有的屏不用复位也行 
//		LCD_RST(0);
//    LCD_delay(200);					   
//    LCD_RST(1);		 	 
//    LCD_delay(200);	
//}

void LCD_WriteByteSPI(unsigned char byte)
{
    unsigned char n;

    for (n = 0; n < 8; n++)
    {
        if (byte & 0x80)
            HAL_GPIO_WritePin(lcd_spi_sdi_GPIO_Port, lcd_spi_sdi_Pin, GPIO_PIN_SET); //SPI_SDA(1)
        else
            HAL_GPIO_WritePin(lcd_spi_sdi_GPIO_Port, lcd_spi_sdi_Pin, GPIO_PIN_RESET);//SPI_SDA(0)
        byte <<= 1;

        //        SPI_DCLK(0);
        HAL_GPIO_WritePin(lcd_spi_wr_GPIO_Port, lcd_spi_wr_Pin, GPIO_PIN_RESET);
        delay_us(1);
        //        SPI_DCLK(1);
        HAL_GPIO_WritePin(lcd_spi_wr_GPIO_Port, lcd_spi_wr_Pin, GPIO_PIN_SET);
        delay_us(1);
    }
}
void SPI_WriteComm(u16 CMD)
{
    //	LCD_SPI_CS(0);
    HAL_GPIO_WritePin(lcd_spi_cs_GPIO_Port, lcd_spi_cs_Pin, GPIO_PIN_RESET);
    LCD_WriteByteSPI(0X20);
    LCD_WriteByteSPI(CMD >> 8);
    LCD_WriteByteSPI(0X00);
    LCD_WriteByteSPI(CMD);

    //	LCD_SPI_CS(1);
    HAL_GPIO_WritePin(lcd_spi_cs_GPIO_Port, lcd_spi_cs_Pin, GPIO_PIN_SET);
}
void SPI_WriteData(u16 tem_data)
{
    //	LCD_SPI_CS(0);
    HAL_GPIO_WritePin(lcd_spi_cs_GPIO_Port, lcd_spi_cs_Pin, GPIO_PIN_RESET);
    LCD_WriteByteSPI(0x40);
    LCD_WriteByteSPI(tem_data);
    //	LCD_SPI_CS(1);

    HAL_GPIO_WritePin(lcd_spi_cs_GPIO_Port, lcd_spi_cs_Pin, GPIO_PIN_SET);
}
void Lcd_Initialize(void)
{
    //    LCD_SPI_CS(1);
    HAL_GPIO_WritePin(lcd_spi_cs_GPIO_Port, lcd_spi_cs_Pin, GPIO_PIN_SET);
    //    LCD_delay(20);
    delay_us(1);
    //    LCD_SPI_CS(0);
    HAL_GPIO_WritePin(lcd_spi_cs_GPIO_Port, lcd_spi_cs_Pin, GPIO_PIN_RESET);
    //    LCD_Reset();
    delay_us(1);

    //ENABLE PAGE 1
    SPI_WriteComm(0xF000); SPI_WriteData(0x55);
    SPI_WriteComm(0xF001); SPI_WriteData(0xAA);
    SPI_WriteComm(0xF002); SPI_WriteData(0x52);
    SPI_WriteComm(0xF003); SPI_WriteData(0x08);
    SPI_WriteComm(0xF004); SPI_WriteData(0x01);

    //GAMMA SETING  RED
    SPI_WriteComm(0xD100); SPI_WriteData(0x00);
    SPI_WriteComm(0xD101); SPI_WriteData(0x00);
    SPI_WriteComm(0xD102); SPI_WriteData(0x1b);
    SPI_WriteComm(0xD103); SPI_WriteData(0x44);
    SPI_WriteComm(0xD104); SPI_WriteData(0x62);
    SPI_WriteComm(0xD105); SPI_WriteData(0x00);
    SPI_WriteComm(0xD106); SPI_WriteData(0x7b);
    SPI_WriteComm(0xD107); SPI_WriteData(0xa1);
    SPI_WriteComm(0xD108); SPI_WriteData(0xc0);
    SPI_WriteComm(0xD109); SPI_WriteData(0xee);
    SPI_WriteComm(0xD10A); SPI_WriteData(0x55);
    SPI_WriteComm(0xD10B); SPI_WriteData(0x10);
    SPI_WriteComm(0xD10C); SPI_WriteData(0x2c);
    SPI_WriteComm(0xD10D); SPI_WriteData(0x43);
    SPI_WriteComm(0xD10E); SPI_WriteData(0x57);
    SPI_WriteComm(0xD10F); SPI_WriteData(0x55);
    SPI_WriteComm(0xD110); SPI_WriteData(0x68);
    SPI_WriteComm(0xD111); SPI_WriteData(0x78);
    SPI_WriteComm(0xD112); SPI_WriteData(0x87);
    SPI_WriteComm(0xD113); SPI_WriteData(0x94);
    SPI_WriteComm(0xD114); SPI_WriteData(0x55);
    SPI_WriteComm(0xD115); SPI_WriteData(0xa0);
    SPI_WriteComm(0xD116); SPI_WriteData(0xac);
    SPI_WriteComm(0xD117); SPI_WriteData(0xb6);
    SPI_WriteComm(0xD118); SPI_WriteData(0xc1);
    SPI_WriteComm(0xD119); SPI_WriteData(0x55);
    SPI_WriteComm(0xD11A); SPI_WriteData(0xcb);
    SPI_WriteComm(0xD11B); SPI_WriteData(0xcd);
    SPI_WriteComm(0xD11C); SPI_WriteData(0xd6);
    SPI_WriteComm(0xD11D); SPI_WriteData(0xdf);
    SPI_WriteComm(0xD11E); SPI_WriteData(0x95);
    SPI_WriteComm(0xD11F); SPI_WriteData(0xe8);
    SPI_WriteComm(0xD120); SPI_WriteData(0xf1);
    SPI_WriteComm(0xD121); SPI_WriteData(0xfa);
    SPI_WriteComm(0xD122); SPI_WriteData(0x02);
    SPI_WriteComm(0xD123); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD124); SPI_WriteData(0x0b);
    SPI_WriteComm(0xD125); SPI_WriteData(0x13);
    SPI_WriteComm(0xD126); SPI_WriteData(0x1d);
    SPI_WriteComm(0xD127); SPI_WriteData(0x26);
    SPI_WriteComm(0xD128); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD129); SPI_WriteData(0x30);
    SPI_WriteComm(0xD12A); SPI_WriteData(0x3c);
    SPI_WriteComm(0xD12B); SPI_WriteData(0x4A);
    SPI_WriteComm(0xD12C); SPI_WriteData(0x63);
    SPI_WriteComm(0xD12D); SPI_WriteData(0xea);
    SPI_WriteComm(0xD12E); SPI_WriteData(0x79);
    SPI_WriteComm(0xD12F); SPI_WriteData(0xa6);
    SPI_WriteComm(0xD130); SPI_WriteData(0xd0);
    SPI_WriteComm(0xD131); SPI_WriteData(0x20);
    SPI_WriteComm(0xD132); SPI_WriteData(0x0f);
    SPI_WriteComm(0xD133); SPI_WriteData(0x8e);
    SPI_WriteComm(0xD134); SPI_WriteData(0xff);
    //GAMMA SETING GREEN
    SPI_WriteComm(0xD200); SPI_WriteData(0x00);
    SPI_WriteComm(0xD201); SPI_WriteData(0x00);
    SPI_WriteComm(0xD202); SPI_WriteData(0x1b);
    SPI_WriteComm(0xD203); SPI_WriteData(0x44);
    SPI_WriteComm(0xD204); SPI_WriteData(0x62);
    SPI_WriteComm(0xD205); SPI_WriteData(0x00);
    SPI_WriteComm(0xD206); SPI_WriteData(0x7b);
    SPI_WriteComm(0xD207); SPI_WriteData(0xa1);
    SPI_WriteComm(0xD208); SPI_WriteData(0xc0);
    SPI_WriteComm(0xD209); SPI_WriteData(0xee);
    SPI_WriteComm(0xD20A); SPI_WriteData(0x55);
    SPI_WriteComm(0xD20B); SPI_WriteData(0x10);
    SPI_WriteComm(0xD20C); SPI_WriteData(0x2c);
    SPI_WriteComm(0xD20D); SPI_WriteData(0x43);
    SPI_WriteComm(0xD20E); SPI_WriteData(0x57);
    SPI_WriteComm(0xD20F); SPI_WriteData(0x55);
    SPI_WriteComm(0xD210); SPI_WriteData(0x68);
    SPI_WriteComm(0xD211); SPI_WriteData(0x78);
    SPI_WriteComm(0xD212); SPI_WriteData(0x87);
    SPI_WriteComm(0xD213); SPI_WriteData(0x94);
    SPI_WriteComm(0xD214); SPI_WriteData(0x55);
    SPI_WriteComm(0xD215); SPI_WriteData(0xa0);
    SPI_WriteComm(0xD216); SPI_WriteData(0xac);
    SPI_WriteComm(0xD217); SPI_WriteData(0xb6);
    SPI_WriteComm(0xD218); SPI_WriteData(0xc1);
    SPI_WriteComm(0xD219); SPI_WriteData(0x55);
    SPI_WriteComm(0xD21A); SPI_WriteData(0xcb);
    SPI_WriteComm(0xD21B); SPI_WriteData(0xcd);
    SPI_WriteComm(0xD21C); SPI_WriteData(0xd6);
    SPI_WriteComm(0xD21D); SPI_WriteData(0xdf);
    SPI_WriteComm(0xD21E); SPI_WriteData(0x95);
    SPI_WriteComm(0xD21F); SPI_WriteData(0xe8);
    SPI_WriteComm(0xD220); SPI_WriteData(0xf1);
    SPI_WriteComm(0xD221); SPI_WriteData(0xfa);
    SPI_WriteComm(0xD222); SPI_WriteData(0x02);
    SPI_WriteComm(0xD223); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD224); SPI_WriteData(0x0b);
    SPI_WriteComm(0xD225); SPI_WriteData(0x13);
    SPI_WriteComm(0xD226); SPI_WriteData(0x1d);
    SPI_WriteComm(0xD227); SPI_WriteData(0x26);
    SPI_WriteComm(0xD228); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD229); SPI_WriteData(0x30);
    SPI_WriteComm(0xD22A); SPI_WriteData(0x3c);
    SPI_WriteComm(0xD22B); SPI_WriteData(0x4a);
    SPI_WriteComm(0xD22C); SPI_WriteData(0x63);
    SPI_WriteComm(0xD22D); SPI_WriteData(0xea);
    SPI_WriteComm(0xD22E); SPI_WriteData(0x79);
    SPI_WriteComm(0xD22F); SPI_WriteData(0xa6);
    SPI_WriteComm(0xD230); SPI_WriteData(0xd0);
    SPI_WriteComm(0xD231); SPI_WriteData(0x20);
    SPI_WriteComm(0xD232); SPI_WriteData(0x0f);
    SPI_WriteComm(0xD233); SPI_WriteData(0x8e);
    SPI_WriteComm(0xD234); SPI_WriteData(0xff);

    //GAMMA SETING BLUE
    SPI_WriteComm(0xD300); SPI_WriteData(0x00);
    SPI_WriteComm(0xD301); SPI_WriteData(0x00);
    SPI_WriteComm(0xD302); SPI_WriteData(0x1b);
    SPI_WriteComm(0xD303); SPI_WriteData(0x44);
    SPI_WriteComm(0xD304); SPI_WriteData(0x62);
    SPI_WriteComm(0xD305); SPI_WriteData(0x00);
    SPI_WriteComm(0xD306); SPI_WriteData(0x7b);
    SPI_WriteComm(0xD307); SPI_WriteData(0xa1);
    SPI_WriteComm(0xD308); SPI_WriteData(0xc0);
    SPI_WriteComm(0xD309); SPI_WriteData(0xee);
    SPI_WriteComm(0xD30A); SPI_WriteData(0x55);
    SPI_WriteComm(0xD30B); SPI_WriteData(0x10);
    SPI_WriteComm(0xD30C); SPI_WriteData(0x2c);
    SPI_WriteComm(0xD30D); SPI_WriteData(0x43);
    SPI_WriteComm(0xD30E); SPI_WriteData(0x57);
    SPI_WriteComm(0xD30F); SPI_WriteData(0x55);
    SPI_WriteComm(0xD310); SPI_WriteData(0x68);
    SPI_WriteComm(0xD311); SPI_WriteData(0x78);
    SPI_WriteComm(0xD312); SPI_WriteData(0x87);
    SPI_WriteComm(0xD313); SPI_WriteData(0x94);
    SPI_WriteComm(0xD314); SPI_WriteData(0x55);
    SPI_WriteComm(0xD315); SPI_WriteData(0xa0);
    SPI_WriteComm(0xD316); SPI_WriteData(0xac);
    SPI_WriteComm(0xD317); SPI_WriteData(0xb6);
    SPI_WriteComm(0xD318); SPI_WriteData(0xc1);
    SPI_WriteComm(0xD319); SPI_WriteData(0x55);
    SPI_WriteComm(0xD31A); SPI_WriteData(0xcb);
    SPI_WriteComm(0xD31B); SPI_WriteData(0xcd);
    SPI_WriteComm(0xD31C); SPI_WriteData(0xd6);
    SPI_WriteComm(0xD31D); SPI_WriteData(0xdf);
    SPI_WriteComm(0xD31E); SPI_WriteData(0x95);
    SPI_WriteComm(0xD31F); SPI_WriteData(0xe8);
    SPI_WriteComm(0xD320); SPI_WriteData(0xf1);
    SPI_WriteComm(0xD321); SPI_WriteData(0xfa);
    SPI_WriteComm(0xD322); SPI_WriteData(0x02);
    SPI_WriteComm(0xD323); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD324); SPI_WriteData(0x0b);
    SPI_WriteComm(0xD325); SPI_WriteData(0x13);
    SPI_WriteComm(0xD326); SPI_WriteData(0x1d);
    SPI_WriteComm(0xD327); SPI_WriteData(0x26);
    SPI_WriteComm(0xD328); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD329); SPI_WriteData(0x30);
    SPI_WriteComm(0xD32A); SPI_WriteData(0x3c);
    SPI_WriteComm(0xD32B); SPI_WriteData(0x4A);
    SPI_WriteComm(0xD32C); SPI_WriteData(0x63);
    SPI_WriteComm(0xD32D); SPI_WriteData(0xea);
    SPI_WriteComm(0xD32E); SPI_WriteData(0x79);
    SPI_WriteComm(0xD32F); SPI_WriteData(0xa6);
    SPI_WriteComm(0xD330); SPI_WriteData(0xd0);
    SPI_WriteComm(0xD331); SPI_WriteData(0x20);
    SPI_WriteComm(0xD332); SPI_WriteData(0x0f);
    SPI_WriteComm(0xD333); SPI_WriteData(0x8e);
    SPI_WriteComm(0xD334); SPI_WriteData(0xff);


    //GAMMA SETING  RED
    SPI_WriteComm(0xD400); SPI_WriteData(0x00);
    SPI_WriteComm(0xD401); SPI_WriteData(0x00);
    SPI_WriteComm(0xD402); SPI_WriteData(0x1b);
    SPI_WriteComm(0xD403); SPI_WriteData(0x44);
    SPI_WriteComm(0xD404); SPI_WriteData(0x62);
    SPI_WriteComm(0xD405); SPI_WriteData(0x00);
    SPI_WriteComm(0xD406); SPI_WriteData(0x7b);
    SPI_WriteComm(0xD407); SPI_WriteData(0xa1);
    SPI_WriteComm(0xD408); SPI_WriteData(0xc0);
    SPI_WriteComm(0xD409); SPI_WriteData(0xee);
    SPI_WriteComm(0xD40A); SPI_WriteData(0x55);
    SPI_WriteComm(0xD40B); SPI_WriteData(0x10);
    SPI_WriteComm(0xD40C); SPI_WriteData(0x2c);
    SPI_WriteComm(0xD40D); SPI_WriteData(0x43);
    SPI_WriteComm(0xD40E); SPI_WriteData(0x57);
    SPI_WriteComm(0xD40F); SPI_WriteData(0x55);
    SPI_WriteComm(0xD410); SPI_WriteData(0x68);
    SPI_WriteComm(0xD411); SPI_WriteData(0x78);
    SPI_WriteComm(0xD412); SPI_WriteData(0x87);
    SPI_WriteComm(0xD413); SPI_WriteData(0x94);
    SPI_WriteComm(0xD414); SPI_WriteData(0x55);
    SPI_WriteComm(0xD415); SPI_WriteData(0xa0);
    SPI_WriteComm(0xD416); SPI_WriteData(0xac);
    SPI_WriteComm(0xD417); SPI_WriteData(0xb6);
    SPI_WriteComm(0xD418); SPI_WriteData(0xc1);
    SPI_WriteComm(0xD419); SPI_WriteData(0x55);
    SPI_WriteComm(0xD41A); SPI_WriteData(0xcb);
    SPI_WriteComm(0xD41B); SPI_WriteData(0xcd);
    SPI_WriteComm(0xD41C); SPI_WriteData(0xd6);
    SPI_WriteComm(0xD41D); SPI_WriteData(0xdf);
    SPI_WriteComm(0xD41E); SPI_WriteData(0x95);
    SPI_WriteComm(0xD41F); SPI_WriteData(0xe8);
    SPI_WriteComm(0xD420); SPI_WriteData(0xf1);
    SPI_WriteComm(0xD421); SPI_WriteData(0xfa);
    SPI_WriteComm(0xD422); SPI_WriteData(0x02);
    SPI_WriteComm(0xD423); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD424); SPI_WriteData(0x0b);
    SPI_WriteComm(0xD425); SPI_WriteData(0x13);
    SPI_WriteComm(0xD426); SPI_WriteData(0x1d);
    SPI_WriteComm(0xD427); SPI_WriteData(0x26);
    SPI_WriteComm(0xD428); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD429); SPI_WriteData(0x30);
    SPI_WriteComm(0xD42A); SPI_WriteData(0x3c);
    SPI_WriteComm(0xD42B); SPI_WriteData(0x4A);
    SPI_WriteComm(0xD42C); SPI_WriteData(0x63);
    SPI_WriteComm(0xD42D); SPI_WriteData(0xea);
    SPI_WriteComm(0xD42E); SPI_WriteData(0x79);
    SPI_WriteComm(0xD42F); SPI_WriteData(0xa6);
    SPI_WriteComm(0xD430); SPI_WriteData(0xd0);
    SPI_WriteComm(0xD431); SPI_WriteData(0x20);
    SPI_WriteComm(0xD432); SPI_WriteData(0x0f);
    SPI_WriteComm(0xD433); SPI_WriteData(0x8e);
    SPI_WriteComm(0xD434); SPI_WriteData(0xff);

    //GAMMA SETING GREEN
    SPI_WriteComm(0xD500); SPI_WriteData(0x00);
    SPI_WriteComm(0xD501); SPI_WriteData(0x00);
    SPI_WriteComm(0xD502); SPI_WriteData(0x1b);
    SPI_WriteComm(0xD503); SPI_WriteData(0x44);
    SPI_WriteComm(0xD504); SPI_WriteData(0x62);
    SPI_WriteComm(0xD505); SPI_WriteData(0x00);
    SPI_WriteComm(0xD506); SPI_WriteData(0x7b);
    SPI_WriteComm(0xD507); SPI_WriteData(0xa1);
    SPI_WriteComm(0xD508); SPI_WriteData(0xc0);
    SPI_WriteComm(0xD509); SPI_WriteData(0xee);
    SPI_WriteComm(0xD50A); SPI_WriteData(0x55);
    SPI_WriteComm(0xD50B); SPI_WriteData(0x10);
    SPI_WriteComm(0xD50C); SPI_WriteData(0x2c);
    SPI_WriteComm(0xD50D); SPI_WriteData(0x43);
    SPI_WriteComm(0xD50E); SPI_WriteData(0x57);
    SPI_WriteComm(0xD50F); SPI_WriteData(0x55);
    SPI_WriteComm(0xD510); SPI_WriteData(0x68);
    SPI_WriteComm(0xD511); SPI_WriteData(0x78);
    SPI_WriteComm(0xD512); SPI_WriteData(0x87);
    SPI_WriteComm(0xD513); SPI_WriteData(0x94);
    SPI_WriteComm(0xD514); SPI_WriteData(0x55);
    SPI_WriteComm(0xD515); SPI_WriteData(0xa0);
    SPI_WriteComm(0xD516); SPI_WriteData(0xac);
    SPI_WriteComm(0xD517); SPI_WriteData(0xb6);
    SPI_WriteComm(0xD518); SPI_WriteData(0xc1);
    SPI_WriteComm(0xD519); SPI_WriteData(0x55);
    SPI_WriteComm(0xD51A); SPI_WriteData(0xcb);
    SPI_WriteComm(0xD51B); SPI_WriteData(0xcd);
    SPI_WriteComm(0xD51C); SPI_WriteData(0xd6);
    SPI_WriteComm(0xD51D); SPI_WriteData(0xdf);
    SPI_WriteComm(0xD51E); SPI_WriteData(0x95);
    SPI_WriteComm(0xD51F); SPI_WriteData(0xe8);
    SPI_WriteComm(0xD520); SPI_WriteData(0xf1);
    SPI_WriteComm(0xD521); SPI_WriteData(0xfa);
    SPI_WriteComm(0xD522); SPI_WriteData(0x02);
    SPI_WriteComm(0xD523); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD524); SPI_WriteData(0x0b);
    SPI_WriteComm(0xD525); SPI_WriteData(0x13);
    SPI_WriteComm(0xD526); SPI_WriteData(0x1d);
    SPI_WriteComm(0xD527); SPI_WriteData(0x26);
    SPI_WriteComm(0xD528); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD529); SPI_WriteData(0x30);
    SPI_WriteComm(0xD52A); SPI_WriteData(0x3c);
    SPI_WriteComm(0xD52B); SPI_WriteData(0x4a);
    SPI_WriteComm(0xD52C); SPI_WriteData(0x63);
    SPI_WriteComm(0xD52D); SPI_WriteData(0xea);
    SPI_WriteComm(0xD52E); SPI_WriteData(0x79);
    SPI_WriteComm(0xD52F); SPI_WriteData(0xa6);
    SPI_WriteComm(0xD530); SPI_WriteData(0xd0);
    SPI_WriteComm(0xD531); SPI_WriteData(0x20);
    SPI_WriteComm(0xD532); SPI_WriteData(0x0f);
    SPI_WriteComm(0xD533); SPI_WriteData(0x8e);
    SPI_WriteComm(0xD534); SPI_WriteData(0xff);

    //GAMMA SETING BLUE
    SPI_WriteComm(0xD600); SPI_WriteData(0x00);
    SPI_WriteComm(0xD601); SPI_WriteData(0x00);
    SPI_WriteComm(0xD602); SPI_WriteData(0x1b);
    SPI_WriteComm(0xD603); SPI_WriteData(0x44);
    SPI_WriteComm(0xD604); SPI_WriteData(0x62);
    SPI_WriteComm(0xD605); SPI_WriteData(0x00);
    SPI_WriteComm(0xD606); SPI_WriteData(0x7b);
    SPI_WriteComm(0xD607); SPI_WriteData(0xa1);
    SPI_WriteComm(0xD608); SPI_WriteData(0xc0);
    SPI_WriteComm(0xD609); SPI_WriteData(0xee);
    SPI_WriteComm(0xD60A); SPI_WriteData(0x55);
    SPI_WriteComm(0xD60B); SPI_WriteData(0x10);
    SPI_WriteComm(0xD60C); SPI_WriteData(0x2c);
    SPI_WriteComm(0xD60D); SPI_WriteData(0x43);
    SPI_WriteComm(0xD60E); SPI_WriteData(0x57);
    SPI_WriteComm(0xD60F); SPI_WriteData(0x55);
    SPI_WriteComm(0xD610); SPI_WriteData(0x68);
    SPI_WriteComm(0xD611); SPI_WriteData(0x78);
    SPI_WriteComm(0xD612); SPI_WriteData(0x87);
    SPI_WriteComm(0xD613); SPI_WriteData(0x94);
    SPI_WriteComm(0xD614); SPI_WriteData(0x55);
    SPI_WriteComm(0xD615); SPI_WriteData(0xa0);
    SPI_WriteComm(0xD616); SPI_WriteData(0xac);
    SPI_WriteComm(0xD617); SPI_WriteData(0xb6);
    SPI_WriteComm(0xD618); SPI_WriteData(0xc1);
    SPI_WriteComm(0xD619); SPI_WriteData(0x55);
    SPI_WriteComm(0xD61A); SPI_WriteData(0xcb);
    SPI_WriteComm(0xD61B); SPI_WriteData(0xcd);
    SPI_WriteComm(0xD61C); SPI_WriteData(0xd6);
    SPI_WriteComm(0xD61D); SPI_WriteData(0xdf);
    SPI_WriteComm(0xD61E); SPI_WriteData(0x95);
    SPI_WriteComm(0xD61F); SPI_WriteData(0xe8);
    SPI_WriteComm(0xD620); SPI_WriteData(0xf1);
    SPI_WriteComm(0xD621); SPI_WriteData(0xfa);
    SPI_WriteComm(0xD622); SPI_WriteData(0x02);
    SPI_WriteComm(0xD623); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD624); SPI_WriteData(0x0b);
    SPI_WriteComm(0xD625); SPI_WriteData(0x13);
    SPI_WriteComm(0xD626); SPI_WriteData(0x1d);
    SPI_WriteComm(0xD627); SPI_WriteData(0x26);
    SPI_WriteComm(0xD628); SPI_WriteData(0xaa);
    SPI_WriteComm(0xD629); SPI_WriteData(0x30);
    SPI_WriteComm(0xD62A); SPI_WriteData(0x3c);
    SPI_WriteComm(0xD62B); SPI_WriteData(0x4A);
    SPI_WriteComm(0xD62C); SPI_WriteData(0x63);
    SPI_WriteComm(0xD62D); SPI_WriteData(0xea);
    SPI_WriteComm(0xD62E); SPI_WriteData(0x79);
    SPI_WriteComm(0xD62F); SPI_WriteData(0xa6);
    SPI_WriteComm(0xD630); SPI_WriteData(0xd0);
    SPI_WriteComm(0xD631); SPI_WriteData(0x20);
    SPI_WriteComm(0xD632); SPI_WriteData(0x0f);
    SPI_WriteComm(0xD633); SPI_WriteData(0x8e);
    SPI_WriteComm(0xD634); SPI_WriteData(0xff);

    //AVDD VOLTAGE SETTING
    SPI_WriteComm(0xB000); SPI_WriteData(0x05);
    SPI_WriteComm(0xB001); SPI_WriteData(0x05);
    SPI_WriteComm(0xB002); SPI_WriteData(0x05);
    //AVEE VOLTAGE SETTING
    SPI_WriteComm(0xB100); SPI_WriteData(0x05);
    SPI_WriteComm(0xB101); SPI_WriteData(0x05);
    SPI_WriteComm(0xB102); SPI_WriteData(0x05);

    //AVDD Boosting
    SPI_WriteComm(0xB600); SPI_WriteData(0x34);
    SPI_WriteComm(0xB601); SPI_WriteData(0x34);
    SPI_WriteComm(0xB603); SPI_WriteData(0x34);
    //AVEE Boosting
    SPI_WriteComm(0xB700); SPI_WriteData(0x24);
    SPI_WriteComm(0xB701); SPI_WriteData(0x24);
    SPI_WriteComm(0xB702); SPI_WriteData(0x24);
    //VCL Boosting
    SPI_WriteComm(0xB800); SPI_WriteData(0x24);
    SPI_WriteComm(0xB801); SPI_WriteData(0x24);
    SPI_WriteComm(0xB802); SPI_WriteData(0x24);
    //VGLX VOLTAGE SETTING
    SPI_WriteComm(0xBA00); SPI_WriteData(0x14);
    SPI_WriteComm(0xBA01); SPI_WriteData(0x14);
    SPI_WriteComm(0xBA02); SPI_WriteData(0x14);
    //VCL Boosting
    SPI_WriteComm(0xB900); SPI_WriteData(0x24);
    SPI_WriteComm(0xB901); SPI_WriteData(0x24);
    SPI_WriteComm(0xB902); SPI_WriteData(0x24);
    //Gamma Voltage
    SPI_WriteComm(0xBc00); SPI_WriteData(0x00);
    SPI_WriteComm(0xBc01); SPI_WriteData(0xa0);//vgmp=5.0
    SPI_WriteComm(0xBc02); SPI_WriteData(0x00);
    SPI_WriteComm(0xBd00); SPI_WriteData(0x00);
    SPI_WriteComm(0xBd01); SPI_WriteData(0xa0);//vgmn=5.0
    SPI_WriteComm(0xBd02); SPI_WriteData(0x00);
    //VCOM Setting
    SPI_WriteComm(0xBe01); SPI_WriteData(0x3d);//3
    //ENABLE PAGE 0
    SPI_WriteComm(0xF000); SPI_WriteData(0x55);
    SPI_WriteComm(0xF001); SPI_WriteData(0xAA);
    SPI_WriteComm(0xF002); SPI_WriteData(0x52);
    SPI_WriteComm(0xF003); SPI_WriteData(0x08);
    SPI_WriteComm(0xF004); SPI_WriteData(0x00);
    //Vivid Color Function Control
    SPI_WriteComm(0xB400); SPI_WriteData(0x10);
    //Z-INVERSION
    SPI_WriteComm(0xBC00); SPI_WriteData(0x05);
    SPI_WriteComm(0xBC01); SPI_WriteData(0x05);
    SPI_WriteComm(0xBC02); SPI_WriteData(0x05);

    //*************** add on 20111021**********************//
    SPI_WriteComm(0xB700); SPI_WriteData(0x22);//GATE EQ CONTROL
    SPI_WriteComm(0xB701); SPI_WriteData(0x22);//GATE EQ CONTROL

    SPI_WriteComm(0xC80B); SPI_WriteData(0x2A);//DISPLAY TIMING CONTROL
    SPI_WriteComm(0xC80C); SPI_WriteData(0x2A);//DISPLAY TIMING CONTROL
    SPI_WriteComm(0xC80F); SPI_WriteData(0x2A);//DISPLAY TIMING CONTROL
    SPI_WriteComm(0xC810); SPI_WriteData(0x2A);//DISPLAY TIMING CONTROL
    //*************** add on 20111021**********************//
    //PWM_ENH_OE =1
    SPI_WriteComm(0xd000); SPI_WriteData(0x01);
    //DM_SEL =1
    SPI_WriteComm(0xb300); SPI_WriteData(0x10);
    //VBPDA=07h
    SPI_WriteComm(0xBd02); SPI_WriteData(0x07);
    //VBPDb=07h
    SPI_WriteComm(0xBe02); SPI_WriteData(0x07);
    //VBPDc=07h
    SPI_WriteComm(0xBf02); SPI_WriteData(0x07);
    //ENABLE PAGE 2
    SPI_WriteComm(0xF000); SPI_WriteData(0x55);
    SPI_WriteComm(0xF001); SPI_WriteData(0xAA);
    SPI_WriteComm(0xF002); SPI_WriteData(0x52);
    SPI_WriteComm(0xF003); SPI_WriteData(0x08);
    SPI_WriteComm(0xF004); SPI_WriteData(0x02);
    //SDREG0 =0
    SPI_WriteComm(0xc301); SPI_WriteData(0xa9);
    //DS=14
    SPI_WriteComm(0xfe01); SPI_WriteData(0x94);
    //OSC =60h
    SPI_WriteComm(0xf600); SPI_WriteData(0x60);
    //TE ON
    SPI_WriteComm(0x3500); SPI_WriteData(0x00);

    //0 8 4 C     2 A 6 E
    SPI_WriteComm(0x3600); SPI_WriteData(0x00C0);
    SPI_WriteComm(0x1100);
    //LCD_delay(120);
    delay_us(120);

    SPI_WriteComm(0x2900);

    SPI_WriteComm(0x2c00);
    SPI_WriteComm(0x3c00);
}
/* USER CODE END 1 */
