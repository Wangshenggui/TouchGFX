/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "Radio.h"

#include "adc.h"
#include "my_adc.h"
#include "iwdg.h"
#include "rtc.h"

#include "InfoNES.h"
#include "ltdc.h"

#include "ft5206.h"
TouchTypedef mtouch;

#include "InfoNES.h"
#include "InfoNES_System.h"
#include "InfoNES_Mapper.h"
#include "InfoNES_pAPU.h"
#include "K6502.h"
#include "ltdc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "usbd_storage.h"

#include "usmart.h"

#include "InfoNES.h"
#include "InfoNES.h"
#include "InfoNES_System.h"
#include "InfoNES_Mapper.h"
#include "InfoNES_pAPU.h"
#include "K6502.h"
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */



extern uint32_t g_osRuntimeCounter;
extern char g_tasks_buf[512]; //用于存放显示数据
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
EventGroupHandle_t IWDG_Event;//创建事件组句柄
/* USER CODE END Variables */
osThreadId touchGFXHandle;
osThreadId GUI_MesProcessHandle;
osThreadId SendContGUIMessHandle;
osThreadId IwdgTaskHandle;
osThreadId PerDataProcess_Handle;
osMessageQId USB_StateQueueHandle;
osMessageQId GUI_ControlTaskQueueHandle;
osMessageQId Task_ControlGUIQueueHandle;
osSemaphoreId RadioUART_BinSemHandle;
osSemaphoreId RenCPUTempBinSemHandle;
osSemaphoreId UpRadioDatBinSemHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TouchGFX_Task(void const * argument);
void GUI_MesProcess_Task(void const * argument);
void SendContGUIMess_Task(void const * argument);
void StartIwdgTask(void const * argument);
void PerDataProcess_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);
void vApplicationIdleHook(void);
void vApplicationTickHook(void);

/* USER CODE BEGIN 1 */
void debugShowOSTasksLists(void);

void debugShowOSTasksRunTimeStats(void);



void debugShowOSTasksLists(void)
{
#if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) )

    memset(g_tasks_buf, 0, 512);

    strcat((char*)g_tasks_buf, "\r\n任务名称 运行状态 优先级 剩余堆栈 任务序号\r\n");

    strcat((char*)g_tasks_buf, "---------------------------------------------\r\n");

    /* The list of tasks and their status */

    //osThreadList ((char *)(g_tasks_buf + strlen(g_tasks_buf)));

    vTaskList((char*)(g_tasks_buf + strlen(g_tasks_buf)));

    strcat((char*)g_tasks_buf, "---------------------------------------------\r\n");

    //strcat((char *)g_tasks_buf, "B : Blocked, R : Ready, D : Deleted, S : Suspended\r\n");

    strcat((char*)g_tasks_buf, "B : 阻塞, R : 就绪, D : 删除, S : 暂停\r\n");

    //UART1SendLen((uint8_t*)g_tasks_buf, strlen(g_tasks_buf));
    printf("%s\r\n", g_tasks_buf);
#endif

}

void debugShowOSTasksRunTimeStats(void)
{
#if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) )

    memset(g_tasks_buf, 0, 512);

    strcat((char*)g_tasks_buf, "\r\n任务名称\t运行计数\t使用率\r\n");

    strcat((char*)g_tasks_buf, "---------------------------------------------\r\n");

    /* displays the amount of time each task has spent in the Running state

    * in both absolute and percentage terms. */

    vTaskGetRunTimeStats((char*)(g_tasks_buf + strlen(g_tasks_buf)));

    strcat((char*)g_tasks_buf, "---------------------------------------------\r\n");

    //UART1SendLen((uint8_t*)g_tasks_buf, strlen(g_tasks_buf));
    printf("%s\r\n", g_tasks_buf);
#endif

}
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
    g_osRuntimeCounter = 0;
}

__weak unsigned long getRunTimeCounterValue(void)
{
    return g_osRuntimeCounter;
}
/* USER CODE END 1 */

/* USER CODE BEGIN 2 */
#define CPU_USAGE_CALC_TICK 100
#define CPU_USAGE_LOOP      100

