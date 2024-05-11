/*-------------------------------------------------------------------*/
/*  InfoNES_system.c                                                 */
/*-------------------------------------------------------------------*/

#include "InfoNES.h"
#include <string.h>
#include <stdio.h>

#include "delay.h"
#include "tim.h"
#include "touch.h"
 
/*-------------------------------------------------------------------*/
/*  Palette data                                                     */
/*-------------------------------------------------------------------*/
WORD NesPalette[64]={
#if 0
  0x738E,0x88C4,0xA800,0x9808,0x7011,0x1015,0x0014,0x004F,
  0x0148,0x0200,0x0280,0x11C0,0x59C3,0x0000,0x0000,0x0000,
  0xBDD7,0xEB80,0xE9C4,0xF010,0xB817,0x581C,0x015B,0x0A59,
  0x0391,0x0480,0x0540,0x3C80,0x8C00,0x0000,0x0000,0x0000,
  0xFFDF,0xFDC7,0xFC8B,0xFC48,0xFBDE,0xB39F,0x639F,0x3CDF,
  0x3DDE,0x1690,0x4EC9,0x9FCB,0xDF40,0x0000,0x0000,0x0000,
  0xFFDF,0xFF15,0xFE98,0xFE5A,0xFE1F,0xDE1F,0xB5DF,0xAEDF,
  0xA71F,0xA7DC,0xBF95,0xCFD6,0xF7D3,0x0000,0x0000,0x0000,
#else 
  0x738E,0x20D1,0x0015,0x4013,0x880E,0xA802,0xA000,0x7840,
  0x4140,0x0200,0x0280,0x01C2,0x19CB,0x0000,0x0000,0x0000,
  0xBDD7,0x039D,0x21DD,0x801E,0xB817,0xE00B,0xD940,0xCA41,
  0x8B80,0x0480,0x0540,0x0487,0x0411,0x0000,0x0000,0x0000,
  0xFFDF,0x3DDF,0x5C9F,0x445F,0xF3DF,0xFB96,0xFB8C,0xFCC7,
  0xF5C7,0x8682,0x4EC9,0x5FD3,0x075B,0x0000,0x0000,0x0000,
  0xFFDF,0xAF1F,0xC69F,0xD65F,0xFE1F,0xFE1B,0xFDD6,0xFED5,
  0xFF14,0xE7D4,0xAF97,0xB7D9,0x9FDE,0x0000,0x0000,0x0000,	
#endif		
};

/*-------------------------------------------------------------------*/
/*  Function prototypes                                              */
/*-------------------------------------------------------------------*/

/* Menu screen */
int InfoNES_Menu()
{
	return 0;
}

/* Read ROM image file */
extern const BYTE nes_rom[];
int InfoNES_ReadRom( const char *pszFileName )
{
/*
 *  Read ROM image file
 *
 *  Parameters
 *    const char *pszFileName          (Read)
 *
 *  Return values
 *     0 : Normally
 *    -1 : Error
 */


  /* Read ROM Header */
  BYTE * rom = (BYTE*)nes_rom;
  memcpy( &NesHeader, rom, sizeof(NesHeader));
  if ( memcmp( NesHeader.byID, "NES\x1a", 4 ) != 0 )
  {
    /* not .nes file */
    return -1;
  }
  rom += sizeof(NesHeader);

  /* Clear SRAM */
  memset( SRAM, 0, SRAM_SIZE );

  /* If trainer presents Read Triner at 0x7000-0x71ff */
  if ( NesHeader.byInfo1 & 4 )
  {
    //memcpy( &SRAM[ 0x1000 ], rom, 512);
	rom += 512;
  }

  /* Allocate Memory for ROM Image */
  ROM = rom;
  rom += NesHeader.byRomSize * 0x4000;

  if ( NesHeader.byVRomSize > 0 )
  {
    /* Allocate Memory for VROM Image */
	VROM = (BYTE*)rom;
	rom += NesHeader.byVRomSize * 0x2000;
  }

  /* Successful */
  return 0;
}

/* Release a memory for ROM */
void InfoNES_ReleaseRom()
{
}

/* Transfer the contents of work frame on the screen */
extern 
void InfoNES_LoadFrame()
{

//	unsigned char buf[20];
 
//	buf[0]= FPS/100%10+0x30; 
//	buf[1]= FPS/10%10+0x30; 	
//	buf[2]= FPS%10+0x30; 
 
//	LCD_ShowString(310,0,200,16,16,buf);
}

 
uint8_t buff__[256*240]={0};

