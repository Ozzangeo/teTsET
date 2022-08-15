#pragma once
#pragma comment (lib, "winmm.lib")

// System.h

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <typeinfo>
#include <Windows.h>
#include <chrono>
#include <cmath>
#include <thread>
#include <mmsystem.h>
#include <Digitalv.h>
#include <atlstr.h>
#include <atlconv.h>
#include <vector>
#include <map>

#endif // !Util_H

using namespace std;
using namespace chrono;

enum KeyCode {
	KC_SPACE = 32,

	KC_0 = 48,
	KC_1 = 49,
	KC_2 = 50,
	KC_3 = 51,
	KC_4 = 52,
	KC_5 = 53,
	KC_6 = 54,
	KC_7 = 55,
	KC_8 = 56,
	KC_9 = 57,

	KC_A = 65,
	KC_B = 66,
	KC_C = 67,
	KC_D = 68,
	KC_E = 69,
	KC_F = 70,
	KC_G = 71,
	KC_H = 72,
	KC_I = 73,
	KC_J = 74,
	KC_K = 75,
	KC_L = 76,
	KC_M = 77,
	KC_N = 78,
	KC_O = 79,
	KC_P = 80,
	KC_Q = 81,
	KC_R = 82,
	KC_S = 83,
	KC_T = 84,
	KC_U = 85,
	KC_V = 86,
	KC_W = 87,
	KC_X = 88,
	KC_Y = 89,
	KC_Z = 90,

	KC_LSHIFT = 160,
	KC_RSHIFT = 161,
	KC_LCTRL = 162,
	KC_RCTRL = 163,
	KC_LALT = 164,
	KC_RALT = 165,
};

template<typename T> struct Vector2 {
	T x;
	T y;

	Vector2(T x = 0, T y = 0) {
		this->x = x;
		this->y = y;
	}
};
template<typename T> struct Vector3 {
	T x;
	T y;
	T z;

	Vector3(T x = 0, T y = 0, T z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

void Stop(float millisecond);
void Cursor(SHORT x = 0, SHORT y = 0);
void Cursor(Vector2<SHORT> Pos);
