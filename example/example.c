#include "AD5293.h"
#include <stdio.h>
#include <stdint.h>

/* ===================== 模拟 SPI 回调函数 ===================== */
// 根据你实际平台实现 SPI 发送/接收函数和片选
void SPI_CS(uint8_t level) {
    // 拉低或拉高片选
}

void SPI_Transmit(uint8_t *data, uint16_t len) {
    // 通过 SPI 发送数据
}

void SPI_Receive(uint8_t *data, uint16_t len) {
    // 通过 SPI 接收数据
}

#if AD5293_USE_HW_RESET
void HW_Reset(void) {
    // 控制硬件 RESET 引脚，高电平触发
}
#endif

/* ===================== 主程序示例 ===================== */
int main(void) {
    AD5293_Handle_t potHandle = NULL;

    // 配置结构体
    AD5293_Conf_t conf = {0};
    conf.cs_func = SPI_CS;
    conf.trans_func = SPI_Transmit;
    conf.recv_func = SPI_Receive;
#if AD5293_USE_HW_RESET
    conf.reset_func = HW_Reset;
#endif
    conf.type = AD5293_TYPE_10K; // 选择器件阻值类型

    // 初始化电位器
    if (AD5293_Init(&potHandle, &conf) != AD5293_OK) {
        printf("AD5293 init failed!\n");
    }


    // 设置阻值为 5 kΩ
    if (AD5293_SetResistance(potHandle, 5000) != AD5293_OK) {
        printf("Set resistance failed!\n");
    }

    // 读取当前阻值
    uint16_t currentResistance = 0;
    if (AD5293_GetResistance(potHandle, &currentResistance) == AD5293_OK) {
        printf("Current resistance: %u Ω\n", currentResistance);
    } else {
        printf("Read resistance failed!\n");
    }

    // 设置写保护和工作模式
    AD5293_WritePortect(potHandle, AD5293_WP_DISABLE, AD5293_MODE_PER); // 禁用写保护，私用性能模式

    // 修改阻值到 8 kΩ
    AD5293_SetResistance(potHandle, 8000);

    // 再次读取
    AD5293_GetResistance(potHandle, &currentResistance);
    printf("Updated resistance: %u Ω\n", currentResistance);
 
    AD5293_SetPower(potHandle,AD5293_PWR_DOWN); // 设备掉电

    AD5293_SetPower(potHandle,AD5293_PWR_NORMAL); // 重新唤醒
 
    // 反初始化
    AD5293_DeInit(&potHandle);

    return 0;
}
