#include "Util.h"

using namespace std;

void Stop(float millisecond) {
	system_clock::time_point Start = system_clock::now();
	millisecond *= 0.001f;

	while (duration<float>(system_clock::now() - Start).count() < millisecond);
}
void Cursor(SHORT x, SHORT y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
}
void Cursor(Vector2<SHORT> Pos) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { Pos.x, Pos.y });
}
