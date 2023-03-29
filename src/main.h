#ifndef _MAIN_H_
#define _MAIN_H_

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#define _USE_MATH_DEFINES

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "entity.h"
#include "car.h"
#include "mesh.h"

#define STYLE WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void InitGraphics();
void Redraw();
void DrawCar(HDC dc, PVECTOR2 mesh);
void DrawTree(HDC dc, PVECTOR2 mesh);
void DrawDirtRoad(HDC dc, PVECTOR2 ribbon, int fragments, float width);
void InitTrees();
void InitCar();
void DrawTrees();
void DrawUI();
void DetectCollisions();
void ReadKeys(char key, BOOL state);

#endif