#include "CustomComponents.h"

using namespace GS;
using namespace DCs;
using namespace CCs;

// CrossTestComp
void CrossTestComp::Update() {
	static bool isVis = true;

	if (object->Pos.y + (object->Size.y * 0.5f) >= HEIGHT) {
		object->Pos.y -= HEIGHT;
	}

	static bool isPlaySound = false;
	if (keyboard->GetKey(KC_SPACE)) {
		if (!isPlaySound) {
			isVis = !isVis;
			isPlaySound = true;
		}
	}
	else isPlaySound = false;

	if (isVis) object->isVisible = true;
	else object->isVisible = false;

	object->Pos.y += graphic->deltatime * speed;
}

// AudioTestComp
void AudioTestComp::Awake() {
	audio = object->CompHolder.RequireComponent<Audio>();

	audio->LoadAudio("Music\\BGM.mp3");
	audio->LoadAudio("SoundEffect\\BBong.mp3");

	audio->PlayAudio(1, true);
}
void AudioTestComp::Update() {
	static bool isPlaySound = false;
	if (keyboard->GetKey(KC_SPACE)) {
		if (!isPlaySound) {
			audio->PlayAudio(2);
			isPlaySound = true;
		}
	}
	else isPlaySound = false;
}

// PlayerComp
void PlayerComp::Awake() {
	Col = object->CompHolder.RequireComponent<Collider>();
}
void PlayerComp::Update()
{
	if (keyboard->GetKey(KC_W)) {
		object->Pos.y -= PlayerSpeed * graphic->deltatime;
		if (Col->isCollision("Wall")) object->Pos.y += PlayerSpeed * graphic->deltatime;
	}
	if (keyboard->GetKey(KC_A)) {
		object->Pos.x -= PlayerSpeed * graphic->deltatime * 2;
		if (Col->isCollision("Wall")) object->Pos.x += PlayerSpeed * graphic->deltatime * 2;
	}
	if (keyboard->GetKey(KC_S)) {
		object->Pos.y += PlayerSpeed * graphic->deltatime;
		if (Col->isCollision("Wall")) object->Pos.y -= PlayerSpeed * graphic->deltatime;
	}
	if (keyboard->GetKey(KC_D)) {
		object->Pos.x += PlayerSpeed * graphic->deltatime * 2;
		if (Col->isCollision("Wall")) object->Pos.x -= PlayerSpeed * graphic->deltatime * 2;
	}

	graphic->Text("[ isCollision : " + to_string(isCollision) + " ] ", {1, 9}, true);
}
