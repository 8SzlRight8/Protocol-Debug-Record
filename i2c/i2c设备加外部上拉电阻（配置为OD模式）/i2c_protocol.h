#ifndef _I2C_PROTOCOL_H
#define _I2C_PROTOCOL_H

/***************************** 使 用 说 明 *****************************
* ----------------------------------------------------------------------
* 
* 调 试 平 台 ：STM32F429ZET6
* I2C（软/硬）：软件模拟I2C。
* SDA、SCL端口配置：外部加上拉电阻，OD开漏输出
* 
* ----------------------------------------------------------------------
* 
* 使用步骤：
* 1、若I2C的GPIO口不对，则修改为对应的GPIO口宏定义 即可
*    I2C_SCL_PORT、I2C_SCL_CLK、I2C_SCL_PIN	以及
*    I2C_SDA_PORT、I2C_SDA_CLK、I2C_SDA_PIN	  
*    （初始化端口在第四步中调用）
* 
* 2、包含此头文件到对应的设备驱动文件，定义一个全局 的I2C结构体变量
* 	 I2C_Dev_t * i2c_LTC2942;   //i2c_LTC2942 为自己取的变量名
* 
* 3、在使用前 调用函数 i2c_LTC2942 = i2c_dev_create();即可。 
* 	 （此函数作用：创建 I2C结构体变量，并初始化）
* 
* 4、随后即可用指针的方式调用对应的函数（方法）
*    Eg: i2c_dev->i2c_checkDevice(0xC8)...//检查是否能正常通信
* 
* 注意：【I2C总线只挂一个设备不用看】
*    1）用指针操作方便了，但是没有函数传参说明，需要到头文件查看。
*       （不过有参数没写的话，编译器可检查，keil中F12可调转到申明）
* 
*    2）定义了一个 i2c_dev_del(I2C_Dev_t* dev) 函数，有点问题，如果
*       全程不需要删除i2c设备，可不用关心。需要使用内存池就能解决。
*       （自带malloc和free函数的问题，申请次数过多容易造成内存溢出）。
* 
* ----------------------------------------------------------------------
***********************************************************************/

#include "stm32f4xx.h"
#include <inttypes.h>

/*********** DEFINE ***********/
#define I2C_WR	0		/* 写控制bit */
#define I2C_RD	1		/* 读控制bit */

#define I2C_SCL_PORT        GPIOA			/* GPIO端口 */
#define I2C_SCL_CLK         RCC_AHB1Periph_GPIOA		/* GPIO端口时钟 */
#define I2C_SCL_PIN	        GPIO_Pin_3			/* 连接到SCL时钟线的GPIO */

#define I2C_SDA_PORT        GPIOG			/* GPIO端口 */
#define I2C_SDA_CLK         RCC_AHB1Periph_GPIOG		/* GPIO端口时钟 */
#define I2C_SDA_PIN         GPIO_Pin_14			/* 连接到SCL时钟线的GPIO */

#define I2C_SCL_1()         GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN)		/* SCL = 1 */
#define I2C_SCL_0()         GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN)		/* SCL = 0 */
										       
#define I2C_SDA_1()         GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN)		/* SDA = 1 */
#define I2C_SDA_0()         GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN)		/* SDA = 0 */

#define I2C_SDA_READ()      GPIO_ReadInputDataBit(I2C_SDA_PORT, I2C_SDA_PIN)	/* 读SDA口线状态 */


/*********** DEFINE TYPE ***********/
//define a struct
typedef struct
{
	//i2c function
	void(*i2c_start)(void);
	void(*i2c_stop)(void);
	void(*i2c_writeByte)(uint8_t Data);
	uint8_t(*i2c_readByte)(void);
	
	uint8_t(*i2c_waitAck)(void);
	void(*i2c_ack)(void);    //ack 0
	void(*i2c_nack)(void);   //ack 1
	
	//i2c check function
	uint8_t(*i2c_checkDevice)(uint8_t _Address);
	
}I2C_Dev_t;


/*********** Function ***********/
//init i2c device
I2C_Dev_t* i2c_dev_create(void);

//del i2c device(littte wrong here)
void i2c_dev_del(I2C_Dev_t* dev);

#endif

