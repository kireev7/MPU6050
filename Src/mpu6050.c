#include "mpu6050.h"

void MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t check;
    uint8_t data;

    // Зчитати WHO_AM_I
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_REG_WHO_AM_I, 1, &check, 1, HAL_MAX_DELAY);

    if (check == 0x68) // MPU6050 знайдено
    {
        // Скинути сплячий режим
        data = 0;
        HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_REG_PWR_MGMT_1, 1, &data, 1, HAL_MAX_DELAY);
    }
}

void MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_Data_t *data)
{
    uint8_t Rec_Data[14];

    // Зчитати 14 байт з ACCEL_XOUT_H
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_REG_ACCEL_XOUT_H, 1, Rec_Data, 14, HAL_MAX_DELAY);

    // Обробити акселерометр
    data->Accel_X = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    data->Accel_Y = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    data->Accel_Z = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    // Пропустити температуру (6 і 7 байт)

    // Обробити гіроскоп
    data->Gyro_X = (int16_t)(Rec_Data[8] << 8 | Rec_Data[9]);
    data->Gyro_Y = (int16_t)(Rec_Data[10] << 8 | Rec_Data[11]);
    data->Gyro_Z = (int16_t)(Rec_Data[12] << 8 | Rec_Data[13]);
}
