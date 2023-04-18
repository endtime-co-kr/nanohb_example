#pragma once

#ifndef _SCIDEVICE_H_
#define _SCIDEVICE_H_

#ifndef MAXDEVICES
#define MAXDEVICES 128
#endif // !MAXDEVICES


typedef	struct _SCIDEVICE
{
	HANDLE handle;
	uint32_t device_type;
} SCIDEVICE, *PSCIDEVICE;  //

#endif 