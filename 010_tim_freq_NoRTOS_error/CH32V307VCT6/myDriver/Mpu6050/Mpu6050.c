#include <myI2c.h>
#include <Mpu6050.h>

void nMpu6050_init(void)
{
    while(MPU_Init())   //MPU6050��ʼ��
    {
        printf("MPU6050 Error");
        Delay_Ms(200);
        Delay_Ms(200);
    }printf("MPU6050 OK");
}
/***************************************
������:    void ICM206xx_Read_Data(vector3f *gyro,vector3f *accel,float *temperature)
˵��: ��ȡ���������ٶȼ�/������/�¶�����
���: vector3f *gyro-��ȡ��������������ָ��
            vector3f *accelgyro-��ȡ������ٶ�����ָ��
            float *temperaturegyro-��ȡ�¶�����ָ��
��ע: �����ǵ�λdeg/s,���ٶȼƵ�λg,�¶ȵ�λ��
***************************************/
void ICM206xx_Read_Data(vector3f *gyro,vector3f *accel,float *temperature)
{
    uint8_t buf[14];
    int16_t temp;

    MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);

    accel->x=-(int16_t)((buf[0]<<8)|buf[1]);
    accel->y=-(int16_t)((buf[2]<<8)|buf[3]);
    accel->z= (int16_t)((buf[4]<<8)|buf[5]);
    temp        =(int16_t)((buf[6]<<8)|buf[7]);
    gyro->x =-(int16_t)((buf[8]<<8)|buf[9]);
    gyro->y =-(int16_t)((buf[10]<<8)|buf[11]);
    gyro->z = (int16_t)((buf[12]<<8)|buf[13]);
    *temperature=36.53f+(float)(temp/340.0f);

    gyro->x*=GYRO_CALIBRATION_COFF;
    gyro->y*=GYRO_CALIBRATION_COFF;
    gyro->z*=GYRO_CALIBRATION_COFF;

    accel->x/=GRAVITY_RAW;
    accel->y/=GRAVITY_RAW;
    accel->z/=GRAVITY_RAW;
}
//****************************************
/***************************************
������:    void imu_calibration_params_init(void)
˵��: ���ٶȼ�/�����Ǳ궨���ݳ�ʼ��
***************************************/
void imu_calibration_params_init(void)
{
    smartcar_imu.gyro_offset.x=0;
    smartcar_imu.gyro_offset.y=0;
    smartcar_imu.gyro_offset.z=0;

    smartcar_imu.imu_cal_flag=0;

    //У׼��������ƫ
    smartcar_imu.accel_scale.x=1.0f;
    smartcar_imu.accel_scale.y=1.0f;
    smartcar_imu.accel_scale.z=1.0f;

    smartcar_imu.accel_offset.x=0;
    smartcar_imu.accel_offset.y=0;
    smartcar_imu.accel_offset.z=0;
}
/***************************************
������:    void imu_calibration(vector3f *gyro,vector3f *accel)
˵��: ���ٶȼ�/�����Ǳ궨
***************************************/
#define gyro_delta_dps  3.0f
void imu_calibration(vector3f *gyro,vector3f *accel)
{
    if(smartcar_imu.imu_cal_flag==1)  return;

    static uint16_t cnt=0;
    static vector3f last_gyro;
    static vector3f accel_sum,gyro_sum;

    if(ABS(gyro->x-last_gyro.x)<=gyro_delta_dps
     &&ABS(gyro->y-last_gyro.y)<=gyro_delta_dps
     &&ABS(gyro->z-last_gyro.z)<=gyro_delta_dps)
    {
        gyro_sum.x+=gyro->x;
        gyro_sum.y+=gyro->y;
        gyro_sum.z+=gyro->z;
        accel_sum.x+=accel->x;
        accel_sum.y+=accel->y;
        accel_sum.z+=accel->z;
        cnt++;
    }
    else
    {
        gyro_sum.x=0;
        gyro_sum.y=0;
        gyro_sum.z=0;
        accel_sum.x=0;
        accel_sum.y=0;
        accel_sum.z=0;
        cnt=0;
    }
    last_gyro.x=gyro->x;
    last_gyro.y=gyro->y;
    last_gyro.z=gyro->z;

    if(cnt>=400)//��������2s//5ms*400=2s
    {
        smartcar_imu.gyro_offset.x =(gyro_sum.x/cnt);//�õ������Ǳ궨ƫ��
        smartcar_imu.gyro_offset.y =(gyro_sum.y/cnt);
        smartcar_imu.gyro_offset.z =(gyro_sum.z/cnt);
        smartcar_imu.accel_offset.x =(accel_sum.x/cnt);//�õ����ٶȱ궨ƫ��
        smartcar_imu.accel_offset.y =(accel_sum.y/cnt);
        smartcar_imu.accel_offset.z =(accel_sum.z/cnt)-safe_sqrt(1-sq2(smartcar_imu.accel_offset.x)-sq2(smartcar_imu.accel_offset.y));
        gyro_sum.x=0;
        gyro_sum.y=0;
        gyro_sum.z=0;
        accel_sum.x=0;
        accel_sum.y=0;
        accel_sum.z=0;
        cnt=0;
        smartcar_imu.imu_cal_flag=1;
    }
}
//��ʼ��MPU6050
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Init(void)
{ 
	u8 res;
	IIC_Init(100000,0x02);//��ʼ��IIC���� SCL-PB10 SDA-PB11
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//��λMPU6050
	Delay_Ms(200);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//����MPU6050 
	MPU_Write_Byte(MPU_SAMPLE_RATE_REG, 0x07);
	MPU_Write_Byte(MPU_CFG_REG,0x06);
	MPU_Write_Byte(MPU_ACCEL_CFG_REG,0x01);
	MPU_Write_Byte(MPU_GYRO_CFG_REG,0x018);

	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//�ر������ж�
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
	res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
	if(res==MPU_ADDR)//����ID��ȷ
	{
        MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);     //��λMPU6050
        Delay_Ms(200);
        MPU_Write_Byte(MPU_SAMPLE_RATE_REG,0x00);   // sample rate.  Fsample= 1Khz/(<this value>+1) = 1000Hz
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X03);	    //ʱ��Դ PLL with Z Gyro reference
		MPU_Write_Byte(MPU_CFG_REG,0x02);	        //�ڲ���ͨ�˲�Ƶ�ʣ����ٶȼ�184hz��������188hz  //Ĭ��0x03
		MPU_Write_Byte(MPU_GYRO_CFG_REG,0x08);      //500deg/s
		MPU_Write_Byte(MPU_ACCEL_CFG_REG,0x08);     // Accel scale 4g (8192 LSB/g)
 	}else return 1;
	Delay_Ms(200);
	imu_calibration_params_init();                  //�궨���ݳ�ʼ��
	return 0;
}
//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}
//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    u16 raw;
	float temp;
	MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;;
}
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Gyroscope(u16 *gx,u16 *gy,u16 *gz)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Accelerometer(u16 *ax,u16 *ay,u16 *az)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i=0; 
	I2C_AcknowledgeConfig( I2C2, ENABLE );
    I2C_GenerateSTART( I2C2, ENABLE );
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );
    I2C_Send7bitAddress(I2C2,((addr << 1) | 0),I2C_Direction_Transmitter);//����������ַ+д����
	while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) );  //�ȴ�Ӧ��
    while( I2C_GetFlagStatus( I2C2, I2C_FLAG_TXE ) ==  RESET );
    I2C_SendData(I2C2,reg);     //д�Ĵ�����ַ
	while(i < len)
    {
        if( I2C_GetFlagStatus( I2C2, I2C_FLAG_TXE ) !=  RESET )
            {
                I2C_SendData(I2C2,buf[i]);     //��������
                i++;
            }
    }
