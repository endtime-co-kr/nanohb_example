/*	sciulpdefs.h : include file for mockingjay definitions
 *	
 * Author: SignalCore Inc
 * copyright 2021 SignalCore Inc
 * rev 1.0.0
*/

#pragma once

#ifndef SCIULPREGS_H_
#define SCIULPREGS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*
 *	Registers
*/
// Define user device registers
#define REG_DUMMY							0x00
#define REG_INITIALIZE						0x01    // Initialize the devices
#define REG_RESERVED0						0x02   
#define REG_RESERVED1						0x03 
#define REG_RESERVED2						0x04	
#define REG_LIST_MODE_CONFIG				0x05	// modes for list/sweep, such as trigger types
#define REG_SWEEP_START_FREQ				0x06	//
#define REG_SWEEP_STOP_FREQ					0x07	//
#define REG_SWEEP_STEP_FREQ					0x08	//
#define REG_SWEEP_DWELL_TIME				0x09    // for sweep dwell time
#define REG_SWEEP_CYCLE_COUNT				0x0A	// number of cycles for sweep/list
#define REG_LIST_BUFFER_WRITE				0x0B    // list frequencies
#define REG_LIST_BUFFER_TRANSFER			0x0C	// transfer to/from EEPROM into buffer memory
#define REG_RESERVED3						0x0D    
#define REG_RESERVED4						0x0E
#define REG_LIST_SOFT_TRIGGER				0x0F	//Soft Trigger

//
#define REG_RF_FREQUENCY					0x10	// set the CW signal frequency
#define REG_RF_PHASE						0x11	// set the relative phase of signal
#define REG_STORE_DEFAULT_STATE				0x12    // Save current settings as default
#define REG_SYNTH_SELF_CAL					0x13	// Self Calibrate 
#define REG_SYNTH_MODE						0x14	// sets fixed/list and harmonic/fracN and PLL loopGain
#define REG_SERIAL_CONFIG					0x15	// configure the UART baudrate, and SPI mode

#define REG_GET_DEVICE_PARAM				0x20	// Get the frequency related parameters
#define REG_GET_DEVICE_INFO					0x21	// Get dvice info such such firmware, model ...
#define REG_GET_TEMPERATURE					0x22	// Get device temperature
#define REG_LIST_BUFFER_READ				0x23	// read the frequency data in the list buffer
#define REG_CAL_EEPROM_READ					0x24    // read eeprom, 8 bytes per transfer (U64 read)
#define REG_SERIAL_OUT_BUFFER				0x25    // transfer user EEPROM data to SPI output buffer

#ifdef __cplusplus
}
#endif

#	endif  /* ___H__ */	

