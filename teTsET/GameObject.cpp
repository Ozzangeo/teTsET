#include "GameObject.h"

using namespace std;
using namespace GS;
using namespace DCs;

// Component
Component::Component() {
	this->isActivate = true;
	this->graphic = &Graphic::GetInstance();
	this->keyboard = &Keyboard::GetInstance();
	this->Object = nullptr;
}

// ComponentHolder
void ComponentHolder::Awake() {
	for (Component* Comp : Components) {
		if (Comp->isActivate) Comp->Awake();
	}
}
void ComponentHolder::Update() {
	for (Component* Comp : Components) {
		if (Comp->isActivate) Comp->Update();
	}
}
void ComponentHolder::Clear() {
	for (Component* Comp : Components) {
		Comp->Remove();
		delete Comp;
	}
	Components.clear();
}

// GameObject
void GameObject::Update() {
	CompHolder.Update();
}
void GameObject::Remove() {
	CompHolder.Clear();
}

// Sprite
void Sprite::Update() {
	if (Object->isVisible) {
		graphic->Fill(sprite, {
		(int)(Object->Pos.x - (Object->Size.x * 0.5f)),
		(int)(Object->Pos.y - (Object->Size.y * 0.5f)),
		(int)Object->Pos.z },
		Object->Size);
	}
}

// Sprite2D
void Sprite2D::Update() {
	if (Object->isVisible) {
		graphic->TextBox(sprite.c_str(), {
		(int)(Object->Pos.x - (Object->Size.x * 0.5f)),
		(int)(Object->Pos.y - (Object->Size.y * 0.5f)),
		(int) Object->Pos.z},
		Object->Size);
	}
}

// Audio
void Audio::Remove() {
	for (const SoundInfo Item : SoundList) {
		mciSendCommand(Item.ID, MCI_CLOSE, 0, NULL);
	}
	SoundList.clear();
}
void Audio::SetAudioType(string Type) {
	if (Type == ".mp3") AudioType = "mpegvideo";
	else if (Type == ".wav") AudioType = "waveaudio";
	else if (Type == ".avi") AudioType = "avivideo";
	else return;
}
void Audio::LoadAudio(CString path) {
	mciOpen.lpstrDeviceType = AudioType;
	mciOpen.lpstrElementName = path;
	SoundInfo si;
	si.Sound = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);
	si.ID = mciOpen.wDeviceID;

	SoundList.push_back(si);
}
void Audio::PlayAudio(UINT ID, bool isLoop) {
	for (SoundInfo Item : SoundList) {
		if (ID == Item.ID) {
			mciSendCommand(ID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
			if (isLoop) Item.Sound = mciSendCommand(ID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
			else Item.Sound = mciSendCommand(ID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
		}
	}
}
void Audio::RePlayAudio(UINT ID) {
	mciSendCommand(ID, MCI_RESUME, 0, NULL);
}
void Audio::PauseAudio(UINT ID) {
	mciSendCommand(ID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
}
