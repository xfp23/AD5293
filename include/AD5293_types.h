/**
 * @file AD5293_types.h
 * @author https://github.com/xfp23/
 * @brief AD5293 Driver
 * @version 0.1
 * @date 2025-12-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef __AD5293_TYPES_H_
#define __AD5293_TYPES_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef int (*AD5293_SPITransmit_t)(uint8_t *data, size_t len);

typedef int (*AD5293_SPIReveive_t)(uint8_t *buffer, size_t len);

typedef void (*AD5293_GPIOActive_t)(uint8_t level);


typedef struct
{
    AD5293_SPITransmit_t trans_func;
    AD5293_SPIReveive_t recv_func;
    AD5293_GPIOActive_t cs_func;

} AD5293_Conf_t;

typedef struct
{
    AD5293_Conf_t conf;

} AD5293_Obj_t;

typedef AD5293_Obj_t *AD5293_Handle_t; // 句柄 

#ifdef __cplusplus
}
#endif

#endif //! __AD5293_TYPES_H_