#include <stdio.h>
#include <unistd.h>

#include "ohos_init.h"
#include "cmsis_os2.h"

#include "hal_bsp_pcf8574.h" // For PCF8574
#include "hal_bsp_aw2013.h" // For RGB

#define RGB_TASK_STACK_SIZE 1024
#define RGB_OFF 0
#define RGB_ON 255
#define TASK_DELAY_TIME 1
#define TASK_DELAY_TIME_MS 1024

osThreadId_t Task1_ID = 0; // Task1 ID

void Task1(void *arg)
{
    prints("Task1 is running\n");
    while(1)
    {
     AW2013_Control_Red(RGB_ON);
     AW2013_Control_Green(RGB_ON);
     AW2013_Control_Blue(RGB_ON);
     sleep(TASK_DELAY_TIME);

     AW2013_Control_Red(RGB_OFF);
     AW2013_Control_Green(RGB_OFF);
     AW2013_Control_Blue(RGB_OFF);
     sleep(TASK_DELAY_TIME);

    }

}
void RGB_example(void)
{
    prints("enter RGB_example()!\n");
    PFC8574_Init();
    AW2013_Init(); // Init RGB
    AW2013_Control_Red(RGB_OFF);
    AW2013_Control_Green(RGB_OFF);
    AW2013_Control_Blue(RGB_OFF);

    osThreadAttr_t options;
    options.name = "RGB_Task1";
    options.attr_bits = 0;//属性位
    option.cb_mem = NULL;//控制块内存
    options.cb_size = 0;//控制块大小
    options.stack_mem = NULL;//堆栈内存
    options.stack_size = RGB_TASK_STACK_SIZE;
    options.priority = osPriorityNormal;
    Task1_ID = osThreadNew(Task1, NULL, &options); // Create Task1
    if (Task1_ID != NULL)
    {
         printf("ID = %d, Create Task1_ID is OK!\r\n", Task1_ID);
    }
}
SUN_RUN(RGB_example);