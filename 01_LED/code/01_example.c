#include <stdio.h>
#include <unistd.h>

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "hal_bsp_pcf8574.h"

osThreadId_t Task1_ID = 0;        //  任务1 ID
#define TASK_STACK_SIZE 1024

/**
 * @description: 任务1
 * @param {*}
 * @return {*}
 */
void Task1(void)
{
    printf("enter Task 1.......\r\n");
    while (1) {
        set_led(true); // LED灯点亮
        sleep(1);

        set_led(false); // LED灯熄灭
        sleep(1);
    }
}

/**
 * @description: 初始化并创建任务
 * @param {*}
 * @return {*}
 */
static void base_led_demo(void)
{
    printf("[demo] Enter base_led_demo()!\r\n");

    PCF8574_Init();

    osThreadAttr_t taskOptions;
    taskOptions.name = "Task1";              // 任务的名字
    taskOptions.attr_bits = 0;               // 属性位
    taskOptions.cb_mem = NULL;               // 堆空间地址
    taskOptions.cb_size = 0;                 // 堆空间大小
    taskOptions.stack_mem = NULL;            // 栈空间地址
    taskOptions.stack_size = TASK_STACK_SIZE;           // 栈空间大小 单位:字节
    taskOptions.priority = osPriorityNormal; // 任务的优先级:wq

    Task1_ID = osThreadNew((osThreadFunc_t)Task1, NULL, &taskOptions); // 创建任务1
    if (Task1_ID != NULL) {
        printf("ID = %d, Create Task1_ID is OK!\r\n", Task1_ID);
    }
}
SYS_RUN(base_led_demo);
