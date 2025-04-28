Схема підключення:
![image](https://github.com/user-attachments/assets/01618ee9-eb8e-4d41-9673-b1351bfb1274)
Отримання значень з I2C1, та надсилання їх на USART2:
```
/* USER CODE BEGIN Includes */
// Підключення бібліотеки для роботи з MPU6050
// (Include library for MPU6050)
#include "mpu6050.h"
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
char uart_buf[100];  // Буфер для UART (UART buffer)
// Структура для збереження даних з MPU6050
// (Structure to store MPU6050 data)
MPU6050_Data_t mpu6050;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
// Ініціалізація MPU6050 (Initialize MPU6050)
MPU6050_Init(&hi2c1);
/* USER CODE END 2 */

/* Infinite loop */
/* USER CODE BEGIN WHILE */
while (1) {
    // Читання всіх даних з MPU6050 (Read all data from MPU6050)
    MPU6050_Read_All(&hi2c1, &mpu6050);

    // Форматування даних для передачі через UART
    // (Format data for UART transmission)
    snprintf(uart_buf, sizeof(uart_buf),
                "Ax: %d Ay: %d Az: %d | Gx: %d Gy: %d Gz: %d\r\n",
                mpu6050.Accel_X,
                mpu6050.Accel_Y,
                mpu6050.Accel_Z,
                mpu6050.Gyro_X,
                mpu6050.Gyro_Y,
                mpu6050.Gyro_Z);

    // Передача тексту через UART2 (Transmit text via UART2)
    HAL_UART_Transmit(&huart2, (uint8_t*)uart_buf, strlen(uart_buf), HAL_MAX_DELAY);

    // Затримка 100 мс (100 ms delay)
    HAL_Delay(100);
/* USER CODE END WHILE */

/* USER CODE BEGIN 3 */
}

```
