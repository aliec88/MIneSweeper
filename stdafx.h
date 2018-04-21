// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <fstream>
#include <time.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

// TODO: reference additional headers your program requires here
#include "Params.h"
#include "Timer.h"
#include "Mine.h"
#include "Sweeper.h"
#include "GA.h"
#include "NueralNet.h"
#include "SVector2D.h"
#include "tools.h"
#include "Matrix2D.h"