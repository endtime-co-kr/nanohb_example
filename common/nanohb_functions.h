/**
 * Header functions for nanoSYnth Hummingbird
 *
 *	
 *	Copyright (c) 2021 SignalCore Inc.
 *	
 *	Rev 1.0.0
*/

#ifndef SCIULPFUNCTIONS_H__
#define SCIULPFUNCTIONS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** Export Function Prototypes */


/**	Function to find the serial numbers of all SignalCore device with the same product ID
	return:		Status
	input:		interface enum {USB, RS232, PXI}
	output:		serialNumberList 2-D array to pass out the list serial numbers for devices found
				numberDevices the namuber of devices found on that interface
	Example, calling function could declare:
		char **serialNumberList;
		sNList = (char**)malloc(sizeof(char*)*50); // 50 serial numbers
		for (i=0;i<50; i++)
			searchNumberList[i] = (char*)malloc(sizeof(char)*SCI_SN_LENGTH); 
	and pass searchNumberList to the function.
*/

#include "sci_types.h"
#include "nanohb_defs.h"
#include <winnt.h>



SCISTATUS __cdecl nanohb_SearchDevices(uint32_t interface,
		char **serialNumberList, int *numberDevices);

/*	Same as above for LabVIEW calls
*/
SCISTATUS __cdecl nanohb_SearchDevicesLV(uint32_t interface, 
		char *serialNumberList, int *numberDevices);

/*	Function opens the target device.
	return:		pointer to device handle
	input: 		-interface enum {USB, RS232, PXI}
				-devSerialNum is the product serial number. Product number is available on
				the product label.
*/
SCISTATUS __cdecl nanohb_OpenDevice(uint32_t interface, 
		char *devSerialNum, uint8_t baudRateIndex, PHANDLE deviceHandle);

/* Same as above for LabVIEW calls
*/
SCISTATUS __cdecl nanohb_OpenDeviceLV(uint32_t interface, 
		char *devSerialNum, uint8_t baudRateIndex, PHANDLE deviceHandle);

/*	Function  closes the device associated with the handle.
	return:		error code
	input: 		device handle
*/
SCISTATUS __cdecl nanohb_CloseDevice(HANDLE deviceHandle);

/* 	Register level access function prototypes 
	=========================================================================================
*/

/* 	Writing the register with via the USB device handle allocated by OpenDevice
	return: error code
	input: commandByte contains the target register address, eg 0x10 is the frequency register
	input: instructWord contains necessary data for the specified register address
*/
SCISTATUS __cdecl nanohb_RegWrite(HANDLE deviceHandle,
							uint8_t commandByte, 
							uint64_t instructWord);

/* 	Reading the register with via the USB device handle allocated by OpenDevice
	input: commandByte contains the target register address, eg 0x10 is the frequency register
	input: instructWord contains necessary data for the specified register address
	output: receivedWord is the return data request through the commandByte and instructWord
*/							
SCISTATUS __cdecl nanohb_RegRead(HANDLE deviceHandle,
							uint8_t commandByte,
							uint64_t instructWord,
							uint64_t *receivedWord);
							
/* 	Product configuration wrapper function prototypes 
	=========================================================================================
*/
/*	Initializes the device
	return: error code
	input: 		Mode	0: 	The device initializes to the power up state
						1:	The device reprograms all internal components to the current device 
							state
*/							
SCISTATUS __cdecl nanohb_InitDevice(HANDLE deviceHandle);

/*	Sets the device RF frequency
	return: error code
	input:	frequency in Hz
*/
SCISTATUS __cdecl nanohb_SetFrequency(HANDLE deviceHandle, double frequency);

/*	Sets the device RF phase
	return: error code
	input:	phase in degrees 
*/
SCISTATUS __cdecl nanohb_SetPhase(HANDLE deviceHandle, float phase);

/*	Saves the current setup as default, such as frequency
	return:	error code
*/
SCISTATUS __cdecl nanohb_SetAsDefault(HANDLE deviceHandle);

