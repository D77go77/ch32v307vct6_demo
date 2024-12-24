#include "scheduler.h"

// ȫ�ֱ��������ڴ洢��������
uint8_t task_num;

typedef struct {
    void (*task_func)(void);
    uint32_t rate_ms;
    uint32_t last_run;
} task_t;

// ��̬�������飬ÿ�����������������ִ�����ڣ����룩���ϴ�����ʱ�䣨���룩
static task_t scheduler_task[] =//����һ��������������ִ������Ϊx���룬��ʼ�ϴ�����ʱ��Ϊ x
{
    {task_led0_proc,5,0},
    {task_led1_proc,5,0},
    {task_key_gets,5,0},
    {task_oled_proc,200,100},
    {task_lcd_proc,200,100}
};

/**
 * @brief ��������ʼ������
 * �������������Ԫ�ظ�������������洢�� task_num ��
 */
void scheduler_init(void)
{
    // �������������Ԫ�ظ�������������洢�� task_num ��
    task_num = sizeof(scheduler_task) / sizeof(task_t);
}

/**
 * @brief ���������к���
 * �����������飬����Ƿ���������Ҫִ�С������ǰʱ���Ѿ����������ִ�����ڣ���ִ�и����񲢸����ϴ�����ʱ��
 */
void scheduler_run(void)
{
    // �������������е���������
    for (uint8_t i = 0; i < task_num; i++)
    {
        // ��ȡ��ǰ��ϵͳʱ�䣨���룩
        uint32_t now_time = tickTime;

        // ��鵱ǰʱ���Ƿ�ﵽ�����ִ��ʱ��
        if (now_time >= scheduler_task[i].rate_ms + scheduler_task[i].last_run)
        {
            // ����������ϴ�����ʱ��Ϊ��ǰʱ��
            scheduler_task[i].last_run = now_time;

            // ִ��������
            scheduler_task[i].task_func();
        }
    }
}
