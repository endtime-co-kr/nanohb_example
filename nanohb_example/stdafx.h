// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h"


#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#endif

// Windows Header Files:
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>

// SCI Error definitions

#include "../common/sci_types.h"
#include "../common/sci_device.h"
#include "../common/sci_errors.h"
#include "../common/nanohb_defs.h"
#include "../common/nanohb_regs.h"
#include "../common/nanohb_functions.h"