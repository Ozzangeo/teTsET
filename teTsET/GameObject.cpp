#include "GameObject.h"

using namespace std;
using namespace GS;
using namespace DCs;

// Component
Component::Component() {
	this->isActivate = true;
	this->graphic = &Graphic::GetInstance();
	this->keyboard = &Keyboard::GetInstance();
	this->object = nullptr;
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

// Scene
void Scene::Update() {
	for (GameObject* Temp : Objects) {
		Temp->Update();
	}
}
void Scene::Clear() {
	for (GameObject* Temp : Objects) {
		Temp->Remove();
		delete Temp;
	}
	Objects.clear();
}
GameObject* Scene::GetGameObject(string name) {
	for (GameObject* Item : Objects) {
		if (Item->name == name) return Item;
	}
	return nullptr;
}
list<GameObject*> Scene::GetGameObjectList(string tag) {
	list<GameObject*> Temp;

	for (GameObject* Item : Objects) {
		if (Item->tag == tag) Temp.push_back(Item);
	}

	return Temp;
}

// SceneManager
SceneManager& SceneManager::GetInstance() {
	static SceneManager m_SceneManager;
	return m_SceneManager;
}
void SceneManager::AddScene(Scene* Scene_, string Tag) {
	for (auto& Item : Scenes) {
if (Item.Tag == Tag) {
	Item.Scene_ = Scene_;
	return;
}
	}
	Scenes.push_back({ Scene_, Tag });
}
void SceneManager::SetScene(string Tag) {
	for (auto& Item : Scenes) {
		if (Item.Tag == Tag) UpdateScene = Item.Scene_;
	}
}
void SceneManager::Update() {
	UpdateScene->Update();
}
void SceneManager::Clear() {
	for (auto& Item : Scenes) {
		Item.Scene_->Clear();
		delete Item.Scene_;
	}
	Scenes.clear();
}

// Sprite
void Sprite::Update() {
	if (object->isVisible) {
		graphic->Fill(sprite, {
		(int)(object->Pos.x - (object->Size.x * 0.5f)),
		(int)(object->Pos.y - (object->Size.y * 0.5f)),
		(int)object->Pos.z },
			{ (int)object->Size.x, (int)object->Size.y });
	}
}

// Sprite2D
void Sprite2D::Update() {
	if (object->isVisible) {
		graphic->TextBox(sprite.c_str(), {
		(int)(object->Pos.x - (object->Size.x * 0.5f)),
		(int)(object->Pos.y - (object->Size.y * 0.5f)),
		(int)object->Pos.z },
			{ (int)object->Size.x, (int)object->Size.y });
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

// Collider
void Collider::Awake()
{
	SceneManager_ = &SceneManager::GetInstance();
}
bool Collider::isCollision(string tag)
{
	{
		list<GameObject*> objects = SceneManager_->UpdateScene->GetGameObjectList(tag);

		if (object == nullptr) return false;

		// Pos < Pos + Size
		for (GameObject* Item : objects) {
			if (object->Pos.x + (object->Size.x * 0.5) >= Item->Pos.x - (Item->Size.x * 0.5) &&
				object->Pos.x - (object->Size.x * 0.5) <= Item->Pos.x + (Item->Size.x * 0.5)) {
				if (object->Pos.y + (object->Size.y * 0.5) >= Item->Pos.y - (Item->Size.y * 0.5) &&
				    object->Pos.y - (object->Size.y * 0.5) <= Item->Pos.y + (Item->Size.y * 0.5)) {
					return true;
				}
			}
		}

		return false;
	}
}
