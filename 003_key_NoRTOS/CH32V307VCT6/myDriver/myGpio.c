#include "myGpio.h"

_gpio_control  led0;
_gpio_control  led1;
/*********************************************************************
 * @fn      nGpio_init
 *
 * @brief   ʵ��gpio�˿ڽṹ���ʼ��
 *
 * @return  none
 */
void nGpio_init(void)
{
    led0.port = GPIO_PORT_LED0;
    led0.pin = GPIO_PIN_LED0;
    led0.period = 100;                //100*1ms
    led0.light_on_percent = 0.5f;
    led0.reset = 1;
    led0.times = 5;

    led1.port = GPIO_PORT_LED1;
    led1.pin = GPIO_PIN_LED1;
    led1.period = 100;                //100*1ms
    led1.light_on_percent = 0.5f;
    led1.reset = 1;
    led1.times = 5;
}

/*********************************************************************
 * @fn      gpio_control_work(_gpio_control *light)
 * @time    10ms
 * @brief   gpio����״̬��
 * @input   _gpio_control *light-gpio���ƽṹ��
 * @return  none
 */
void gpio_control_work(_gpio_control *light)
{
    if(light->reset==1){                                    //����gpio����
        light->reset=0;
        light->cnt=0;
        light->times_cnt=0;
        light->end=0;
    }
    if(light->times_cnt==light->times){                     //gpio���ڿ���
        light->end=1;
        return;
    }
    light->cnt++;
//    printf("led0: %d \r\n",led0.cnt);
    if(light->cnt<=light->period*light->light_on_percent){  // �ڵ���ʱ�������ڣ����� light_on_percent��
        GPIO_SetBits(light->port, light->pin);
    }else if(light->cnt<light->period){                     // ��Ϩ��ʱ��������
        GPIO_ResetBits(light->port, light->pin);
    }else{                                                  //���ڽ��������ü�������¼����ɴ���
        light->cnt=0;
        light->times_cnt++;
    }
}
/*********************************************************************
 * @fn      led_setup
 * @time
 * @brief   led��ʱ����
 * @input   uint32_t _period, float _light_on_percent, uint16_t _times
 * @return  none
 */
void led0_setup(uint32_t _period, float _light_on_percent, uint16_t _times)
{
    led0.period = _period; //x*1ms
    led0.light_on_percent = _light_on_percent;
    led0.reset = 1;
    led0.times = _times;
}
void led1_setup(uint32_t _period, float _light_on_percent, uint16_t _times)
{
    led1.period = _period; //x*1ms
    led1.light_on_percent = _light_on_percent;
    led1.reset = 1;
    led1.times = _times;
}
/*********************************************************************
 * @fn      task_led_proc
 *
 * @brief   led������
 *
 * @return  none
 */
void task_led0_proc(void){
    gpio_control_work(&led0);
}
void task_led1_proc(void){
    gpio_control_work(&led1);
}