/*	Set the synthesizer to perform a self calibration of the VCO
*	This procedure that 5-7s, during calibration the devices should not
*   not interrupted by communication to the device
	return:	error code
*/
SCISTATUS __cdecl nanohb_SetSynthSelfCal(HANDLE deviceHandle, uint8_t source);

/*	Set the synthesizer mode to determine the tuning behavior of the device
	return:	error code
	input:  SynthMode
*/
SCISTATUS __cdecl nanohb_SetSynthMode(HANDLE deviceHandle, const synthMode_t *synthMode);

/*
	Sets the power-up UART baudrate when physical mode pin is pulled high 
	Index			baudrate
	0				57600
	1				115200
	2				19200
	3				38400
	4				230400
	5				460800
	6				921600
	7				1843200

	Note, when the physical mode pin is low, the rate is always 57600.

	mode -unused set to zero
*/
SCISTATUS __cdecl nanohb_SetSerialConfig(HANDLE deviceHandle, uint8_t mode, uint8_t uartBaudrateIndex);

/*	Configures the list Mode behavior
return: error code
input:	Mode behavior see documentation for the data bit representation
*/
SCISTATUS __cdecl nanohb_SweepConfig(HANDLE deviceHandle, const sweepConfig_t *sweepConfig);

/*	Sets the sweep start frequency
return: error code
input:	frequency in Hz
*/
SCISTATUS __cdecl nanohb_SweepStartFreq(HANDLE deviceHandle, double freq);

/*	Sets the sweep stop frequency
return: error code
input:	frequency in Hz
*/
SCISTATUS __cdecl nanohb_SweepStopFreq(HANDLE deviceHandle, double freq);

/*	Sets the sweep step frequency
return: error code
input:	frequency in HzSC
*/
SCISTATUS __cdecl nanohb_SweepStepFreq(HANDLE deviceHandle, double freq);

/*	Sets the list/sweep dwell time
return: error code
input:	dwellTime in units of 500 us. 1 = 500us, 2 = 1 ms, etc
*/
SCISTATUS __cdecl nanohb_SweepDwellTime(HANDLE deviceHandle, float dwellTime);

/*	Sets the cycle count for list/sweep
return: error code
input:	cycleCount 0 = loop sweep/list forever.
*/
SCISTATUS __cdecl nanohb_SweepCycleCount(HANDLE deviceHandle, uint32_t cycleCount);

/*	Writes the frequency to the buffer list
return: error code
input:	frequency array in Hz.
		dwelltime array in 0.5 ms
		len of array
*/
SCISTATUS __cdecl nanohb_ListBufferWrite(HANDLE deviceHandle, double* frequencies, float* dwellTimes, uint16_t len);

/*	Transfers the list frequencies between RAM and EEPROM
return: error code
input:	transfer_mode = 0 will transfer the list in current RAM into the EEPROM, 1 = transfer from EEPROM to RAM
*/
SCISTATUS __cdecl nanohb_ListBufferTransfer(HANDLE deviceHandle, uint8_t transferMode);

/*	Sends a trigger to start/stop a sweep
	return:	error code
*/
SCISTATUS __cdecl nanohb_ListSoftTrigger(HANDLE deviceHandle);


SCISTATUS __cdecl nanohb_GetDeviceStatus(HANDLE deviceHandle, deviceStatus_t *deviceStatus);

SCISTATUS __cdecl nanohb_GetDeviceInfo(HANDLE deviceHandle, deviceInfo_t *deviceInfo);

SCISTATUS __cdecl nanohb_GetRfParameters(HANDLE deviceHandle, rfParams_t *currentRfParameters);

SCISTATUS __cdecl nanohb_GetTemperature(HANDLE deviceHandle, float *temperature);

SCISTATUS __cdecl nanohb_GetListBuffer(HANDLE deviceHandle, double* frequencies, float* dwellTimes, uint16_t *len);

# 	ifdef __cplusplus
}
#	endif

#	endif  /* __H__ */	