#include "../myDriver/gpio_driver.h"

_gpio_control  led0;
_gpio_control  led1;
void nGpio_init(void);

//#define  GPIO_PORT        (GPIOD)
//#define  GPIO_PIN         (GPIO_Pin_3)
//#define  GPIO_SET    (GPIO_SetBits(GPIO_PORT, GPIO_PIN))   //输出高电平
//#define  GPIO_RESET  (GPIO_ResetBits(GPIO_PORT, GPIO_PIN)) //输出低电平
//#define  GPIO_INPUT  (GPIO_ReadOutputDataBit(GPIO_PORT, GPIO_PIN)) //获取输入电平
//#define  GPIO_TOGGLE (GPIO_WriteBit(GPIO_PORT, GPIO_PIN, 1-GPIO_INPUT)) //输出翻转
//#define  GPIO_RCC_ENADLE (RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE)) //打开时钟线

#define GPIO_PORT_LED0  GPIOA
#define GPIO_PORT_LED1  GPIOA
#define GPIO_PIN_LED0   GPIO_Pin_0
#define GPIO_PIN_LED1   GPIO_Pin_1
/*********************************************************************
 * @fn      GPIOA_INIT
 *
 * @brief   Initializes GPIOA.0
 *
 * @return  none
 */
void GPIOx_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    //GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //启动GPIO的时钟线,让时钟进去以驱动其GPIO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;      //pin PA0 and PA1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            //推挽输出(最大驱动能力输出)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //频率越高,切换GPIO高低电平时间越短
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //init_gpio_struct
    nGpio_init();
}
/*********************************************************************
 * @fn      nGpio_init
 *
 * @brief   实现gpio端口结构体初始化
 *
 * @return  none
 */
void nGpio_init(void)
{
    led0.port = GPIO_PORT_LED0;
    led0.pin = GPIO_PIN_LED0;
    led0.period = 10;                //10*5ms
    led0.light_on_percent = 0.5f;
    led0.reset = 1;
    led0.times = 5;

    led1.port = GPIO_PORT_LED1;
    led1.pin = GPIO_PIN_LED1;
    led1.period = 10;                //10*5ms
    led1.light_on_percent = 0.5f;
    led1.reset = 1;
    led1.times = 3;
}

/*********************************************************************
 * @fn      gpio_control_work(_gpio_control *light)
 * @time    10ms
 * @brief   gpio驱动状态机
 * @input   _gpio_control *light-gpio控制结构体
 * @return  none
 */
void gpio_control_work(_gpio_control *light)
{
    if(light->reset==1){                                    //重置gpio控制
        light->reset=0;
        light->cnt=0;
        light->times_cnt=0;
        light->end=0;
    }
    if(light->times_cnt==light->times){                     //gpio周期控制
        light->end=1;
        return;
    }
    light->cnt++;printf("led0: %d \r\n",led0.cnt);
    if(light->cnt<=light->period*light->light_on_percent){  // 在点亮时间区间内（根据 light_on_percent）
        GPIO_SetBits(light->port, light->pin);
    }else if(light->cnt<light->period){                     // 在熄灭时间区间内
        GPIO_ResetBits(light->port, light->pin);
    }else{                                                  //周期结束，重置计数并记录已完成次数
        light->cnt=0;
        light->times_cnt++;
    }
}
/*********************************************************************
 * @fn      led_setup
 * @time
 * @brief   led及时控制
 * @input   uint32_t _period, float _light_on_percent, uint16_t _times
 * @return  none
 */
void led_setup(uint32_t _period, float _light_on_percent, uint16_t _times)
{
    led0.period = _period; //x*10ms
    led0.light_on_percent = _light_on_percent;
    led0.reset = 1;
    led0.times = _times;
}
/*********************************************************************
 * @fn      task_led_proc
 *
 * @brief   led任务函数
 *
 * @return  none
 */
void task_led0_proc(void){
    gpio_control_work(&led0);
}
void task_led1_proc(void){
    gpio_control_work(&led1);
}









