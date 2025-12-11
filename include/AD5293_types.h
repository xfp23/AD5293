/**
 * @file AD5293_types.h
 * @author https://github.com/xfp23/
 * @brief AD5293 Driver types
 * @version 0.1
 * @date 2025-12-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef __AD5293_TYPES_H_
#define __AD5293_TYPES_H_

#include "stdint.h"
#include "stdbool.h"
#include "AD5293_conf.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    AD5293_OK,
    AD5293_ERR,
    AD5293_BUSY,
    AD5293_INVALID_PARAM, // Invalid parameter
    AD5293_ALREADY_INITED,
    AD5293_OVERFLOW, // overflow
} AD5293_Status_t;

typedef enum
{
    AD5293_NOP = 0x00,
    AD5293_WR_RDAC = 0x01,
    AD5293_RD_RDAC = 0x02,
    AD5293_RESET = 0x04,
    AD5293_WR_CTRL = 0x06,
    AD5293_RD_CTRL = 0x07,
    AD5293_PWRDN = 0x08,
} AD5293_Cmd_t;

typedef enum
{
    AD5293_WP_ENABLE = 0,
    AD5293_WP_DISABLE = 1,
} AD5293_WriteProtect_t;

typedef enum
{
    AD5293_MODE_PER,
    AD5293_MODE_NORMAL,
} AD5293_WorkMode_t;

typedef enum
{
    AD5293_TYPE_10K,
    AD5293_TYPE_50K,
    AD5293_TYPE_100K,
} AD5293_type_t;

typedef enum
{
    AD5293_PWR_NORMAL,
    AD5293_PWR_DOWN,
} AD5293_Pwr_t;

typedef int (*AD5293_SPITransmit_t)(uint8_t *data, size_t len);

typedef int (*AD5293_SPIReveive_t)(uint8_t *buffer, size_t len);

typedef void (*AD5293_GPIOActive_t)(uint8_t level);

#if AD5293_USE_HW_RESET
typedef void (*AD5293_HardWareReset_t)(void);
#endif

typedef union
{
    struct
    {
        uint16_t value : 10;   // 10-bit RDAC data
        uint16_t command : 4;  // 4-bit command code
        uint16_t reserved : 2; // Reserved (always 0)
    } bits;

    uint8_t raw[2]; // Raw 16-bit frame
} AD5293_Frame_t;

typedef struct
{
    AD5293_SPITransmit_t trans_func;
    AD5293_SPIReveive_t recv_func;
    AD5293_GPIOActive_t cs_func;
#if AD5293_USE_HW_RESET
    AD5293_HardWareReset_t reset_func;
#endif
    AD5293_type_t type;
} AD5293_Conf_t;

typedef struct
{
    AD5293_SPITransmit_t Writebyte;
    AD5293_SPIReveive_t Readbyte;
    AD5293_GPIOActive_t cs;
#if AD5293_USE_HW_RESET
    AD5293_HardWareReset_t reset;
#endif
    uint32_t rab_ohm;
    // volatile uint8_t RDY;
} AD5293_Obj_t;

typedef AD5293_Obj_t *AD5293_Handle_t; // 句柄

#ifdef __cplusplus
}
#endif

#endif //! __AD5293_TYPES_H_