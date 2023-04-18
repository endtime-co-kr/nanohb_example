// nanohb_example.c : This file contains the 'main' function. Program execution begins and ends there.
//

//using precompiled headers

#include "stdafx.h"
#include "../common/nanohb_defs.h"

#ifdef WIN32
#pragma warning(disable : 4996)
#endif

void display_device_status(deviceStatus_t* deviceStatus)
{
	printf("\n\n*********DEVICE STATUS READ FROM DEVICE***************\n");
	printf(" Sum PLL lock:				%d \n", deviceStatus->pllStatus.sumPllLD);
	printf(" Coarse PLL lock:			%d \n", deviceStatus->pllStatus.crsPllLD);
	printf(" Fine PLL lock:				%d \n", deviceStatus->pllStatus.finePllLD);
	printf(" Coarse PLL lock:			%d \n", deviceStatus->pllStatus.crsIntNPllLD);
	printf(" Coarse Reference PLL lock:	%d \n", deviceStatus->pllStatus.crsRefPllLD);
	printf(" System Clock PLL lock:		%d \n\n", deviceStatus->pllStatus.sysPllLD);

	printf("RF Mode:					%d \n", deviceStatus->operateStatus.synthMode.rfMode);
	printf("Loop Gain:					%d \n", deviceStatus->operateStatus.synthMode.loopGain);
	printf("Lock Mode:					%d \n", deviceStatus->operateStatus.synthMode.lockMode);
	printf("Resolution:					%d \n", deviceStatus->operateStatus.synthMode.freqResln);
	printf("Spur Suppression:			%d \n", deviceStatus->operateStatus.synthMode.autoSpurSuppress);
	printf("Over Temperature:			%d \n", deviceStatus->operateStatus.overTemp);
	printf("List Mode Running:			%d \n", deviceStatus->operateStatus.listModeRunning);
	printf("UART Pin Set:				%d \n", deviceStatus->operateStatus.uartPinSet);
	printf("UART Baudrate:				%d \n", deviceStatus->operateStatus.selectedBaud);
}

void display_device_info(deviceInfo_t* devInfo)
{
	printf("\n\n**********DEVICE ATTRIBUTES************* \n");
	if (devInfo->model.modelNumber > 0)
		printf(" The device is a SC802A \n");
	else
		printf(" The device is a SC801A \n");
	printf(" The product serial number: 0x%08X \n", devInfo->productSerialNumber);
	printf(" The product firmware version:  %d.%d.%d\n", devInfo->firmwareVersion.major, devInfo->firmwareVersion.minor, devInfo->firmwareVersion.fix);
	printf(" The product hardware version:  %d.%d.%d\n", devInfo->hardwareVersion.major, devInfo->hardwareVersion.minor, devInfo->hardwareVersion.fix);
	printf(" The product manufacture date is: %d-%d-%d\n\n",
		devInfo->manDate.year, devInfo->manDate.month,
		devInfo->manDate.day);
}

void display_rf_parameters(rfParams_t* rfParams)
{
	printf("\n**********RF PARAMETERS************* \n");
	printf(" The current rf frequency is %f Hz\n", (double)rfParams->frequency);
	printf(" The sweep start frequency is %f Hz\n", (double)rfParams->sweepStartFreq);
	printf(" The sweep stop frequency is %f Hz\n", (double)rfParams->sweetStopFreq);
	printf(" The sweep step frequency is %f Hz\n", (double)rfParams->sweetStepFreq);
	printf(" The sweep dwell time is %f ms\n", rfParams->sweepDwellTime);
}


