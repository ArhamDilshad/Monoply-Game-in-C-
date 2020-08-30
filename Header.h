#pragma once
#include <windows.h>
#define _WIN32_WINNT 0x0500 

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <cwchar>



void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void myLine(int x1, int y1, int x2, int y2, int R, int G, int B) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);

}

void myTriangle(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);

	int mid = (x1 + x2) / 2;
	MoveToEx(device_context, mid, y1, NULL);
	LineTo(device_context, x2, y2);
	LineTo(device_context, x1, y2);
	LineTo(device_context, mid + 1, y1);

	HBRUSH brush = ::CreateSolidBrush(RGB(FR, FG, FB));  //Fill color is black
	SelectObject(device_context, brush);

	FloodFill(device_context, mid, (y1 + y2) / 2, RGB(R, G, B));

	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);




}

// This function checks if any of the 4 cursor keys are pressed. 
// If any cursor key is pressed, then the function returns true, and whichKey identifies which of the 4 cursor keys is pressed.
// whichkey is assigned following values if any cursor key is pressed. 1 for left, 2 for up, 3 for right and 4 for left.
bool isCursorKeyPressed(int& whickKey)   //whichKey passed as reference.... 
{
	char key;
	key = GetAsyncKeyState(37);
	if (key == 1)
	{
		whickKey = 1;		// 1 if left key is pressed 
		return true;
	}
	key = GetAsyncKeyState(38);
	if (key == 1)
	{

		whickKey = 2;		// 2 if up key is pressed
		return true;
	}

	key = GetAsyncKeyState(39);
	if (key == 1)
	{

		whickKey = 3; // 3 if right key is pressed
		return true;
	}
	key = GetAsyncKeyState(40);
	if (key == 1)
	{

		whickKey = 4;   // 4 if down key is pressed
		return true;
	}
	key = GetAsyncKeyState(13);
	if (key == 1)
	{

		whickKey = 5;   // 4 if down key is pressed
		return true;
	}
	return false;
}

void myRect(int x1, int y1, int x2, int y2, int R, int G, int B, int BR, int BG, int BB)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(BR, BG, BB)); //Fill color is passed as parameter to the function!!!

	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myEllipse(int x1, int y1, int x2, int y2, int R, int G, int B,int RR,int GG ,int BB)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(RR, GG, BB));  //Fill color is black
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);


}


void myDrawText(int x, int y, int ht, char str[], COLORREF lineColor, COLORREF fillColor)
{
	char wstr[20] = {};
	for (int i = 0; i < 20 && str[i]; ++i)
		wstr[i] = str[i];

	RECT rects;
	rects.left = x;
	rects.top = y;
	rects.right = x + ht;
	rects.bottom = y + ht;//(x,y,x+ht,y+ht);

	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	SetTextColor(device_context, lineColor);
	SetBkColor(device_context, fillColor);
	DrawText(device_context, wstr, -1, &rects, DT_TOP | DT_NOCLIP);


	ReleaseDC(console_handle, device_context);

}

void myDrawTextWithFont(int x, int y, int ht, char  str[], COLORREF lineColor, COLORREF fillColor)
{
	char wstr[20] = {};
	for (int i = 0; i < 20 && str[i]; ++i)
		wstr[i] = str[i];

	RECT rects;
	HFONT hFont;
	rects.left = x;
	rects.top = y;
	rects.right = x + ht;
	rects.bottom = y + ht;//(x,y,x+ht,y+ht);

	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);
	hFont = CreateFont(ht, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, 1, VARIABLE_PITCH, TEXT("Impact"));
	SelectObject(device_context, hFont);

	SetTextColor(device_context, lineColor);
	SetBkColor(device_context, fillColor);
	DrawText(device_context, wstr, -1, &rects, DT_TOP | DT_NOCLIP);
	DeleteObject(hFont);
	ReleaseDC(console_handle, device_context);

}
