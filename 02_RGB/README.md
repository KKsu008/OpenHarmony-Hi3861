## Hi3861 三色灯实验

### **一、实验目的**

通过I2C设备控制，实现Hi3861控制三色灯的亮度和颜色。

### 二、开发环境 

开发板： Hi3861 

系统： OpenHarmony 

LiteOS-M 开发工具： DevEco Device Tool 

编译： hb build

### 三、实验现象

烧录程序后：led灯亮（可利用三色led每个的亮度来调节led的颜色）

### 四、知识点

初始化



 * ```
    * uint32_t AW2013_Init(void)
   
      {
   
        uint32_t result;
   
        // gpio_9 复用为 I2C_SCL
   
        hi_io_set_pull(HI_IO_NAME_GPIO_9, HI_IO_PULL_UP);
   
        hi_io_set_func(HI_IO_NAME_GPIO_9, HI_IO_FUNC_GPIO_9_I2C0_SCL);
   
        // gpio_10 复用为 I2C_SDA
   
        hi_io_set_pull(HI_IO_NAME_GPIO_10, HI_IO_PULL_UP);
   
        hi_io_set_func(HI_IO_NAME_GPIO_10, HI_IO_FUNC_GPIO_10_I2C0_SDA);
   
        result = hi_i2c_init(AW2013_I2C_IDX, AW2013_I2C_SPEED);
   
        if (result != HI_ERR_SUCCESS) {
   
      ​    printf("I2C aw2013 Init status is 0x%x!!!\r\n", result);
   
      ​    return result;
   
        }
   
        // 复位芯片
   
        result = aw2013_WiteByte(RSTR_REG_ADDR, 0x55);
   
        if (result != HI_ERR_SUCCESS) {
   
      ​    printf("I2C aw2013 RdSTR_REG_ADDR status = 0x%x!!!\r\n", result);
   
      ​    return result;
   
        }
   
        usleep(TIME_RESET);
   
        // 使能全局控制器 设置为RUN模式
   
        result = aw2013_WiteByte(GCR_REG_ADDR, 0x01);
   
        if (result != HI_ERR_SUCCESS) {
   
      ​    printf("I2C aw2013 GCR_REG_ADDR status = 0x%x!!!\r\n", result);
   
      ​    return result;
   
        }
   
        // 设置打开RGB三路通道
   
        result = aw2013_WiteByte(LCTR_REG_ADDR, 0x07); // 4: B, 2: G, 1: R
   
        if (result != HI_ERR_SUCCESS) {
   
      ​    printf("I2C aw2013 LCTR_REG_ADDR status = 0x%x!!!\r\n", result);
   
      ​    return result;
   
        }
   
        // 设置RGB三路通道的工作模式
   
        result = aw2013_WiteByte(LCFG0_REG_ADDR, 0x63);
   
        if (result != HI_ERR_SUCCESS) {
   
      ​    printf("I2C aw2013 LCFG0_REG_ADDR status = 0x%x!!!\r\n", result);
   
      ​    return result;
   
        }
   
        result = aw2013_WiteByte(LCFG1_REG_ADDR, 0x63);
   
        if (result != HI_ERR_SUCCESS) {
   
      ​    printf("I2C aw2013 LCFG1_REG_ADDR status = 0x%x!!!\r\n", result);
   
      ​    return result;
   
        }
   
        result = aw2013_WiteByte(LCFG2_REG_ADDR, 0x63);
   
        if (result != HI_ERR_SUCCESS) {
   
      ​    printf("I2C aw2013 LCFG2_REG_ADDR status = 0x%x!!!\r\n", result);
   
      ​    return result;
   
        }
   
        printf("I2C aw2013 Init is succeeded!!!\r\n");
   
        return HI_ERR_SUCCESS;
   
      }
   
   
   ```

   