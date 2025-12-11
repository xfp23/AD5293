---

[中文](./readme.zh.md)

---

# AD5293 Digital Potentiometer Driver

## Overview

This is a simple driver for the AD5293 10-bit digital potentiometer.
It provides APIs to initialize the device, read/write RDAC values, configure protection, perform reset, and set/get output resistance.

---

## API Reference

### Initialization

```c
AD5293_Status_t AD5293_Init(AD5293_Handle_t *handle, AD5293_Conf_t *conf);
```

* **Description:** Initialize the AD5293 device, register SPI callbacks, and set device type.
* **Parameters:**

  * `handle` : Pointer to the device handle.
  * `conf` : Configuration structure containing SPI functions, reset function (optional), and device type.
* **Returns:** `AD5293_Status_t`

---

### Read RDAC Code

```c
AD5293_Status_t AD5293_ReadRDAC(AD5293_Handle_t handle, uint16_t *buffer);
```

* **Description:** Read the current RDAC code from the device.
* **Parameters:**

  * `handle` : Device handle.
  * `buffer` : Pointer to store 10-bit RDAC value.
* **Returns:** `AD5293_Status_t`

---

### Write RDAC Code

```c
AD5293_Status_t AD5293_WriteRDAC(AD5293_Handle_t handle, uint16_t buffer);
```

* **Description:** Write a 10-bit RDAC code to the device.
* **Parameters:**

  * `handle` : Device handle.
  * `buffer` : RDAC value (0 ~ 1023).
* **Returns:** `AD5293_Status_t`

---

### Configure Write Protection

```c
AD5293_Status_t AD5293_WritePortect(AD5293_Handle_t handle, AD5293_WriteProtect_t en, AD5293_WorkMode_t mode);
```

* **Description:** Enable or disable write protection and set device working mode.
* **Parameters:**

  * `handle` : Device handle.
  * `en` : `AD5293_WriteProtect_t`, write protection enable/disable.
  * `mode` : `AD5293_WorkMode_t`, device operating mode.
* **Returns:** `AD5293_Status_t`

---

### Set Resistance

```c
AD5293_Status_t AD5293_SetResistance(AD5293_Handle_t handle, uint16_t resistance);
```

* **Description:** Convert desired resistance to RDAC code and write to device.
* **Parameters:**

  * `handle` : Device handle.
  * `resistance` : Desired resistance in Ohms (limited by device RAB).
* **Returns:** `AD5293_Status_t`

---

### Get Resistance

```c
AD5293_Status_t AD5293_GetResistance(AD5293_Handle_t handle, uint16_t *buffer);
```

* **Description:** Read RDAC code and convert to actual resistance.
* **Parameters:**

  * `handle` : Device handle.
  * `buffer` : Pointer to store resistance in Ohms.
* **Returns:** `AD5293_Status_t`

---

### Software Reset

```c
AD5293_Status_t AD5293_SoftWareReset(AD5293_Handle_t handle);
```

* **Description:** Perform a software reset, setting RDAC to midscale.
* **Parameters:**

  * `handle` : Device handle.
* **Returns:** `AD5293_Status_t`

---

### Hardware Reset (optional)

```c
AD5293_Status_t AD5293_HardwareReset(AD5293_Handle_t handle);
```

* **Description:** Perform hardware reset via RESET pin (requires `AD5293_USE_HW_RESET = 1`).
* **Parameters:**

  * `handle` : Device handle.
* **Returns:** `AD5293_Status_t`

---

### Shutdown / Power Down

```c
AD5293_Status_t AD5293_SetPower(AD5293_Handle_t handle, AD5293_Pwr_t pwr);
```

* **Description:** Put the device into shutdown or normal operation mode. Controls power down via D0 bit.

* **Parameters:**

  * `handle` : Device handle.
  * `pwr` : `AD5293_Pwr_t` enum, selects shutdown or normal mode.

* **Returns:** `AD5293_Status_t`

---

### De-initialize

```c
AD5293_Status_t AD5293_DeInit(AD5293_Handle_t *handle);
```

* **Description:** Free resources and de-initialize the device handle.
* **Parameters:**

  * `handle` : Pointer to device handle.
* **Returns:** `AD5293_Status_t`

---

## Data Types

* **`AD5293_Handle_t`** : Opaque pointer to device instance.
* **`AD5293_Conf_t`** : Configuration struct containing SPI callbacks, device type, and optional reset function.
* **`AD5293_Status_t`** : Return status (OK, OVERFLOW, ERROR, etc.).
* **`AD5293_WriteProtect_t`** : Write protection enable/disable enum.
* **`AD5293_WorkMode_t`** : Device operating mode enum.

---

## Notes

* The device supports 10-bit RDAC (0–1023).
* Maximum SPI clock should be ≤ 5 MHz for reliable operation.
* Hardware reset is optional; software reset always works.

---
