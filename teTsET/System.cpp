#include "System.h"

using namespace std;
using namespace GS;

// Graphic
Graphic::Graphic() {
	string SYSTEM = "mode con: cols=" + to_string(WIDTH) + " lines=" + to_string(HEIGHT);
	system(SYSTEM.c_str());

	// [ 접근 방식 ]
	// TLayer : x + (y * WIDTH)
	// Layer : x + (y * WIDTH) + (DEPTH * CANVAS)

	// TLayer 초기화
	TLayer = new char[CANVAS + 1];
	TLayer[CANVAS] = '\0';
	Clear();

	// Layer 초기화
	Layer.Screen = new char[CANVAS * DEPTH + 1];
	Layer.isStatic = new bool[CANVAS * DEPTH];
	Layer.Screen[CANVAS * DEPTH] = '\0';
	for (int i = 0, MAX_SIZE = CANVAS * DEPTH; i < MAX_SIZE; i++) {
		Layer.Screen[i] = background;
		Layer.isStatic[i] = false;
	}
}
Graphic& Graphic::GetInstance() {
	static Graphic m_Graphic;
	return m_Graphic;
}
void Graphic::Merge() {
	for (int i = 0; i < DEPTH; i++) {
		for (int j = 0; j < CANVAS; j++) {
			if (Layer.Screen[j + (i * CANVAS)] != background && Layer.Screen[j + (i * CANVAS)] != ' ') {
				TLayer[j] = Layer.Screen[j + (i * CANVAS)];
			}
		}
	}
}
void Graphic::Clear() {
	for (int i = 0; i < CANVAS; i++) {
		TLayer[i] = ' ';
	}
}
void Graphic::ClearAll() {
	for (int i = 0, MAX_SIZE = CANVAS * DEPTH; i < MAX_SIZE; i++) {
		if(!Layer.isStatic[i]) Layer.Screen[i] = background;
	}
}
Graphic::~Graphic() {
	delete[] TLayer;

	delete[] Layer.Screen;
	delete[] Layer.isStatic;
}
void Graphic::Clear(int depth) {
	if (depth >= DEPTH) depth = DEPTH - 1;
	
	depth = depth * CANVAS;
	for (int i = 0; i < CANVAS; i++) {
		Layer.Screen[depth + i] = background;
	}
}
void Graphic::Draw() {
	Cursor();

	Merge();
	ClearAll();

	// [ printf vs cout ]
	// 최대 프레임 : cout(730 fps), printf(680 fps)
	// 최소 프레임 : cout(540 fps), printf(600 fps)
	// 안정성 면에서 printf 사용
	
	printf("%s", TLayer);
	// cout << TLayer;

	Clear();
}
void Graphic::TextBox(char* text, Vector3<int> Pos, Vector2<int> Box) {
	int Temp = Pos.x + (Pos.y * WIDTH);
	int i = 0;

	for (int y = 0; y < Box.y && Pos.y + y < HEIGHT; y++) {
		if (Pos.y + y < 0) continue;
		for (int x = 0; x < Box.x; x++) {
			// 만약 text길이 넘으면 for문 종료
			if (i >= (int)strlen(text)) return;

			// 화면 오른쪽 넘김 방지(?)
			if (Pos.x + x >= WIDTH) {
				i += Box.x - x;
				break;
			}

			// 화면 왼쪽 넘김 방지
			if (Pos.x + x >= 0) Layer.Screen[Temp + x + (y * WIDTH) + (Pos.z * CANVAS)] = text[i];
			i++;
		}
	}
}
void Graphic::TextBox(const char* text, Vector3<int> Pos, Vector2<int> Box) {
	int Temp = Pos.x + (Pos.y * WIDTH);
	int i = 0;

	for (int y = 0; y < Box.y && Pos.y + y < HEIGHT; y++) {
		if (Pos.y + y < 0) {
			i += Box.x;
			continue;
		}
		for (int x = 0; x < Box.x; x++) {
			// 만약 text길이 넘으면 for문 종료
			if (i >= (int)strlen(text)) return;

			// 화면 오른쪽 넘김 방지(?)
			if (Pos.x + x >= WIDTH) {
				i += Box.x - x;
				break;
			}

			// 화면 왼쪽 넘김 방지
			if (Pos.x + x >= 0) Layer.Screen[Temp + x + (y * WIDTH) + (Pos.z * CANVAS)] = text[i];
			i++;
		}
	}
}
void Graphic::Text(char* text, Vector3<int> Pos, bool isStatic) {
	int Temp = Pos.x + (Pos.y * WIDTH);

	for (int i = 0, MAX_SIZE = (int)strlen(text); i < MAX_SIZE && Temp + i < CANVAS; i++) {
		Layer.Screen[Temp + (Pos.z * CANVAS) + i] = text[i];
		Layer.isStatic[Temp + (Pos.z * CANVAS) + i] = isStatic;
	}
}
void Graphic::Text(const char* text, Vector3<int> Pos, bool isStatic) {
	int Temp = Pos.x + (Pos.y * WIDTH);

	for (int i = 0, MAX_SIZE = (int)strlen(text); i < MAX_SIZE && Temp + i < CANVAS; i++) {
		Layer.Screen[Temp + (Pos.z * CANVAS) + i] = text[i];
		Layer.isStatic[Temp + (Pos.z * CANVAS) + i] = isStatic;
	}
}
void Graphic::Text(string text, Vector3<int> Pos, bool isStatic) {
	int Temp = Pos.x + (Pos.y * WIDTH);

	for (int i = 0, MAX_SIZE = (int)text.length(); i < MAX_SIZE && Temp + i < CANVAS; i++) {
		Layer.Screen[Temp + (Pos.z * CANVAS) + i] = text[i];
		Layer.isStatic[Temp + (Pos.z * CANVAS) + i] = isStatic;
	}
}
void Graphic::Fill(char pixel, Vector3<int> Pos, Vector2<int> Size, bool isStatic) {
	int Temp = Pos.x + (Pos.y * WIDTH);

	// [ 접근 방식 ]
	// TLayer : x + (y * WIDTH)
	// Layer : x + (y * WIDTH) + (DEPTH * CANVAS)

	for (int y = 0; y < Size.y && Pos.y + y < HEIGHT; y++) {
		if (Pos.y + y < 0) continue;
		for (int x = 0; x < Size.x && Pos.x + x < WIDTH; x++) {
			if (Pos.x + x < 0) continue;
			Layer.Screen[Temp + (Pos.z * CANVAS) + x + (y * WIDTH)] = pixel;
			Layer.isStatic[Temp + (Pos.z * CANVAS) + x + (y * WIDTH)] = isStatic;
		}
	}
}

