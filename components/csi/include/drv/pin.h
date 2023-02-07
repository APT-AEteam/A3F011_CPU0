/*
 * Copyright (C) 2017-2020 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     soc.h
 * @brief    For pin
 * @version  V1.0
 * @date     11. Mar 2020
 ******************************************************************************/

#ifndef _DRV_PIN_H_
#define _DRV_PIN_H_

#include <drv/common.h>
#include <soc.h>
#include <drv/gpio.h>

//typedef enum{
//    PIN_UART_TX		= 0U,
//    PIN_UART_RX,
//    PIN_UART_CTS,
//    PIN_UART_RTS
//}csi_pin_uart_t;

//typedef enum{
//    PIN_IIC_SCL		= 0U,
//    PIN_IIC_SDA
//}csi_pin_iic_t;

//typedef enum{
//    PIN_SPI_MISO	= 0U,
//    PIN_SPI_MOSI,
//    PIN_SPI_SCK,
//    PIN_SPI_CS
//}csi_pin_spi_t;

//typedef enum{
//    PIN_I2S_MCLK	= 0U,
//    PIN_I2S_SCLK,
//    PIN_I2S_WSCLK,
//    PIN_I2S_SDA
//}csi_pin_i2s_t;

//typedef struct {
//    pin_name_e  pin_name;
//    uint8_t     idx;        //ctrl idx.    e.g: ADC0 channel 1, idx = 0, channel = 1
//    uint8_t     channel;    //channel idx. e.g: same as the previous line
//    pin_func_e  pin_func;
//} csi_pinmap_t;
//
//extern uint32_t target_pin_to_devidx(pin_name_e pin_name, const csi_pinmap_t *pinmap);
//extern uint32_t target_pin_to_channel(pin_name_e pin_name,const csi_pinmap_t *pinmap);
//extern pin_name_e target_gpio_to_pin(uint8_t gpio_idx, uint8_t channel,const csi_pinmap_t *pinmap);

/**
  \brief       Set pin mux function
  \param[in]   ePinName    pin name, defined in soc.h
  \param[in]   ePinFunc    pin function, defined in soc.h
  \return      none
*/
void csi_pin_set_mux(pin_name_e ePinName, pin_func_e ePinFunc);

/**
  \brief       Get pin function
  \param[in]   ePinName    pin name, defined in soc.h
  \return      pin function
*/
pin_func_e csi_pin_get_mux(pin_name_e ePinName);

/**
  \brief       Set pin mode
  \param[in]   ePinName    pin name, defined in soc.h
  \param[in]   ePullMode   pull mode, pull none/pull up/pull down
  \return      \ref  csi_error_t
*/
csi_error_t csi_pin_pull_mode(pin_name_e ePinName, csi_gpio_pull_mode_e ePullMode);

/**
  \brief       Set pin speed
  \param[in]   ePinName    pin name, defined in soc.h
  \param[in]   eSpeed      io speed
  \return      none
*/
void csi_pin_speed(pin_name_e ePinName, csi_gpio_speed_e eSpeed);

/**
  \brief       Set pin drive
  \param[in]   ePinName    pin name, defined in soc.h
  \param[in]   eDrive      io drive
  \return      \ref  csi_error_t
*/
csi_error_t csi_pin_drive(pin_name_e ePinName, csi_gpio_drive_e eDrive);

/** 
  \brief 	   set gpio pin input mode
  \param[in]   ePinName		gpio pin name, defined in soc.h.
  \param[in]   eInputMode	INPUT_CMOS/INPUT_TTL
  \return 	   error code \ref csi_error_t
 */ 
csi_error_t csi_pin_input_mode(pin_name_e ePinName, csi_gpio_input_mode_e eInputMode);

/** 
  \brief       set gpio pin out mode
  \param[in]   ePinName		gpio pin name, defined in soc.h.
  \param[in]   eOutMode		push-pull/open drain
  \return      error code \ref csi_error_t
 */ 
csi_error_t csi_pin_output_mode(pin_name_e ePinName, csi_gpio_output_mode_e eOutMode);

/** 
  \brief       get gpio pin num
  \param[in]   ePinName	 	gpio pin name, defined in soc.h.
  \return      pin num
 */
uint8_t csi_pin_get_num(pin_name_e ePinName);

/** 
  \brief 	   Get the value of  selected pin 
  \param[in]   ePinName		gpio pin name, defined in soc.h.
  \return 	   According to the bit mask, the corresponding pin status is obtained
*/
uint32_t csi_pin_read(pin_name_e ePinName);

/** 
  \brief       config pin irq mode(assign exi group)
  \param[in]   ePinName		pin name
  \param[in]   eExiGrp		exi group; EXI_GRP0 ~EXI_GRP19
  \param[in]   eTrgEdge		rising edge; falling edge;	both edge;
  \return      error code \ref csi_error_t
 */ 
csi_error_t csi_pin_irq_mode(pin_name_e ePinName, csi_exi_grp_e eExiGrp, csi_gpio_irq_mode_e eTrgEdge);

/** 
  \brief pin irq enable
  \param[in] ePinName: pio pin name, defined in soc.h.
  \param[in] bEnable: ENABLE OR DISABLE
  \return none
 */ 
void csi_pin_irq_enable(pin_name_e ePinName, bool bEnable);

