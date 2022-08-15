#pragma once

// GameObject.h
#include "Util.h"

// Graphic Size
namespace GS {
	const static int WIDTH = 100;
	const static int HEIGHT = 50;
	const static int DEPTH = 5;

	const static int CANVAS = WIDTH * HEIGHT;
}

class Graphic
{
#pragma region Singleton
private:
	Graphic();
	Graphic(const Graphic& ref) {
		TLayer = nullptr;
		Layer;
	}
	Graphic& operator=(const Graphic& ref) {}

public:
	static Graphic& GetInstance();

#pragma endregion
private:
	struct Pixel {
		char* Screen;
		bool* isStatic;
	};

	// [ 출력 레이어 ]
	char* TLayer;

	char background = '\a';

	void Merge();
	void Clear();
	
public:
	void ClearAll();
	float deltatime = 0.0f;

	Pixel Layer;

	~Graphic();

	void Clear(int depth);
	void Draw();

	void TextBox(char* text, Vector3<int> Pos, Vector2<int> Box);
	void TextBox(const char* text, Vector3<int> Pos, Vector2<int> Box);

	void Text(char* text, Vector3<int> Pos, bool isStatic = false);
	void Text(const char* text, Vector3<int> Pos, bool isStatic = false);
	void Text(string text, Vector3<int> Pos, bool isStatic = false);

	void Fill(char pixel, Vector3<int> Pos, Vector2<int> Size, bool isStatic = false);
};
class Keyboard {
#pragma region Singleton
private:
	Keyboard();
	Keyboard(const Keyboard& ref);
	Keyboard& operator=(const Keyboard& ref) {}

public:
	static Keyboard& GetInstance();

#pragma endregion
private:
	map<KeyCode, bool> Keys;

	void Reset();
public:
	~Keyboard();

	void Update();

	bool GetKey(KeyCode key);
};