#define LCD_WIDTH       480
#define LCD_HEIGHT      800
#define LCD_FRAME_BUF_ADDR			0xC0000000  
//定义最大屏分辨率时,LCD所需的帧缓存数组大小
uint16_t LCD_FRAME_BUFFER[LCD_WIDTH][LCD_HEIGHT] __attribute__((at(LCD_FRAME_BUF_ADDR)));
extern void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
extern void dma2d_transfer_data_r2m(uint32_t *addr, uint32_t xSize, uint32_t ySize, uint32_t offsetLine, uint16_t color);
/* Transfer the contents of work line on the screen */

void InfoNES_LoadLine()
{
//	int i;
	
//	//若不需要显示帧数，可注释此处代码//
//	if(PPU_Scanline == 0)
//	{
//		FPS_LS++; 
//	}
//	if(flag_over)
//	{
//		flag_over=0;
//		InfoNES_LoadFrame();
//	}
//	////////////////////////////////
  
//	//此处添加自己的LCD刷新函数//
//	LCD_SetCursor(0,PPU_Scanline);
//	LCD_WriteRAM_Prepare();     //开始写入GRAM
//	for(i=0;i<256;i++)
//	{
//	  LCD->LCD_RAM=WorkLine[i];//写入数据 
//	}
//	////////////////////////////////
//    dma2d_transfer_data_r2m();
    
    
    uint32_t pos;
    uint16_t *ptr;


//    for (uint16_t i = 8; i < 248; i++)
//    {
//        pos = i + PPU_Scanline * LCD_WIDTH;
//        ptr = (uint16_t*)LCD_FRAME_BUFFER;
//        *(ptr + pos) = WorkLine[i];


//        pos = i + 799-(PPU_Scanline * LCD_WIDTH);
//        ptr = (uint16_t*)LCD_FRAME_BUFFER;
//        *(ptr + pos) = WorkLine[i];
//    }

    //for (uint16_t i = 8; i < 248; i++)
    //{
    //    pos = (799 - PPU_Scanline - 280) * LCD_WIDTH + 480-i;
    //    ptr = (uint16_t*)LCD_FRAME_BUFFER;
    //    *(ptr+pos) = WorkLine[i];
    //}

    
    
    for(uint16_t i=8;i<248;i++)
    {
        pos = (i-8)*2 + PPU_Scanline*2*LCD_WIDTH;
        ptr = (uint16_t*)LCD_FRAME_BUFFER;
        *(ptr+pos) = WorkLine[i];
        
        pos = (i-8)*2+1 + PPU_Scanline*2*LCD_WIDTH;
        ptr = (uint16_t*)LCD_FRAME_BUFFER;
        *(ptr+pos) = WorkLine[i];
        
        
        pos = (i-8)*2 + (PPU_Scanline*2+1)*LCD_WIDTH;
        ptr = (uint16_t*)LCD_FRAME_BUFFER;
        *(ptr+pos) = WorkLine[i];
        
        pos = (i-8)*2+1 + (PPU_Scanline*2+1)*LCD_WIDTH;
        ptr = (uint16_t*)LCD_FRAME_BUFFER;
        *(ptr+pos) = WorkLine[i];
    }
    
//    for(uint16_t i=0;i<256;i++)
//    {
//        pos = i*2 + PPU_Scanline*2*LCD_WIDTH;
//        ptr = (uint16_t*)LCD_FRAME_BUFFER;
//        *(ptr+pos) = WorkLine[i];
//        
//        pos = i*2+1 + (PPU_Scanline*2+1)*LCD_WIDTH;
//        ptr = (uint16_t*)LCD_FRAME_BUFFER;
//        *(ptr+pos) = WorkLine[i];
//    }
}

/* Get a joypad state */
extern u8 key_data;

#define TP_UP 		0X01
#define TP_DOWN 	0X02
#define TP_LEFT 	0X04
#define TP_RIGHT 	0X08
#define TP_SELECT 	0X10
#define TP_START 	0X20
#define TP_A 		0X40
#define TP_B 		0X80

void InfoNES_PadState( DWORD *pdwPad1, DWORD *pdwPad2, DWORD *pdwSystem )
{
//	static u8 flag=0;
	
	*pdwPad1=0;
//	if(flag)	{*pdwPad1|=PAD_JOY_B;}
	if(key_data)
	{
		if(key_data&TP_UP)		*pdwPad1|=PAD_JOY_A;
		if(key_data&TP_DOWN)	*pdwPad1|=PAD_JOY_DOWN;
		if(key_data&TP_LEFT)	*pdwPad1|=PAD_JOY_LEFT;
		if(key_data&TP_RIGHT)	*pdwPad1|=PAD_JOY_RIGHT;
		if(key_data&TP_SELECT)	*pdwPad1|=PAD_JOY_SELECT;
		if(key_data&TP_START)	{*pdwPad1|=PAD_JOY_START;}
		if(key_data&TP_A)		*pdwPad1|=PAD_JOY_UP;
		if(key_data&TP_B)		*pdwPad1|=PAD_JOY_B;
		
//		key_data=0;
	}
}

