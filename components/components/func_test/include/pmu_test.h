/* \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2025-05-16 <td>V0.0  <td>WCH   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _PMU_TEST_H
#define _PMU_TEST_H

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "soc.h"
#include "sys_clk.h"
#include <drv/pin.h>
#include <iostring.h>

extern void deepsleep_mode_test(void);
extern void shutdown_mode_test(void);
extern void shutdown_rtc_wakeup_test(void);
extern void retention_sram_test(void);

#endif