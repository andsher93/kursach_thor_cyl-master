#pragma once
#ifndef WINDOWSPROJECT5_H
#define WINDOWSPROJECT5_H



#define STRICT

#include "struct.h"
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>

#include <stdio.h>
#include <cmath>
#include <assert.h>

#include <gl\\gl.h>
#include <gl\\glu.h>



#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")



#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define CYLINDER 1
#define SPIRAL   2
#define POINT    3
#define AXIS     0


#define PI360 6.2831853
#define PI    3.14159265


#define ALL_PT  10   //  число узлов на половине линии пересечения
#define DFI  (2.0*PI)/10.0
#define N_delta 30

//#include "draw_figure.h"
#include "inters.h"
#include "draw_figure.h"
#include "Cylindr.h"

#endif // !WINDOWSPROJECT5_H