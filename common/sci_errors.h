/* 
	Error definitions for Signalcore Products
*/

#pragma once

#ifndef _SCI_ERRORS_H
#define	_SCI_ERRORS_H

//
// define the error codes
//
#define SCI_SUCCESS										0
#define SCI_ERROR_NONE									0
#define SCI_ERROR_INVALID_DEVICE_HANDLE					-1
#define SCI_ERROR_NO_DEVICE								-2
#define SCI_ERROR_INVALID_DEVICE						-3
#define SCI_ERROR_MEM_UNALLOCATE						-4
#define SCI_ERROR_MEM_EXCEEDED							-5
#define SCI_ERROR_INVALID_REG							-6
#define SCI_ERROR_INVALID_ARGUMENT						-7
#define SCI_ERROR_COMM_FAIL								-8
#define SCI_ERROR_OUT_OF_RANGE							-9
#define SCI_ERROR_PLL_LOCK								-10
#define	SCI_ERROR_TIMED_OUT								-11
#define SCI_ERROR_COMM_INIT								-12
#define	SCI_ERROR_TIMED_OUT_READ						-13
#define SCI_ERROR_INVALID_INTERFACE						-14

#endif 