__weak void vApplicationIdleHook(void)
{
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
    task. It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()). If the application makes use of the
    vTaskDelete() API function (as this demo application does) then it is also
    important that vApplicationIdleHook() is permitted to return to its calling
    function, because it is the responsibility of the idle task to clean up
    memory allocated by the kernel to any task that has since been deleted. */

    unsigned int tick;
    unsigned int count;
    volatile unsigned int loop;

    if (MAIN_FREERTOS_GlobalVariableStruct.total_count == 0)
    {
        vTaskSuspendAll();
        tick = HAL_GetTick();

        while (HAL_GetTick() - tick < CPU_USAGE_CALC_TICK)
        {
            MAIN_FREERTOS_GlobalVariableStruct.total_count++;
            loop = 0;
            while (loop < CPU_USAGE_LOOP)loop++;
        }
        xTaskResumeAll();
    }

    count = 0;
    tick = HAL_GetTick();

    while (HAL_GetTick() - tick < CPU_USAGE_CALC_TICK)
    {
        count++;
        loop = 0;
        while (loop < CPU_USAGE_LOOP)loop++;
    }

    if (count < MAIN_FREERTOS_GlobalVariableStruct.total_count)
    {
        count = MAIN_FREERTOS_GlobalVariableStruct.total_count - count;
        MAIN_FREERTOS_GlobalVariableStruct.cpu_usage = (count * 100) / MAIN_FREERTOS_GlobalVariableStruct.total_count;
    }
    else
    {
        MAIN_FREERTOS_GlobalVariableStruct.total_count = count;
        MAIN_FREERTOS_GlobalVariableStruct.cpu_usage = 0;
    }
}
/* USER CODE END 2 */

