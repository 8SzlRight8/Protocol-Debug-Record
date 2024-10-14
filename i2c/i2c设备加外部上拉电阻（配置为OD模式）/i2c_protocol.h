#ifndef _I2C_PROTOCOL_H
#define _I2C_PROTOCOL_H

/***************************** ʹ �� ˵ �� *****************************
* ----------------------------------------------------------------------
* 
* �� �� ƽ ̨ ��STM32F429ZET6
* I2C����/Ӳ�������ģ��I2C��
* SDA��SCL�˿����ã��ⲿ���������裬OD��©���
* 
* ----------------------------------------------------------------------
* 
* ʹ�ò��裺
* 1����I2C��GPIO�ڲ��ԣ����޸�Ϊ��Ӧ��GPIO�ں궨�� ����
*    I2C_SCL_PORT��I2C_SCL_CLK��I2C_SCL_PIN	�Լ�
*    I2C_SDA_PORT��I2C_SDA_CLK��I2C_SDA_PIN	  
*    ����ʼ���˿��ڵ��Ĳ��е��ã�
* 
* 2��������ͷ�ļ�����Ӧ���豸�����ļ�������һ��ȫ�� ��I2C�ṹ�����
* 	 I2C_Dev_t * i2c_LTC2942;   //i2c_LTC2942 Ϊ�Լ�ȡ�ı�����
* 
* 3����ʹ��ǰ ���ú��� i2c_LTC2942 = i2c_dev_create();���ɡ� 
* 	 ���˺������ã����� I2C�ṹ�����������ʼ����
* 
* 4����󼴿���ָ��ķ�ʽ���ö�Ӧ�ĺ�����������
*    Eg: i2c_dev->i2c_checkDevice(0xC8)...//����Ƿ�������ͨ��
* 
* ע�⣺��I2C����ֻ��һ���豸���ÿ���
*    1����ָ����������ˣ�����û�к�������˵������Ҫ��ͷ�ļ��鿴��
*       �������в���ûд�Ļ����������ɼ�飬keil��F12�ɵ�ת��������
* 
*    2��������һ�� i2c_dev_del(I2C_Dev_t* dev) �������е����⣬���
*       ȫ�̲���Ҫɾ��i2c�豸���ɲ��ù��ġ���Ҫʹ���ڴ�ؾ��ܽ����
*       ���Դ�malloc��free���������⣬�������������������ڴ��������
* 
* ----------------------------------------------------------------------
***********************************************************************/

#include "stm32f4xx.h"
#include <inttypes.h>

/*********** DEFINE ***********/
#define I2C_WR	0		/* д����bit */
#define I2C_RD	1		/* ������bit */

#define I2C_SCL_PORT        GPIOA			/* GPIO�˿� */
#define I2C_SCL_CLK         RCC_AHB1Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define I2C_SCL_PIN	        GPIO_Pin_3			/* ���ӵ�SCLʱ���ߵ�GPIO */

#define I2C_SDA_PORT        GPIOG			/* GPIO�˿� */
#define I2C_SDA_CLK         RCC_AHB1Periph_GPIOG		/* GPIO�˿�ʱ�� */
#define I2C_SDA_PIN         GPIO_Pin_14			/* ���ӵ�SCLʱ���ߵ�GPIO */

#define I2C_SCL_1()         GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN)		/* SCL = 1 */
#define I2C_SCL_0()         GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN)		/* SCL = 0 */
										       
#define I2C_SDA_1()         GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN)		/* SDA = 1 */
#define I2C_SDA_0()         GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN)		/* SDA = 0 */

#define I2C_SDA_READ()      GPIO_ReadInputDataBit(I2C_SDA_PORT, I2C_SDA_PIN)	/* ��SDA����״̬ */


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

