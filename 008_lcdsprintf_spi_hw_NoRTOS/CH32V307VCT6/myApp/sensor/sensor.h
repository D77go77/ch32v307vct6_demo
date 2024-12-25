/*
 * sensor.h
 *
 *  Created on: 2024年12月23日
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
    // 传感器原始数据
    vector3f _gyro_dps_raw,gyro_dps_raw;
    vector3f _accel_g_raw,accel_g_raw;
    vector3f mag_tesla_raw;
    vector3f last_mag_raw;
    float temperature_raw,last_temperature_raw;
    float temperature_filter;
    float vbat;
    // 校准后的传感器数据
    vector3f gyro_dps;
    vector3f accel_g;
    vector3f mag_tesla;

    // 传感器偏移和尺度校正参数
    vector3f gyro_offset;
    vector3f accel_scale,accel_offset;

    // 电机速度相关数据
    float left_motor_speed_cmps;
    float right_motor_speed_cmps;
    float average_speed_cmps;

    // 四元数初始化状态和数据
    uint8_t quaternion_init_ok;
    float quaternion_init[4];//初始四元数
    float quaternion[4];//四元数

    // 姿态角和角速度数据
    float rpy_deg[3];
    float rpy_gyro_dps[3];
    float rpy_gyro_dps_enu[3];
    vector3f accel_earth_cmpss;
    vector2f accel_body_cmpss;
    float sin_rpy[3];
    float cos_rpy[3];
    float cb2n[9];

    // 姿态观测和卡尔曼滤波结果
    float rpy_obs_deg[3];//观测姿态角度
    float rpy_kalman_deg[3];

    // 方位角数据
    float yaw_gyro_enu;

    // IMU收敛状态和标志
    uint16_t imu_convergence_cnt;
    uint8_t imu_convergence_flag;
    uint8_t temperature_stable_flag;
    uint8_t imu_cal_flag;
    uint8_t imu_health;
    uint8_t lpf_init;
}sensor;

extern sensor smartcar_imu;

void imu_data_sampling(void);//IMU数据采样/校准/滤波
void trackless_ahrs_update(void);//姿态更新
void ICM206xx_Read_Data(vector3f *gyro,vector3f *accel,float *temperature);//读取传感器加速度计/陀螺仪/温度数据
void imu_calibration(vector3f *gyro,vector3f *accel);//加速度计/陀螺仪标定

void calculate_quaternion_init(vector3f a,vector3f m,float *q);//通过加速度计、磁力计数据计算初始四元数
void vector3f_sub(vector3f a,vector3f b,vector3f *c);//向量作差
void euler_to_quaternion(float *rpy,float *q);//欧拉角转四元数

#endif /* MYAPP_SENSOR_SENSOR_H_ */
