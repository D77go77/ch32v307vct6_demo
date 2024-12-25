/*
 * sensor.h
 *
 *  Created on: 2024��12��23��
 *      Author: 19816
 */

#ifndef MYAPP_SENSOR_SENSOR_H_
#define MYAPP_SENSOR_SENSOR_H_

#include "../myApp/common_inc.h"

enum
{
    _ROL=0,
    _PIT,
    _YAW
};

enum
{
    ROL=0,
    PIT,
    YAW
};

typedef struct
{
  float x;
  float y;
  float z;
}vector3f;

typedef struct
{
  float x;
  float y;
}vector2f;

typedef struct
{
    // ������ԭʼ����
    vector3f _gyro_dps_raw,gyro_dps_raw;
    vector3f _accel_g_raw,accel_g_raw;
    vector3f mag_tesla_raw;
    vector3f last_mag_raw;
    float temperature_raw,last_temperature_raw;
    float temperature_filter;
    float vbat;
    // У׼��Ĵ���������
    vector3f gyro_dps;
    vector3f accel_g;
    vector3f mag_tesla;

    // ������ƫ�ƺͳ߶�У������
    vector3f gyro_offset;
    vector3f accel_scale,accel_offset;

    // ����ٶ��������
    float left_motor_speed_cmps;
    float right_motor_speed_cmps;
    float average_speed_cmps;

    // ��Ԫ����ʼ��״̬������
    uint8_t quaternion_init_ok;
    float quaternion_init[4];//��ʼ��Ԫ��
    float quaternion[4];//��Ԫ��

    // ��̬�Ǻͽ��ٶ�����
    float rpy_deg[3];
    float rpy_gyro_dps[3];
    float rpy_gyro_dps_enu[3];
    vector3f accel_earth_cmpss;
    vector2f accel_body_cmpss;
    float sin_rpy[3];
    float cos_rpy[3];
    float cb2n[9];

    // ��̬�۲�Ϳ������˲����
    float rpy_obs_deg[3];//�۲���̬�Ƕ�
    float rpy_kalman_deg[3];

    // ��λ������
    float yaw_gyro_enu;

    // IMU����״̬�ͱ�־
    uint16_t imu_convergence_cnt;
    uint8_t imu_convergence_flag;
    uint8_t temperature_stable_flag;
    uint8_t imu_cal_flag;
    uint8_t imu_health;
    uint8_t lpf_init;
}sensor;

extern sensor smartcar_imu;

void imu_data_sampling(void);//IMU���ݲ���/У׼/�˲�
void trackless_ahrs_update(void);//��̬����
void ICM206xx_Read_Data(vector3f *gyro,vector3f *accel,float *temperature);//��ȡ���������ٶȼ�/������/�¶�����
void imu_calibration(vector3f *gyro,vector3f *accel);//���ٶȼ�/�����Ǳ궨

void calculate_quaternion_init(vector3f a,vector3f m,float *q);//ͨ�����ٶȼơ����������ݼ����ʼ��Ԫ��
void vector3f_sub(vector3f a,vector3f b,vector3f *c);//��������
void euler_to_quaternion(float *rpy,float *q);//ŷ����ת��Ԫ��

#endif /* MYAPP_SENSOR_SENSOR_H_ */
