/*	nanohb_defs.h : include file for mockingjay definitions
 *	
 * Author: SignalCore Inc
 * copyright 2021 SignalCore Inc
 * rev 1.0.0
*/

#pragma once

#ifndef NANOHB_DEFS_H_
#define NANOHB_DEFS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "sci_types.h"

#define SCI_USB_VID						0x277C
#define SCI_USB_PID						0x0035

#define MAX_PORT_NAME_LEN				0x012
#define SCI_SN_LENGTH					0x09

#define SC801A_INDEX					0x01
#define SC802A_INDEX					0x02


/** 
 * Device types this API supports
 */

enum LOOPGAIN	/* pll loop gain*/
{
	LOW,
	MIDIUM, /* factory default*/
	HIGH
};


/*
 * Structure types to hold data
*/

typedef struct _synthMode_s
{
	uint8_t rfMode;  /**< 0 fixed freq, 1 sweep */
	uint8_t loopGain; /**< 0 normal, 1 high */
	uint8_t lockMode; /**< 0 harmonic mode, fracN mode */
	uint8_t freqResln; /**< frequency resolution : 0 - 1 Hz step, 1 - 0.001 Hz step */
	uint8_t autoSpurSuppress; /**< only in harmonic lock mode, enable synth to swtich between
								 lockModes to minimize spurs */
} synthMode_t;

typedef struct _pllStatus_s
{
	uint8_t sumPllLD;	/**< Main sum pll lock detect status */
	uint8_t crsPllLD;	/**< Coarse Harmonic pll lock detect status */
	uint8_t finePllLD;	/**< Fine clock pll lock detect status */
	uint8_t crsIntNPllLD;	/**< Coarse Fractional-N mode pll lock detect status */
	uint8_t crsRefPllLD;	/**< Coarse reference clock pll lock detect status */
	uint8_t sysPllLD;	/**< System clk pll lock detect status */
} pllStatus_t;

typedef struct _operateStatus_s
{
	synthMode_t synthMode;
	uint8_t overTemp;	/**< no/yes */
	uint8_t listModeRunning; /**< no/yes */
	uint8_t uartPinSet;	/**< default (0) for 57600 baud / software selected(1) see next */
	uint8_t selectedBaud; /**< 0=57600, 1=115200, 2=19200, 3=38400, 4=230400,
							 5=460800, 6=921600, 7=1843200 (pin must be pulled high) */
	uint8_t reserved;
} operateStatus_t;

typedef struct _sweepConfig_s
{
	uint8_t useBufferList; /**< use the list loaded into device memory */
	uint8_t sweepDirection; /**< 0-> start to stop, 1-> stop to start */ 
	uint8_t sweepPattern; /**< 0-> trigular start->stop->stop->start, 1-> sawtooth start->stop-start */
	uint8_t returnToStart; /**< On completion of the sweep cycles, the frequency returns to the start */
	uint8_t hwTrig; /**< 0-> software trigger, 1-> hardware trigger */
	uint8_t trigMode; /**< 0-> start on 1st trigger and stop on next, 1-> freq step on each trigger */
	uint8_t TrigOutEnable; /**< enable a trigger pulse on the trigger out pin */
	uint8_t reserved; /**< set to 0 */
} sweepConfig_t;

typedef struct _deviceStatus_s
{
	pllStatus_t	pllStatus;
	operateStatus_t operateStatus;
}	deviceStatus_t;  

typedef struct _sciDate_s
{
	uint8_t day;
	uint8_t month;
	uint8_t year;
} sciDate_t;

typedef struct version_s
{
	uint8_t fix;
	uint8_t minor;
	uint8_t major;
} version_t;

typedef struct device_model_s
{
	uint8_t modelNumber; /**< 0-> SC801, 1-> SC802 */ 
	uint8_t modelOption; /**< any options applied to the device */
} device_model_t;

typedef struct _deviceInfo_s
{
	uint32_t productSerialNumber;
	device_model_t model; 
	uint8_t serialInterface; /**< presence of USB, or/and SPI, or/and UART */
	version_t firmwareVersion;
	version_t hardwareVersion;
	sciDate_t manDate;
} deviceInfo_t;

typedef struct _rfParams_s
{
	double frequency; /**<final synthesizer(RF) frequency */
	double phase; /**< the phase off of the signal */
	double sweepStartFreq; /**< Start frequency of the sweep*/
	double sweetStopFreq; /**< Stop frequency of the the sweep*/
	double sweetStepFreq; /**< Step frequency size of the sweep*/
	float sweepDwellTime; /**< Monotonic sweep dwell time per point */
	uint32_t sweepCycles; /**< number of sweep cycles */
	uint32_t sweepPoints; /**< current number of sweep points */
	uint32_t listBufferPoints; /**< number points in list buffer */
	sweepConfig_t sweepConfig; /**< Configuration for the sweep or list */
} rfParams_t;

#ifdef __cplusplus
}
#endif

#	endif  /* NANOHB_DEFS_H_ */	

