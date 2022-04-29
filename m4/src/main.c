/*==========================================================
 * Copyright 2020 QuickLogic Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *==========================================================*/

/*==========================================================
 *
 *    File   : main.c
 *    Purpose: main for QuickFeather helloworldsw and LED/UserButton test
 *                                                          
 *=========================================================*/

#include "Fw_global_config.h"   // This defines application specific charactersitics

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "RtosTask.h"
#include <stdlib.h>
/*    Include the generic headers required for QORC */
#include "eoss3_hal_gpio.h"
#include "eoss3_hal_rtc.h"
#include "eoss3_hal_timer.h"
#include "eoss3_hal_fpga_usbserial.h"
#include "ql_time.h"
#include "s3x_clock_hal.h"
#include "s3x_clock.h"
#include "s3x_pi.h"
#include "dbg_uart.h"

#include "cli.h"

#include "LCD16x2.h"
#include "LCD16x2_io.h"
#include "PyHal_GPIO.h"


const char *SOFTWARE_VERSION_STR;


/*
 * Connections
        LCD PIN <----> PYGMY
        LCD_D4  <---->  6
        LCD_D5  <---->  8
        LCD_D6  <---->  10
        LCD_D7  <---->  12
        LCD_RS  <---->  2
        LCD_EN  <---->  4
        LCD_RW  <---->  GND
 */


extern void qf_hardwareSetup();
static void nvic_init(void);

int main(void)
{

    SOFTWARE_VERSION_STR = "qorc-onion-apps/qf_hello-fpga-gpio-ctlr";
    HAL_Delay_Init();
    qf_hardwareSetup();
    nvic_init();

    dbg_str("\n\n");
    dbg_str( "##########################\n");
    dbg_str( "Quicklogic QuickFeather FPGA GPIO CONTROLLER EXAMPLE\n");
    dbg_str( "SW Version: ");
    dbg_str( SOFTWARE_VERSION_STR );
    dbg_str( "\n" );
    dbg_str( __DATE__ " " __TIME__ "\n" );
    dbg_str( "##########################\n\n");

    dbg_str( "\n\nHello , look at the LCD!!\n\n");	// <<<<<<<<<<<<<<<<<<<<<  Change me!
    
    PyHal_GPIO_Set(18,1);//blue
    
    LcdInit(); 
    dbg_str( "\ninit done\n");
    int i,j,X[2][2],A,B,C,D,r;
    char* text;

    while(1){
    
        LcdWriteString("Random Matrix"); LcdSetAddress(16);
         LcdWriteString("Multiplication");
        HAL_DelayUSec(1000*1000);
        LcdClear();
       
       
          A=rand()%10;
          B=rand()%10;
          C=rand()%10;
          D=rand()%10;
	
       r = A*C+B*D;
      
       sprintf(text,"%d ",A);
       LcdWriteString(text); LcdSetAddress(16);
       HAL_DelayUSec(500*1000); 
       sprintf(text,"%d ",B);
       LcdWriteString(text); LcdSetAddress(3); 
       HAL_DelayUSec(500*1000);sprintf(text,"%d ",C);
       LcdWriteString(text);  LcdSetAddress(5);
       HAL_DelayUSec(500*1000);sprintf(text,"%d ",D);
       LcdWriteString(text); LcdSetAddress(8);
       LcdWriteString("="); HAL_DelayUSec(500*1000); LcdSetAddress(10);
       HAL_DelayUSec(500*1000);sprintf(text,"%d ",r);
       LcdWriteString(text); 
        
        HAL_DelayUSec(2000*1000);
        LcdClear();
        HAL_DelayUSec(500*1000);
    }
    

    while(1);
}

static void nvic_init(void)
 {
    // To initialize system, this interrupt should be triggered at main.
    // So, we will set its priority just before calling vTaskStartScheduler(), not the time of enabling each irq.
    NVIC_SetPriority(Ffe0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(SpiMs_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(CfgDma_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(Uart_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(FbMsg_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
 }    

//needed for startup_EOSS3b.s asm file
void SystemInit(void)
{

}

