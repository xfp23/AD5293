#include "AD5293.h"
#include "AD5293_com.h"
#include "stdlib.h"

AD5293_Status_t AD5293_Init(AD5293_Handle_t *handle, AD5293_Conf_t *conf)
{
    __AD5293_CHECKPARAM(handle);
    __AD5293_CHECKPARAM(conf);
    __AD5293_CHECKPARAM(conf->cs_func);
    __AD5293_CHECKPARAM(conf->trans_func);
    __AD5293_CHECKPARAM(conf->recv_func);
#if AD5293_USE_HW_RESET
    __AD5293_CHECKPARAM(conf->reset_func);
#endif
    __AD5293_CHECKObj(*handle);

    AD5293_Obj_t *obj = (AD5293_Obj_t *)calloc(1, sizeof(AD5293_Obj_t));

    __AD5293_CHECKPTR(obj);

    // 注册API
    obj->Readbyte = conf->recv_func;
    obj->Writebyte = conf->trans_func;
    obj->cs = conf->cs_func;
    obj->reset = conf->reset_func;

    switch (conf->type)
    {
    case AD5293_TYPE_10K:
        obj->rab_ohm = 10000;
        break;
    case AD5293_TYPE_50K:
        obj->rab_ohm = 50000;
        break;
    case AD5293_TYPE_100K:
        obj->rab_ohm = 100000;
        break;
    default:
        break;
    }

#if AD5293_USE_HW_RESET
    obj->reset();
#elif
    AD5293_SoftWareReset(obj);
#endif
    *handle = obj;

    return AD5293_OK;
}

AD5293_Status_t AD5293_ReadRDAC(AD5293_Handle_t handle, uint16_t *buffer)
{
    __AD5293_CHECKPARAM(handle);
    __AD5293_CHECKPARAM(buffer);

    AD5293_Frame_t frame = {0};
    frame.bits.command = AD5293_RD_RDAC;
    handle->cs(0);
    handle->Writebyte(frame.raw, 2); // 写入2字节

    handle->Readbyte(frame.raw, 2); // 读取2字节
    handle->cs(1);                  // 片选

    *buffer = frame.bits.value;
    return AD5293_OK;
}

AD5293_Status_t AD5293_WriteRDAC(AD5293_Handle_t handle, uint16_t buffer)
{
    __AD5293_CHECKPARAM(handle);

    if (buffer > 0x3FF)
        return AD5293_OVERFLOW;


    AD5293_Frame_t frame = {0};
    frame.bits.command = AD5293_WR_RDAC;

    frame.bits.value = buffer;

    handle->cs(0); // 拉低

    handle->Writebyte(frame.raw, 2);

    handle->cs(1); // 拉高

    return AD5293_OK;
}

AD5293_Status_t AD5293_WritePortect(AD5293_Handle_t handle, AD5293_WriteProtect_t en, AD5293_WorkMode_t mode)
{
    __AD5293_CHECKPARAM(handle);
    AD5293_Frame_t frame = {0};
    frame.bits.command = AD5293_WR_CTRL;
    frame.bits.value = (((uint8_t)en << 1) | ((uint8_t)mode << 2));

    handle->cs(0);

    handle->Writebyte(frame.raw, 2);
    handle->cs(1);

    return AD5293_OK;
}

AD5293_Status_t AD5293_SoftWareReset(AD5293_Handle_t handle)
{
    __AD5293_CHECKPARAM(handle);
    AD5293_Frame_t frame = {0};
    frame.bits.command = AD5293_RESET;

    handle->cs(0);

    handle->Writebyte(frame.raw, 2);
    handle->cs(1);

    return AD5293_OK;
}

#if AD5293_USE_HW_RESET
AD5293_Status_t AD5293_HardwareReset(AD5293_Handle_t handle)
{
    __AD5293_CHECKPARAM(handle);

    handle->reset();

    return AD5293_OK;
}
#endif

AD5293_Status_t AD5293_SetResistance(AD5293_Handle_t handle, uint16_t resistance)
{
    __AD5293_CHECKPARAM(handle);

    uint32_t rab = handle->rab_ohm;
    if (rab == 0)
        return AD5293_ERR;

    if (resistance > rab)
        resistance = rab; // 限幅

    uint32_t code = (uint32_t)resistance * 1024 / rab;
    if (code > 0x3FF)
        code = 0x3FF;

    return AD5293_WriteRDAC(handle, (uint16_t)code);
}

AD5293_Status_t AD5293_GetResistance(AD5293_Handle_t handle, uint16_t *buffer)
{
    __AD5293_CHECKPARAM(handle);
    __AD5293_CHECKPARAM(buffer);

    uint16_t code = 0;
    AD5293_Status_t ret = AD5293_ReadRDAC(handle, &code);
    if (ret != AD5293_OK)
        return ret;

    uint32_t rab = handle->rab_ohm;
    if (rab == 0)
        return AD5293_ERR;

    // Rwb = D / 1024 * RAB
    uint32_t resistance = (uint32_t)code * rab / 1024;

    *buffer = (uint16_t)resistance;

    return AD5293_OK;
}

AD5293_Status_t AD5293_DeInit(AD5293_Handle_t *handle)
{
    __AD5293_CHECKPARAM(handle);
    __AD5293_CHECKPARAM(*handle);

    free(*handle);
    (*handle) = NULL;

    return AD5293_OK;
}

AD5293_Status_t AD5293_SetPower(AD5293_Handle_t handle,AD5293_Pwr_t pwr)
{
    __AD5293_CHECKPARAM(handle);

    AD5293_Frame_t frame = {0};
    frame.bits.command = AD5293_PWRDN;
    frame.bits.value = (uint8_t)pwr; // D0位
    handle->cs(0);
    handle->Writebyte(frame.raw,2);
    handle->cs(1);

    return AD5293_OK;
}