/* memcpy */
void *InfoNES_MemoryCopy( void *dest, const void *src, int count ){return memcpy(dest,src,count);}

/* memset */
void *InfoNES_MemorySet( void  *dest, int c, int count ){return memset(dest,c,count);}

/* Print debug message */
void InfoNES_DebugPrint( char *pszMsg )
{
}

extern u8 falg_scankey;
#include "ft5206.h"
extern TouchTypedef mtouch;

#define TP_UP 		0X01
#define TP_DOWN 	0X02
#define TP_LEFT 	0X04
#define TP_RIGHT 	0X08
#define TP_SELECT 	0X10
#define TP_START 	0X20
#define TP_A 		0X40
#define TP_B 		0X80

extern uint8_t button_key;
/* Wait */
void InfoNES_Wait()
{
	if(falg_scankey)
	{
		falg_scankey=0;
        
        //触摸功能
        if(button_key)
        {
            key_data=0;
            for(uint8_t v=0;v<5;v++)
            {
                //A
                if((mtouch.y[v] > 170 && mtouch.y[v] <170+100) 
                    && (mtouch.x[v] > 350 && mtouch.x[v] < 350+100))
                {
                    key_data |= TP_UP;
//                    key_data |= TP_A;
                }
            }
            for(uint8_t v=0;v<5;v++)
            {
                //B
                if((mtouch.y[v] > 46 && mtouch.y[v] <46+100) 
                    && (mtouch.x[v] > 350 && mtouch.x[v] < 350+100))
                {
                    key_data |= TP_B;
                }
            }
            for(uint8_t v=0;v<5;v++)
            {
                //START
                if((mtouch.y[v] > 197 && mtouch.y[v] <197+33) 
                    && (mtouch.x[v] > 222 && mtouch.x[v] < 222+100))
                {
                    key_data |= TP_START;
                }
            }
            for(uint8_t v=0;v<5;v++)
            {
                //select
                if((mtouch.y[v] > 80 && mtouch.y[v] <80+33) 
                    && (mtouch.x[v] > 222 && mtouch.x[v] < 222+100))
                {
                    key_data |= TP_SELECT;
                }
            }
            for(uint8_t v=0;v<5;v++)
            {
                //上
                if((mtouch.y[v] > 189 && mtouch.y[v] <189+67) 
                    && (mtouch.x[v] > 77 && mtouch.x[v] < 77+67))
                {
                    key_data |= TP_UP;
                }
            }
            for(uint8_t v=0;v<5;v++)
            {
                //下
                if((mtouch.y[v] > 55 && mtouch.y[v] <55+67) 
                    && (mtouch.x[v] > 77 && mtouch.x[v] < 77+67))
                {
                    key_data |= TP_DOWN;
                }
            }
            for(uint8_t v=0;v<5;v++)
            {
                //左
                if((mtouch.y[v] > 122 && mtouch.y[v] <122+67) 
                    && (mtouch.x[v] > 10 && mtouch.x[v] < 10+67))
                {
                    key_data |= TP_LEFT;
                }
            }
            for(uint8_t v=0;v<5;v++)
            {
                //右
                if((mtouch.y[v] > 122 && mtouch.y[v] <122+67) 
                    && (mtouch.x[v] > 143 && mtouch.x[v] < 143+67))
                {
                    key_data |= TP_RIGHT;
                }
            }
        }
        else
        {
            key_data=0;
        }
	}
}

/* Sound Initialize */
void InfoNES_SoundInit( void )
{
}

/* Sound Open */
int InfoNES_SoundOpen( int samples_per_sync, int sample_rate )
{
  return 0;
}

/* Sound Close */
void InfoNES_SoundClose( void )
{
}

/* Sound Output 5 Waves - 2 Pulse, 1 Triangle, 1 Noise, 1 DPCM */
void InfoNES_SoundOutput(int samples, BYTE *wave1, BYTE *wave2, BYTE *wave3, BYTE *wave4, BYTE *wave5)
{
}

/* Print system message */
void InfoNES_MessageBox( char *pszMsg, ... )
{
}