/** 
  \brief exi line group select
  \param[in] exi line: exi line; EXI_LINE0~15
  \param[in] eGroup: \ref csi_exi_line_grp_e 
  \param[in] ePinName: pio pin name, defined in soc.h.
  \return none
 */ 
csi_error_t csi_exi_line_set_group(csi_exi_line_e eLine, csi_exi_line_grp_e eGroup, pin_name_e ePinName);

/** 
  \brief exi line irq mode config
  \param[in] eLine: exi line; EXI_LINE0~15
  \param[in] eMode: or/and \ref csi_exi_line_mode_e
  \param[in] eEdge: rising/falling/both
  \return none
 */ 
void csi_exi_line_irq_mode(csi_exi_line_e eLine, csi_exi_line_mode_e eMode, csi_exi_line_adge_e eEdge);

/** 
  \brief exi line irq enable
  \param[in] eLine: exi line; EXI_LINE0~15
  \param[in] bEnable: ENABLE OR DISABLE
  \return none
 */ 
void csi_exi_line_irq_enable(csi_exi_line_e eLine, bool bEnable);

/** \brief pin vic irq enable
 * 
 *  \param[in] eLine: exi line, EXI_LINE0 ~EXI_LINE15
 *  \param[in] bEnable: ENABLE OR DISABLE
 *  \return none
 */
void csi_exi_line_vic_irq_enable(csi_exi_line_e eLine, bool bEnable);

/** 
  \brief  	   gpio toggle
  \param[in]   pin_name		gpio pin name
  \return      none
 */
void csi_pin_toggle(pin_name_e ePinName);

/** 
  \brief  	   gpio pin set high(output = 1)
  \param[in]   ePinName		gpio pin name
  \return      none
 */
void csi_pin_set_high(pin_name_e ePinName);

/** 
  \brief   	   gpio pin set low(output = 0)
  \param[in]   ePinName		gpio pin name
  \return      none
 */
void csi_pin_set_low(pin_name_e ePinName);

/** \brief  set exi as trigger Event(EV0~5) 
  \param[in]   byTrgOut		output Event select(TRGOUT0~5)
  \param[in]   eTrgSrc 	event source (TRGSRC_EXI0~19)
  \param       eTrgAdge 	accumulated EXI events to output trigger 
  \return 	   error code \ref csi_error_t
 */ 
csi_error_t csi_exi_set_evtrg(csi_exi_trgout_e eTrgOut, csi_exi_trgsrc_e eTrgSrc, csi_exi_trgadge_e eTrgAdge);

/** 
  \brief exi evtrg output enable/disable
  \param[in] eTrgOut: exi evtrg out port (0~5)
  \param[in] bEnable: ENABLE/DISABLE
  \return error code \ref csi_error_t
 */
csi_error_t csi_exi_evtrg_enable(csi_exi_trgout_e eTrgOut, bool bEnable);


//__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_gpio_devidx(pin_name_e pin_name)
//{
//    extern const csi_pinmap_t gpio_pinmap[];
//    return target_pin_to_devidx(pin_name, gpio_pinmap);
//}
//
//__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_uart_devidx(pin_name_e pin_name)
//{
//    extern const csi_pinmap_t uart_pinmap[];
//    return target_pin_to_devidx(pin_name, uart_pinmap);
//}

//__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_iic_devidx(pin_name_e pin_name)
//{
//    extern const csi_pinmap_t iic_pinmap[];
//    return target_pin_to_devidx(pin_name, iic_pinmap);
//}
//
//__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_spi_devidx(pin_name_e pin_name)
//{
//    extern const csi_pinmap_t spi_pinmap[];
//    return target_pin_to_devidx(pin_name, spi_pinmap);
//}
//
//__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_i2s_devidx(pin_name_e pin_name)
//{
//    extern  const csi_pinmap_t i2s_pinmap[];
//    return target_pin_to_devidx(pin_name, i2s_pinmap);
//}

/**
  \brief       Get channel by pin
  \param[in]   pin_name    pin name, defined in soc.h
  \return      channel
*/
//__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_adc_channel(pin_name_e pin_name)
//{
//    extern const csi_pinmap_t adc_pinmap[];
//    return target_pin_to_channel(pin_name, adc_pinmap);
//}

//__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_pwm_channel(pin_name_e pin_name)
//{
//    extern const csi_pinmap_t pwm_pinmap[];
//    return target_pin_to_channel(pin_name, pwm_pinmap);
//}

//__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_gpio_channel(pin_name_e pin_name)
//{
//    extern const csi_pinmap_t gpio_pinmap[];
//    return target_pin_to_channel(pin_name, gpio_pinmap);
//}

/**
  \brief       Get pin name by gpio ctrl idx and channel
  \param[in]   gpio_idx    idx, defined in soc.h
  \param[in]   channel     channel, defined in soc.h
  \return      pin name
*/
//__ALWAYS_STATIC_INLINE pin_name_e csi_pin_get_pinname_by_gpio(uint8_t gpio_idx, uint8_t channel)
//{
//    extern const csi_pinmap_t gpio_pinmap[];
//    return target_gpio_to_pin(gpio_idx,channel,gpio_pinmap);
//}

#endif /* _DRV_PIN_H_ */
