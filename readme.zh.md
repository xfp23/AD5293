---

[English](./readme.md)

---

# AD5293 数字电位器驱动

## 概述

这是一个针对 AD5293 10 位数字电位器的简单驱动。
提供 API 来初始化设备、读写 RDAC 值、配置写保护、执行复位，以及设置/获取输出阻值。

---

## API 参考

### 初始化

```c
AD5293_Status_t AD5293_Init(AD5293_Handle_t *handle, AD5293_Conf_t *conf);
```

* **描述：** 初始化 AD5293 设备，注册 SPI 回调函数，并设置设备类型。
* **参数：**

  * `handle` : 指向设备句柄的指针。
  * `conf` : 配置结构体，包含 SPI 回调函数、可选的复位函数和设备类型。
* **返回值：** `AD5293_Status_t`

---

### 读取 RDAC 值

```c
AD5293_Status_t AD5293_ReadRDAC(AD5293_Handle_t handle, uint16_t *buffer);
```

* **描述：** 读取设备当前 RDAC 代码。
* **参数：**

  * `handle` : 设备句柄。
  * `buffer` : 指向存储 10 位 RDAC 值的指针。
* **返回值：** `AD5293_Status_t`

---

### 写入 RDAC 值

```c
AD5293_Status_t AD5293_WriteRDAC(AD5293_Handle_t handle, uint16_t buffer);
```

* **描述：** 向设备写入 10 位 RDAC 代码。
* **参数：**

  * `handle` : 设备句柄。
  * `buffer` : RDAC 值 (0 ~ 1023)。
* **返回值：** `AD5293_Status_t`

---

### 配置写保护

```c
AD5293_Status_t AD5293_WritePortect(AD5293_Handle_t handle, AD5293_WriteProtect_t en, AD5293_WorkMode_t mode);
```

* **描述：** 启用或禁用写保护，并设置设备工作模式。
* **参数：**

  * `handle` : 设备句柄。
  * `en` : `AD5293_WriteProtect_t`，写保护使能/禁用。
  * `mode` : `AD5293_WorkMode_t`，设备工作模式。
* **返回值：** `AD5293_Status_t`

---

### 设置阻值

```c
AD5293_Status_t AD5293_SetResistance(AD5293_Handle_t handle, uint16_t resistance);
```

* **描述：** 将目标阻值转换为 RDAC 代码并写入设备。
* **参数：**

  * `handle` : 设备句柄。
  * `resistance` : 目标阻值，单位欧姆 (受设备 RAB 限制)。
* **返回值：** `AD5293_Status_t`

---

### 获取阻值

```c
AD5293_Status_t AD5293_GetResistance(AD5293_Handle_t handle, uint16_t *buffer);
```

* **描述：** 读取 RDAC 代码并转换为实际阻值。
* **参数：**

  * `handle` : 设备句柄。
  * `buffer` : 指向存储阻值的指针，单位欧姆。
* **返回值：** `AD5293_Status_t`

---

### 软件复位

```c
AD5293_Status_t AD5293_SoftWareReset(AD5293_Handle_t handle);
```

* **描述：** 执行软件复位，将 RDAC 设置到中间刻度。
* **参数：**

  * `handle` : 设备句柄。
* **返回值：** `AD5293_Status_t`

---

### 硬件复位（可选）

```c
AD5293_Status_t AD5293_HardwareReset(AD5293_Handle_t handle);
```

* **描述：** 通过 RESET 引脚执行硬件复位（需要 `AD5293_USE_HW_RESET = 1`）。
* **参数：**

  * `handle` : 设备句柄。
* **返回值：** `AD5293_Status_t`

---
好的，这里是新增 API 的 **中文文档部分**：

---

### 关机 / 电源控制

```c
AD5293_Status_t AD5293_SetPower(AD5293_Handle_t handle, AD5293_Pwr_t pwr);
```

* **描述:** 将器件置于关机或正常工作模式，通过 D0 位控制电源状态。

* **参数:**

  * `handle` : 设备句柄。
  * `pwr` : `AD5293_Pwr_t` 枚举类型，选择关机或正常模式。

* **返回值:** `AD5293_Status_t`

---

### 反初始化

```c
AD5293_Status_t AD5293_DeInit(AD5293_Handle_t *handle);
```

* **描述：** 释放资源并反初始化设备句柄。
* **参数：**

  * `handle` : 指向设备句柄的指针。
* **返回值：** `AD5293_Status_t`

---

## 数据类型

* **`AD5293_Handle_t`** : 指向设备实例的不透明指针。
* **`AD5293_Conf_t`** : 配置结构体，包含 SPI 回调函数、设备类型和可选复位函数。
* **`AD5293_Status_t`** : 返回状态 (OK、OVERFLOW、ERROR 等)。
* **`AD5293_WriteProtect_t`** : 写保护使能/禁用枚举。
* **`AD5293_WorkMode_t`** : 设备工作模式枚举。

---

## 注意事项

* 设备支持 10 位 RDAC (0–1023)。
* 为保证可靠性，SPI 时钟最大应 ≤ 5 MHz。
* 硬件复位为可选；软件复位总是可用。

---
