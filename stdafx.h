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
#include <vector>
#include <time.h>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

// TODO: reference additional headers your program requires here
#include "Params.h"
#include "tools.h"
#include "GA.h"
#include "NeuralNet.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "MineSweeper.h"
#include "Mine.h"