int main()
{
#ifdef MAXDEVICES
#undef MAXDEVICES
#define MAXDEVICES 50	// redefine MAXDEVICES to 50
#endif
#define MAXDEVICES 50

	int status;
	deviceStatus_t deviceStatus;
	deviceInfo_t deviceInfo;
	rfParams_t rfParams;
	synthMode_t synthMode;
	float temperature;

	uint32_t interface = 0; //0 for usb, 1 for RS232
	HANDLE devHandle = NULL;
	char** deviceList; /// 2D to hold serial numbers or RS232 port names of the devices found
	int devices, selectDevice; /// holds the number of devices found.
	int i;
	char doSweep;

	/* Uncomment to Run Sweep */
	double freqList[5] = { 12.01E9, 12.02e9, 12.03e9, 12.04e9, 12.05e9 };
	float listDwellTime[5] = { 200.0, 500.0, 100.0, 200.0, 400.0 };
	uint16_t listPoints = 5;
	sweepConfig_t sweepConfig;

	deviceList = (char**)malloc(sizeof(char*) * MAXDEVICES); /// 16 serial numbers to search
	if (deviceList)
	{
		for (i = 0; i < MAXDEVICES; i++)
			deviceList[i] = (char*)malloc(sizeof(char) * SCI_SN_LENGTH); /// SCI SN 8 bytes + termination


		status = nanohb_SearchDevices(interface, deviceList, &devices);

		// if(status != SCI_SUCCESS){ /* handle status error */}
		if (devices < 1)
		{
			printf("No SC801A or SC802A devices found on USB ports\n");
			for (i = 0; i < MAXDEVICES; i++) free(deviceList[i]);
			free(deviceList);
			printf("\n\n Press ENTER to exit\n");
			getchar();
			return 1;
		}


		i = 0;
		while (i < devices)
		{
			printf("	Device %d has Serial Number: %s \n", i + 1, deviceList[i]);
			i++;
		}
		/* 	*/
		printf("\n Enter the number of the device you wish to select : ");

		scanf(" %d", &selectDevice);
		getchar();
		if ((selectDevice < 1) || (selectDevice > devices))
		{
			printf(" No such device !!! exiting... \n");
			return 1;
		}

		/*	Open the selected device through the use of its serial number
		*   baudrate has not effect on USB and PXI devices
		*/
		printf("\n Open the device ..........\n");
		status = nanohb_OpenDevice(interface, deviceList[selectDevice - 1], 0, &devHandle);
		if (devHandle == NULL)
		{
			printf("Device with serial number: %s cannot be opened.\n", deviceList[interface - 1]);
			printf("Please ensure your device is powered on and connected\n");
			for (i = 0; i < MAXDEVICES; i++) free(deviceList[i]);
			free(deviceList);
			free(devHandle); //dev_handle is allocated memory on OpenDevice(); 
			printf("\n\n Press ENTER to exit\n");
			getchar();
			return 1;
		}
		for (i = 0; i < MAXDEVICES; i++) free(deviceList[i]);
		free(deviceList); // Done with the deviceList
		printf("\n DEVICE OPENED!!..........\n");
	}
	else
	{
		printf("Could not locate memory for device");
		return 1;
	}

	/*	Begin communication to the device
	*/

	printf("\n Reading the device temperature..........\n");
	status = nanohb_GetTemperature(devHandle, &temperature); // Set to single tone mode, not sweep/list
	if (status != EXIT_SUCCESS) return status;
	printf("\n The device temperature is %f\n", temperature);

	printf("\n Getting the device status..........\n");
	status = nanohb_GetDeviceStatus(devHandle, &deviceStatus); // Obtain the current status of the device
	if (status != EXIT_SUCCESS) return status;
	display_device_status(&deviceStatus); // display the device status 
	synthMode = deviceStatus.operateStatus.synthMode; //Obtain the current synth mode parameter

	printf("\nGetting device Info ..........\n");
	status = nanohb_GetDeviceInfo(devHandle, &deviceInfo);  // obtain calData
	if (status != EXIT_SUCCESS) return status;
	display_device_info(&deviceInfo);

	printf("\nGetting RF parameters ..........\n");
	status = nanohb_GetRfParameters(devHandle, &rfParams);  // obtain calData
	if (status != EXIT_SUCCESS) return status;
	display_rf_parameters(&rfParams);

	printf("\nChange the RF frequency to 13.5 GHz");
	status = nanohb_SetFrequency(devHandle, 2.0e9); // set the device frequency to 13.5 GHz

	/// <summary>
	/// This following commented section loads a list of 5 frequency points with correspondering dwell times.
	/// Then it configures to start and stop the sweep using this list with a software trigger from any
	/// key. The sweep cycle is set to 3, but it can be stopped by pressing any key to soft trigger \
	/// again. 
	/// </summary>
	/// <returns></returns>
	///

	printf("\n DO you want to perform a software trigger to start and stop a list sweep ? (Y/N)");
	scanf("%c", &doSweep);
	getchar();

	if ((doSweep == 'Y') || (doSweep == 'y'))
	{

		printf("\n Setting up to software trigger to sweep a list of frequencies \n");
		printf("  1) Write List frequencies and dwell times \n");
		printf("	Frequencies				Dwell Time \n");
		printf("	12.01 GHz				200 ms \n");
		printf("	12.02 GHz				500 ms \n");
		printf("	12.03 GHz				100 ms \n");
		printf("	12.04 GHz				400 ms \n");
		printf("	12.05 GHz				200 ms \n");

		status = nanohb_ListBufferWrite(devHandle, freqList, listDwellTime, listPoints); // load the lists
		if (status != EXIT_SUCCESS) return status;

		// Setup the sweep configuration
		sweepConfig.useBufferList = 1; //use the list instead of the start/step/stop freq points
		sweepConfig.sweepDirection = 0; // Go from first to last point
		sweepConfig.sweepPattern = 1; // sawtooth sweep
		sweepConfig.returnToStart = 1; // return to the first point after the cycles are completed
		sweepConfig.hwTrig = 0; //use software to trigger. Choose 1 if using the tigger pin to trigger
		sweepConfig.trigMode = 0; //first trigger to start, next trigger to stop
		sweepConfig.TrigOutEnable = 0; // The trigger output pin will not pulse on every frequency

		printf("\n 2) Setup the sweepConfig parameters to use the list\n");
		status = nanohb_SweepConfig(devHandle, &sweepConfig); //load in the configuration
		if (status != EXIT_SUCCESS) return status;

		printf("\n 3) Set the synthMode parameter rfMode to 1 \n");
		// Get the current synth parameter RF mode to sweep/list
		synthMode.rfMode = 1; // 0 = fixed, 1 = sweep/list
		status = nanohb_SetSynthMode(devHandle, &synthMode); //The put the device ready to receive triggering
		if (status != EXIT_SUCCESS) return status;

		printf("\n Waiting for a KEY to be press to send a software trigger to start");
		getchar();
		status = nanohb_ListSoftTrigger(devHandle);
		printf("\n Sweep of the list has started, Press another key to stop the sweep");
		getchar();
		status = nanohb_ListSoftTrigger(devHandle);
		printf("\n Sweep should have stopped, and synthesizer is now set back to fixed frequency mode");
		synthMode.rfMode = 0; // 0 = fixed, 1 = sweep/list
		status = nanohb_SetSynthMode(devHandle, &synthMode); //The put the device ready to receive triggering
		if (status != EXIT_SUCCESS) return status;
	}

	printf("\nClose Device ..........\n");
	nanohb_CloseDevice(devHandle); //function closes the device and frees the device Handle

	printf("\n\n********** EXAMPLE DONE **********\n");

	printf("\n\n Press ENTER to exit\n");
	getchar();
	return EXIT_SUCCESS;
}
