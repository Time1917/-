#include <rtthread.h>
#include "../libraries/ls1c_public.h"
#include "../libraries/ls1c_gpio.h"
#include "../libraries/ls1c_delay.h"
#include "../drivers/led.h"
#include "../drivers/ps2.h"

/* LED引脚 */
#define	LED1	52
#define	LED2	53


void LED_Init(void)
{
	led_init(LED1);
	led_init(LED2);
}

void test_ps2(void)
{
	int key;
	LED_Init();
    PS2_GPIO_Init();
	rt_kprintf("PS2 Init!\n");
	while(1)
	{
		// if(PS2_RedLight())
		// {
			// delay_ms(50);
			// led_on(LED2);
			// PS2_ClearData();
			// //PS2_DataKey();
			// rt_kprintf("%d  %d  %d  %d\n",PS2_AnologData(PSS_LX),PS2_AnologData(PSS_LY),PS2_AnologData(PSS_RX),PS2_AnologData(PSS_RY));
		// }
		// else
		// {
			// led_off(LED2);
		// }
		key = PS2_DataKey();
		if(key!=0)
		{
			if(key == 5)
			{
				led_on(LED2);
			}
			if(key == 13)
				led_off(LED2);
			rt_kprintf("%d is pressd!\n",key);
		}
	}
}

#include  <finsh.h> 
FINSH_FUNCTION_EXPORT(test_ps2, test_ps2  e.g.test_ps2());