/* USER CODE BEGIN 3 */
__weak void vApplicationTickHook(void)
{
    /* This function will be called by each tick interrupt if
    configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
    added here, but the tick hook is called from an interrupt context, so
    code must not attempt to block, and only the interrupt safe FreeRTOS API
    functions can be used (those that end in FromISR()). */
}
/* USER CODE END 3 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer, uint32_t* pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
    IWDG_Event = xEventGroupCreate(); //创建事件组
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
              /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of RadioUART_BinSem */
  osSemaphoreDef(RadioUART_BinSem);
  RadioUART_BinSemHandle = osSemaphoreCreate(osSemaphore(RadioUART_BinSem), 1);

  /* definition and creation of RenCPUTempBinSem */
  osSemaphoreDef(RenCPUTempBinSem);
  RenCPUTempBinSemHandle = osSemaphoreCreate(osSemaphore(RenCPUTempBinSem), 1);

  /* definition and creation of UpRadioDatBinSem */
  osSemaphoreDef(UpRadioDatBinSem);
  UpRadioDatBinSemHandle = osSemaphoreCreate(osSemaphore(UpRadioDatBinSem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
              /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
              /* start timers, add new ones, ... */

  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of USB_StateQueue */
  osMessageQDef(USB_StateQueue, 16, uint8_t);
  USB_StateQueueHandle = osMessageCreate(osMessageQ(USB_StateQueue), NULL);

  /* definition and creation of GUI_ControlTaskQueue */
  osMessageQDef(GUI_ControlTaskQueue, 16, uint8_t);
  GUI_ControlTaskQueueHandle = osMessageCreate(osMessageQ(GUI_ControlTaskQueue), NULL);

  /* definition and creation of Task_ControlGUIQueue */
  osMessageQDef(Task_ControlGUIQueue, 16, uint8_t);
  Task_ControlGUIQueueHandle = osMessageCreate(osMessageQ(Task_ControlGUIQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
              /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of touchGFX */
  osThreadDef(touchGFX, TouchGFX_Task, osPriorityHigh, 0, 4096);
  touchGFXHandle = osThreadCreate(osThread(touchGFX), NULL);

  /* definition and creation of GUI_MesProcess */
  osThreadDef(GUI_MesProcess, GUI_MesProcess_Task, osPriorityRealtime, 0, 1024);
  GUI_MesProcessHandle = osThreadCreate(osThread(GUI_MesProcess), NULL);

  /* definition and creation of SendContGUIMess */
  osThreadDef(SendContGUIMess, SendContGUIMess_Task, osPriorityNormal, 0, 256);
  SendContGUIMessHandle = osThreadCreate(osThread(SendContGUIMess), NULL);

  /* definition and creation of IwdgTask */
  osThreadDef(IwdgTask, StartIwdgTask, osPriorityIdle, 0, 128);
  IwdgTaskHandle = osThreadCreate(osThread(IwdgTask), NULL);

  /* definition and creation of PerDataProcess_ */
  osThreadDef(PerDataProcess_, PerDataProcess_Task, osPriorityAboveNormal, 0, 256);
  PerDataProcess_Handle = osThreadCreate(osThread(PerDataProcess_), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
              /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_TouchGFX_Task */

/**
  * @brief  Function implementing the touchGFX thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TouchGFX_Task */
__weak void TouchGFX_Task(void const * argument)
{
  /* USER CODE BEGIN TouchGFX_Task */

        /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
  /* USER CODE END TouchGFX_Task */
}

/* USER CODE BEGIN Header_GUI_MesProcess_Task */
/**
* @brief Function implementing the GUI_MesProcess thread.
* @param argument: Not used
* @retval None
*/
u8 key_data=0;

#include "rtc.h"
RTC_TimeTypeDef Time;

u8 falg_scankey=0;

uint8_t button_key;
/* USER CODE END Header_GUI_MesProcess_Task */
void GUI_MesProcess_Task(void const * argument)
{
  /* USER CODE BEGIN GUI_MesProcess_Task */
    osEvent event;
    /* Infinite loop */
    for (;;)
    {
        //标记事件组
        xEventGroupSetBits(IWDG_Event, IWDG_Event_2);
        osDelay(10);

        //GUI消息队列
        event = osMessageGet(GUI_ControlTaskQueueHandle, 0);
        if (event.status == osEventMessage)
        {
            if (event.value.v == GUIConTaskQueFanON)
            {
                printf("打开风扇\r\n");
                HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
            }
            else if (event.value.v == GUIConTaskQueFanOFF)
            {
                printf("关闭风扇\r\n");
                HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
            }
            //NES
            else if (event.value.v == GUIConTaskQueNESStart)
            {
                MX_LTDC_Init();
                
                #include "voice.h"
                VoicePlayback(2);
                osDelay(50);
                VoicePlayback(2);
                osDelay(50);
                VoicePlayback(2);
                osDelay(50);
                
                //初始化触摸屏
                FT5206_Init();
                mtouch.dir = 1;
                mtouch.pix_h = 800;
                mtouch.pix_w = 480;
                
                if(InfoNES_Load(NULL)==0)
                {
                    // Initialize InfoNES
                    InfoNES_Init();
                }
                while(1)
                {
                    if ( InfoNES_Menu() == -1 )
                        break;  // Quit
                    
                    
                    int nStep;

                    // Set a flag if a scanning line is a hit in the sprite #0
                    if ( SpriteJustHit == PPU_Scanline &&
                      PPU_ScanTable[ PPU_Scanline ] == SCAN_ON_SCREEN )
                    {
                      // # of Steps to execute before sprite #0 hit
                      nStep = JustHitStep[SPRRAM[ SPR_X ]];

                      // Execute instructions
                      K6502_Step( nStep );

                      // Set a sprite hit flag
                      if ( ( PPU_R1 & R1_SHOW_SP ) && ( PPU_R1 & R1_SHOW_SCR ) )
                        PPU_R2 |= R2_HIT_SP;

                      // NMI is required if there is necessity
                      if ( ( PPU_R0 & R0_NMI_SP ) && ( PPU_R1 & R1_SHOW_SP ) )
                        NMI_REQ;

                      // Execute instructions
                      K6502_Step( STEP_PER_SCANLINE - nStep );
                    }
                    else
                    {
                      // Execute instructions
                      K6502_Step( STEP_PER_SCANLINE );
                    }

                    // Frame IRQ in H-Sync
                    FrameStep += STEP_PER_SCANLINE;
                    if ( FrameStep > STEP_PER_FRAME && FrameIRQ_Enable )
                    {
                      FrameStep %= STEP_PER_FRAME;
                      IRQ_REQ;
                #ifndef APU_NONE
                      APU_Reg[ 0x4015 ] |= 0x40;
                #endif /* APU_NONE */
                    }

                    // A mapper function in H-Sync
                    MapperHSync();
                    
                    // A function in H-Sync
                    if ( InfoNES_HSync() == -1 )
                      return;  // To the menu screen

                    // HSYNC Wait
                    InfoNES_Wait();
                    
                    static uint16_t n=0;
                    
                    if(n++==1000)
                    {
                        n=0;
                        
                        falg_scankey=1;
                        
                        button_key = ft5206_scan(&mtouch);
                        if(button_key == 5)
                        {
                            goto TEST;
                        }
                        //播放音乐
                        if(button_key == 4)
                            VoicePlayback(2);
                    }
                    
                }
            }
            
            TEST:


            HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BCD);
            RTC_DateTypeDef Data;
            HAL_RTC_GetDate(&hrtc, &Data, RTC_FORMAT_BCD);

            //            RTC_Bcd2ToByte(Time.Hours);
            //            printf("时间:%d:%d:%d\r\n",
            //                RTC_Bcd2ToByte(Time.Hours),RTC_Bcd2ToByte(Time.Minutes),RTC_Bcd2ToByte(Time.Seconds));
            //            printf("日期:%d:%d:%d\r\n",
            //                RTC_Bcd2ToByte(Data.Year),RTC_Bcd2ToByte(Data.Month),RTC_Bcd2ToByte(Data.Date));
        }
    }
  /* USER CODE END GUI_MesProcess_Task */
}

/* USER CODE BEGIN Header_SendContGUIMess_Task */
/**
* @brief Function implementing the SendContGUIMess thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SendContGUIMess_Task */
void SendContGUIMess_Task(void const * argument)
{
  /* USER CODE BEGIN SendContGUIMess_Task */
    uint16_t t = 0;
    /* Infinite loop */
    for (;;)
    {
        //标记事件组
        xEventGroupSetBits(IWDG_Event, IWDG_Event_3);
        osDelay(10);

        //CPU
        if (osOK == osSemaphoreWait(RenCPUTempBinSemHandle, 0))
        {
            //查看任务情况
            //debugShowOSTasksLists();
            //发送温度更新消息
            osMessagePut(Task_ControlGUIQueueHandle, TaskConGUIQueRenTemp, 0);
        }
        //无线电
        if (osOK == osSemaphoreWait(UpRadioDatBinSemHandle, 0))
        {
            //发送无线电更新消息
            osMessagePut(Task_ControlGUIQueueHandle, TaskConGUIQueUpRadio, 0);
        }

        if (t++ % 50 == 0)
        {
            HAL_GPIO_TogglePin(led_red_GPIO_Port, led_red_Pin);
        }
    }
  /* USER CODE END SendContGUIMess_Task */
}

/* USER CODE BEGIN Header_StartIwdgTask */
/**
* @brief Function implementing the IwdgTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartIwdgTask */
void StartIwdgTask(void const * argument)
{
  /* USER CODE BEGIN StartIwdgTask */
//    hiwdg1.Instance = IWDG1;
//    hiwdg1.Init.Prescaler = IWDG_PRESCALER_32;
//    hiwdg1.Init.Window = 4000;
//    hiwdg1.Init.Reload = 4000;
//    if (HAL_IWDG_Init(&hiwdg1) != HAL_OK)
//    {
//        Error_Handler();
//    }

    EventBits_t IWDG_EventBits;
    /* Infinite loop */
    for (;;)
    {
        //1.句柄；2.哪些位；3.读完清零；4.全部有效(与逻辑)；5.等待时间
        IWDG_EventBits = xEventGroupWaitBits(IWDG_Event, \
            IWDG_Event_1 | IWDG_Event_2 | IWDG_Event_3 | IWDG_Event_4, \
            pdTRUE, \
            pdTRUE, \
            osWaitForever);

        if ((IWDG_EventBits & (IWDG_Event_1 | IWDG_Event_2 | IWDG_Event_3 | IWDG_Event_4)) \
            == (IWDG_Event_1 | IWDG_Event_2 | IWDG_Event_3 | IWDG_Event_4))
        {
            /* 如果接收完成并且正确 */
            HAL_IWDG_Refresh(&hiwdg1);
        }
        osDelay(10);
    }
  /* USER CODE END StartIwdgTask */
}

/* USER CODE BEGIN Header_PerDataProcess_Task */
/**
* @brief Function implementing the PerDataProcess_ thread.
* @param argument: Not used
* @retval None
*/
uint8_t DateTemp;
/* USER CODE END Header_PerDataProcess_Task */
void PerDataProcess_Task(void const * argument)
{
  /* USER CODE BEGIN PerDataProcess_Task */
    uint16_t t = 0;
    /* Infinite loop */
    for (;;)
    {
        //标记事件组
        xEventGroupSetBits(IWDG_Event, IWDG_Event_4);
        osDelay(10);

        if (osOK == osSemaphoreWait(RadioUART_BinSemHandle, 0))
        {
            //解析无线电状态
            ReadRadioState();
            ParsingUSART();//解析数据

            //校准RTC时间
            RTC_TimeTypeDef sTime = { 0 };
            RTC_DateTypeDef sDate = { 0 };

            RTC_TimeTypeDef Time;
            RTC_DateTypeDef Data;
            HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BCD);

            HAL_RTC_GetDate(&hrtc, &Data, RTC_FORMAT_BCD);

            if (DateTemp != 0 && RTC_Bcd2ToByte(Data.Year) != 0 && RadioStateStru.State)
            {
                /** Initialize RTC and set the Time and Date
                  */
                sTime.Hours = RTC_ByteToBcd2(Radio_GlobalVariableStruct.GPS_Tim[0]);
                sTime.Minutes = RTC_ByteToBcd2(Radio_GlobalVariableStruct.GPS_Tim[1]);
                sTime.Seconds = RTC_ByteToBcd2(Radio_GlobalVariableStruct.GPS_Tim[2]);
                sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
                sTime.StoreOperation = RTC_STOREOPERATION_RESET;
                if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
                {
                    Error_Handler();
                }

                sDate.Month = RTC_ByteToBcd2(Radio_GlobalVariableStruct.GPS_Dat[1]);
                sDate.Date = RTC_ByteToBcd2(Radio_GlobalVariableStruct.GPS_Dat[2]);
                sDate.Year = RTC_ByteToBcd2(Radio_GlobalVariableStruct.GPS_Dat[0]);
                if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
                {
                    Error_Handler();
                }
            }
            
            Radio_GlobalVariableStruct.GPS_Tim[0] = RTC_Bcd2ToByte(Time.Hours);
            Radio_GlobalVariableStruct.GPS_Tim[1] = RTC_Bcd2ToByte(Time.Minutes);
            Radio_GlobalVariableStruct.GPS_Tim[2] = RTC_Bcd2ToByte(Time.Seconds);

            RadioRTxStru.DataBuff[34] = RTC_Bcd2ToByte(Data.Year);
            RadioRTxStru.DataBuff[35] = RTC_Bcd2ToByte(Data.Month);
            RadioRTxStru.DataBuff[36] = RTC_Bcd2ToByte(Data.Date);


            osSemaphoreRelease(UpRadioDatBinSemHandle);//释放无线电更新信号量
        }

        if (t++ % 50 == 0)
        {
            //获取CPU温度
            MAIN_FREERTOS_GlobalVariableStruct.CPUtemperature = (uint8_t)GetADC_Temperate();
            osSemaphoreRelease(RenCPUTempBinSemHandle);//释放温度更新信号量
        }
    }
  /* USER CODE END PerDataProcess_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