//    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) );
	while( I2C_GetFlagStatus( I2C2, I2C_FLAG_TXE ) ==  RESET );
	I2C_GenerateSTOP( I2C2, ENABLE );
	return 0;	
} 
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
    u8 i=0;
    I2C_AcknowledgeConfig( I2C2, ENABLE );
    I2C_GenerateSTART( I2C2, ENABLE );
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) ) ;
    I2C_Send7bitAddress(I2C2,(addr << 1) | 0X00,I2C_Direction_Transmitter); //����������ַ+д����
	while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) ); //�ȴ�Ӧ��
    I2C_SendData(I2C2,reg);         //д�Ĵ�����ַ
    I2C_GenerateSTART( I2C2, ENABLE );
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );
    I2C_Send7bitAddress(I2C2,((addr << 1) | 0x01),I2C_Direction_Receiver);//����������ַ+������
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ) ); //�ȴ�Ӧ��
    while(i < len)
    {
        if( I2C_GetFlagStatus( I2C2, I2C_FLAG_RXNE ) !=  RESET )
        {
            if(i == (len - 2))
            {
                I2C_AcknowledgeConfig( I2C2, DISABLE );
                buf[i] = I2C_ReceiveData(I2C2);		//������,����nACK
            }
            else
            {
                buf[i] = I2C_ReceiveData(I2C2);		//������,����ACK
            }
            i++;
        }
    }
    I2C_GenerateSTOP( I2C2, ENABLE ); //����һ��ֹͣ����
	return 0;	
}
//IICдһ���ֽ� 
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
    I2C_AcknowledgeConfig( I2C2, ENABLE );
    I2C_GenerateSTART( I2C2, ENABLE );
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );
    I2C_Send7bitAddress(I2C2,((MPU_ADDR << 1) | 0),I2C_Direction_Transmitter);//����������ַ+д����
	while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) );  //�ȴ�Ӧ��
    while( I2C_GetFlagStatus( I2C2, I2C_FLAG_TXE ) ==  RESET );
    I2C_SendData(I2C2,reg);     //д�Ĵ�����ַ
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) ); //�ȴ�Ӧ��
	while( I2C_GetFlagStatus( I2C2, I2C_FLAG_TXE ) ==  RESET );
    I2C_SendData(I2C2,data);      //��������
    I2C_GenerateSTOP( I2C2, ENABLE );
	return 0;
}
//IIC��һ���ֽ� 
//reg:�Ĵ�����ַ 
//����ֵ:����������
u8 MPU_Read_Byte(u8 reg)
{
	u8 res;
	I2C_AcknowledgeConfig( I2C2, ENABLE );
    I2C_GenerateSTART( I2C2, ENABLE );
	while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );
    I2C_Send7bitAddress(I2C2,(MPU_ADDR << 1) | 0X00,I2C_Direction_Transmitter); //����������ַ+д����
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) );  //�ȴ�Ӧ��
    I2C_SendData(I2C2,reg);         //д�Ĵ�����ַ
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) );//�ȴ�Ӧ��
    I2C_GenerateSTART( I2C2, ENABLE );
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );
    I2C_Send7bitAddress(I2C2,((MPU_ADDR << 1) | 0x01),I2C_Direction_Receiver);//����������ַ+������
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ) ); //�ȴ�Ӧ��
    while(1)
    {
        if( I2C_GetFlagStatus( I2C2, I2C_FLAG_RXNE ) !=  RESET )
        {
            res = I2C_ReceiveData( I2C2 ); //������,����nACK
            break;
        }
    }
    I2C_GenerateSTOP( I2C2, ENABLE );//����һ��ֹͣ����
	return res;		
}
