/**
 * @file AD5293_conf.h
 * @author https://github.com/xfp23/
 * @brief AD5293 Driver configuration (user-readable)
 * @version 0.1
 * @date 2025-12-11
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef __AD5293_CONF_H_
#define __AD5293_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************
 * User Configuration Section
 * 
 * This section is for documentation and user reference.
 * Only AD5293_USE_HW_RESET is active in code.
 ************************************************************/

/**
 * SPI mode selection (documentation only)
 * Options (user should connect hardware accordingly):
 * - Mode 0: CPOL = 0, CPHA = 0
 * - Mode 1: CPOL = 0, CPHA = 1
 * - Mode 2: CPOL = 1, CPHA = 0
 * - Mode 3: CPOL = 1, CPHA = 1
 */
#define AD5293_SPI_MODE      /* Documentation only, see your SPI driver */

/**
 * SPI clock speed (documentation only)
 * Example: 1 MHz ~ 5 MHz depending on system
 */
#define AD5293_SPI_CLOCK     /* Documentation only */

/**
 * Hardware Reset enable/disable
 * 1: use HW reset pin
 * 0: do not use HW reset
 */
#define AD5293_USE_HW_RESET   1  /* Active in code */

#ifdef __cplusplus
}
#endif

#endif /* __AD5293_CONF_H_ */