// Keyboard
Keyboard::Keyboard() {
#pragma region KeyInsert
	Keys.insert({ KC_SPACE, false });

	Keys.insert({ KC_0, false });
	Keys.insert({ KC_1, false });
	Keys.insert({ KC_2, false });
	Keys.insert({ KC_3, false });
	Keys.insert({ KC_4, false });
	Keys.insert({ KC_5, false });
	Keys.insert({ KC_6, false });
	Keys.insert({ KC_7, false });
	Keys.insert({ KC_8, false });
	Keys.insert({ KC_9, false });
	Keys.insert({ KC_A, false });
	Keys.insert({ KC_B, false });
	Keys.insert({ KC_C, false });
	Keys.insert({ KC_D, false });
	Keys.insert({ KC_E, false });
	Keys.insert({ KC_F, false });
	Keys.insert({ KC_G, false });
	Keys.insert({ KC_H, false });
	Keys.insert({ KC_I, false });
	Keys.insert({ KC_J, false });
	Keys.insert({ KC_K, false });
	Keys.insert({ KC_L, false });
	Keys.insert({ KC_M, false });
	Keys.insert({ KC_N, false });
	Keys.insert({ KC_O, false });
	Keys.insert({ KC_P, false });
	Keys.insert({ KC_Q, false });
	Keys.insert({ KC_R, false });
	Keys.insert({ KC_S, false });
	Keys.insert({ KC_T, false });
	Keys.insert({ KC_U, false });
	Keys.insert({ KC_V, false });
	Keys.insert({ KC_W, false });
	Keys.insert({ KC_X, false });
	Keys.insert({ KC_Y, false });
	Keys.insert({ KC_Z, false });

	Keys.insert({ KC_LSHIFT, false });
	Keys.insert({ KC_RSHIFT, false });
	Keys.insert({ KC_LCTRL, false });
	Keys.insert({ KC_RCTRL, false });
	Keys.insert({ KC_LALT, false });
	Keys.insert({ KC_RALT, false });
#pragma endregion
}
Keyboard::~Keyboard() {
	Keys.clear();
}
void Keyboard::Reset() {
	for (auto& Item : Keys) {
		Item.second = false;
	}
}
void Keyboard::Update() {
	Reset();

	for (auto& Item : Keys) {
		if (GetAsyncKeyState(Item.first)) Item.second = true;
	}
}
bool Keyboard::GetKey(KeyCode key) {
	for (auto& Item : Keys) {
		if (Item.first == key) return Item.second;
	}
	return false;
}
Keyboard& Keyboard::GetInstance() {
	static Keyboard m_Keyboard;
	return m_Keyboard;
}