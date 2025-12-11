/**
 * @file AD5293.h
 * @author https://github.com/xfp23/
 * @brief AD5293 Digital Potentiometer Driver
 * @version 0.1
 * @date 2025-12-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef __AD5293_H_
#define __AD5293_H_

#include "AD5293_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Initialize the AD5293 device and create a handle
 * 
 * This function allocates memory for the AD5293 handle, registers SPI
 * communication callbacks, sets the device type (resistor value), and
 * optionally performs hardware or software reset.
 *
 * @param handle Pointer to a handle variable, will be initialized
 * @param conf Configuration structure including SPI callbacks and device type
 * @return AD5293_Status_t Status of initialization (AD5293_OK, AD5293_ERR, etc.)
 */
extern AD5293_Status_t AD5293_Init(AD5293_Handle_t *handle, AD5293_Conf_t *conf);

/**
 * @brief Read the current RDAC code from the AD5293
 * 
 * @param handle AD5293 device handle
 * @param buffer Pointer to a uint16_t variable to store RDAC code
 * @return AD5293_Status_t Status of the read operation
 */
extern AD5293_Status_t AD5293_ReadRDAC(AD5293_Handle_t handle, uint16_t *buffer);

/**
 * @brief Write a raw RDAC code to the AD5293
 * 
 * @param handle AD5293 device handle
 * @param buffer RDAC code (0 ~ 1023 for 10-bit device)
 * @return AD5293_Status_t Status of the write operation (AD5293_OK, AD5293_OVERFLOW)
 */
extern AD5293_Status_t AD5293_WriteRDAC(AD5293_Handle_t handle, uint16_t buffer);

/**
 * @brief Configure write-protection and working mode
 * 
 * @param handle AD5293 device handle
 * @param en Enable/disable write protection (AD5293_WriteProtect_t)
 * @param mode Device work mode (AD5293_WorkMode_t)
 * @return AD5293_Status_t Status of the configuration operation
 */
extern AD5293_Status_t AD5293_WritePortect(AD5293_Handle_t handle, AD5293_WriteProtect_t en, AD5293_WorkMode_t mode);

/**
 * @brief Set the output resistance of the AD5293
 * 
 * Converts a desired resistance to the corresponding 10-bit RDAC code
 * and writes it to the device.
 * 
 * @param handle AD5293 device handle
 * @param resistance Desired resistance in Ohms (capped by RAB)
 * @return AD5293_Status_t Status of the operation
 */
extern AD5293_Status_t AD5293_SetResistance(AD5293_Handle_t handle, uint16_t resistance);

/**
 * @brief Get the actual output resistance of the AD5293
 * 
 * Reads the RDAC code from the device and converts it to resistance in Ohms.
 * 
 * @param handle AD5293 device handle
 * @param buffer Pointer to a uint16_t variable to store resistance
 * @return AD5293_Status_t Status of the operation
 */
extern AD5293_Status_t AD5293_GetResistance(AD5293_Handle_t handle, uint16_t *buffer);

/**
 * @brief De-initialize the AD5293 handle and free resources
 * 
 * @param handle Pointer to the handle variable to de-initialize
 * @return AD5293_Status_t Status of the de-initialization
 */
extern AD5293_Status_t AD5293_DeInit(AD5293_Handle_t *handle);

#if AD5293_USE_HW_RESET
/**
 * @brief Perform a hardware reset of the AD5293 via RESET pin
 * 
 * Requires AD5293_USE_HW_RESET = 1 and the reset function callback to be registered.
 * Resets the RDAC register to midscale.
 * 
 * @param handle AD5293 device handle
 * @return AD5293_Status_t Status of the hardware reset
 */
extern AD5293_Status_t AD5293_HardwareReset(AD5293_Handle_t handle);
#endif

/**
 * @brief Perform a software reset of the AD5293
 * 
 * Sends the RESET command via SPI, setting the RDAC register to midscale.
 * 
 * @param handle AD5293 device handle
 * @return AD5293_Status_t Status of the software reset
 */
extern AD5293_Status_t AD5293_SoftWareReset(AD5293_Handle_t handle);

#ifdef __cplusplus
}
#endif

#endif //! __AD5293_H_
