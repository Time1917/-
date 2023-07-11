/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2012, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date                Author         Notes
 * 2010-06-25          Bernard        first version
 * 2011-08-08          lgnq           modified for Loongson LS1B
 * 2015-07-06          chinesebear    modified for Loongson LS1C
 */

#include <rtthread.h>
#include "net/synopGMAC.h"
#include <lwip/api.h>
#include "../libraries/ls1c_public.h"
#include "../libraries/ls1c_gpio.h"
#include "../libraries/ls1c_delay.h"
#include "../drivers/led.h"
#include "../drivers/ps2.h"
#include "../libraries/ls1c_pwm.h"  

extern unsigned char Data[9];

void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif
#if defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
    /* mount sd card fat partition 1 as root directory */
    if( dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System initialized!\n");
    }
    else
    {
        rt_kprintf("File System initialzation failed!\n");
    }
#endif /* RT_USING_DFS && RT_USING_DFS_ELMFAT */


/*网口EMAC初始化*/
    rt_hw_eth_init();

#if defined(RT_USING_RTGUI)
/*触摸屏使用SPI总线SPI1 CS0  初始化*/
     rtgui_touch_hw_init("spi10");
#endif
rt_kprintf("系统初始化完成！\n");
}
void ps2_thread_entry(void *parameter)
{
	int key,FLAG=1;
	float Duty_steering = 0;
	float Duty_motor = 0.8;
	
	PS2_GPIO_Init();
	rt_kprintf("PS2 Init!\n");
	
	pwm_info_t pwm_steering;
	pwm_info_t pwm_motor_go;
	pwm_info_t pwm_motor_back1;
	pwm_info_t pwm_motor_back2;
	
	pwm_steering.gpio = LS1C_PWM0_GPIO06;               // pwm引脚位gpio06 
	pwm_steering.mode = PWM_MODE_NORMAL;                // 正常模式--连续输出pwm波形
	pwm_steering.duty = 0.916;                          // pwm占空比
	pwm_steering.period_ns = 20*1000*1000;              // pwm周期20ms  
	
	pwm_motor_go.gpio = LS1C_PWM1_GPIO92;               // pwm引脚位gpio92 
	pwm_motor_go.gpio = LS1C_PWM1_GPIO05;				// pwm引脚位gpio05
	pwm_motor_go.mode = PWM_MODE_NORMAL;                // 正常模式--连续输出pwm波形
	pwm_motor_go.duty = 0.99;                           // pwm占空比
	pwm_motor_go.period_ns = 100*1000;               	// pwm周期0.1ms
	
	pwm_motor_back1.gpio = LS1C_PWM2_GPIO46;				// pwm引脚位gpio53
	pwm_motor_back1.mode = PWM_MODE_NORMAL;              // 正常模式--连续输出pwm波形
	pwm_motor_back1.duty = 0.99;                         // pwm占空比
	pwm_motor_back1.period_ns = 100*1000;                // pwm周期0.1ms
	
	pwm_motor_back2.gpio = LS1C_PWM3_GPIO47;				// pwm引脚位gpio53
	pwm_motor_back2.mode = PWM_MODE_NORMAL;              // 正常模式--连续输出pwm波形
	pwm_motor_back2.duty = 0.99;                         // pwm占空比
	pwm_motor_back2.period_ns = 100*1000;                // pwm周期0.1ms
	
	rt_kprintf("  Init pwm! \n");
	// pwm初始化，初始化后立即产生pwm波形
	pwm_init(&pwm_steering);
	pwm_init(&pwm_motor_go);
	pwm_init(&pwm_motor_back1);
	pwm_init(&pwm_motor_back2);

	while(1)
	{
		//key = PS2_DataKey();
		ReadWriteControl();
		if(Data[2] == 0X5A)
		{
			//控制电机
			if(Data[3] == UP)
			{
				pwm_motor_go.duty = Duty_motor;
				pwm_init(&pwm_motor_go);
				delay_ms(10);
			}
			
			if(Data[3] == DOWN)
			{
				pwm_motor_back1.duty = Duty_motor;
				pwm_motor_back2.duty = Duty_motor;
				pwm_init(&pwm_motor_back1);
				pwm_init(&pwm_motor_back2);
				delay_ms(10);
			}
			if(Data[3] != DOWN && Data[3] != UP)
			{
				pwm_motor_go.duty = 0.99;
				pwm_motor_back1.duty = 0.99;
				pwm_motor_back2.duty = 0.99;
				pwm_init(&pwm_motor_go);
				pwm_init(&pwm_motor_back1);
				pwm_init(&pwm_motor_back2);
				delay_ms(10);
			}
			if(Data[4] == SANJIAO)
			{
				Duty_motor = 0.7;
			}
			if(Data[4] == CHA)
			{
				Duty_motor = 0.8;
			}
			//控制舵机
			if(Data[4] == FANGKUAI)
			{
				FLAG = 1;
				Duty_steering = 0.908;
				pwm_steering.duty = Duty_steering;
				pwm_init(&pwm_steering); 
				delay_ms(10);
			}
			if(Data[4] == YUAN)
			{
				FLAG = 1;
				Duty_steering = 0.923;
				pwm_steering.duty = Duty_steering;
				pwm_init(&pwm_steering); 
				delay_ms(10);
			}
			if(Data[3] == L1)
			{
				pwm_motor_go.duty = Duty_motor;
				pwm_init(&pwm_motor_go);
				delay_ms(10);
			}
			if(Data[4] != FANGKUAI && Data[4] != YUAN && Data[4] != SANJIAO && Data[4] != CHA)
			{	
				Duty_steering = 0.916;
				pwm_steering.duty = Duty_steering;
				if(FLAG ==1)
				{
					FLAG = 0;
					pwm_init(&pwm_steering);
				}
			}
			
			
			//rt_kprintf("%d is pressd!\n",key);
		}
	}
}

int rt_application_init(void)
{
	rt_thread_t tid;
	rt_thread_t tid1;

	/* create initialization thread */
	tid = rt_thread_create("init",
	                        rt_init_thread_entry, RT_NULL,
	                        4096, RT_THREAD_PRIORITY_MAX/3, 20);
	if (tid != RT_NULL)
		rt_thread_startup(tid);

	tid1 = rt_thread_create("thread",
	                        ps2_thread_entry, RT_NULL,
	                        4096, 20, 150);
	if (tid1 != RT_NULL)
		rt_thread_startup(tid1);

	return 0;
}
