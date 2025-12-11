/**
 * @file AD5293_com.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __AD5293_COM_H_
#define __AD5293_COM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define __AD5293_CHECKPARAM(x) do \
{ \
    if(x == NULL) \
    { \
        return AD5293_INVALID_PARAM;\
    }\
} while (0)

#define __AD5293_CHECKPTR(x) do \
{ \
    if(x == NULL) \
    { \
        return AD5293_ERR;\
    }\
} while (0)

#define __AD5293_CHECKObj(x) do \
{ \
    if(x != NULL) \
    { \
        return AD5293_ALREADY_INITED;\
    }\
} while (0)

#define __AD5293_CHECKBUSY(x) do \
{ \
    if(x->RDY) \
    { \
        return AD5293_BUSY;\
    }\
} while(0)

#ifdef __cplusplus
}
#endif

#endif