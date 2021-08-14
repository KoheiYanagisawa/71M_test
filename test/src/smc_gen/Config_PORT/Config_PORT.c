/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : Config_PORT.c
* Version      : 2.1.3
* Device(s)    : R5F571MFCxFP
* Description  : This file implements device driver for Config_PORT.
* Creation Date: 2021-08-14
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "Config_PORT.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_PORT_Create
* Description  : This function initializes the PORT
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_PORT_Create(void)
{
    /* Set PORT1 registers */
    PORT1.ODR0.BYTE = _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT1.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;

    /* Set PORTB registers */
    PORTB.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm4_OUTPUT_0;
    PORTB.ODR0.BYTE = _01_Pm0_NCH_OPEN_DRAIN | _00_Pm1_CMOS_OUTPUT | _10_Pm2_NCH_OPEN_DRAIN | _00_Pm3_CMOS_OUTPUT;
    PORTB.ODR1.BYTE = _01_Pm4_NCH_OPEN_DRAIN | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORTB.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm4_HIDRV_OFF;
    PORTB.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm4_PIN_GPIO;
    PORTB.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _10_Pm4_MODE_OUTPUT;

    R_Config_PORT_Create_UserInit();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
