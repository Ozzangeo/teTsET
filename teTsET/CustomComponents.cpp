#include "CustomComponents.h"

using namespace GS;
using namespace DCs;
using namespace CCs;

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

// CrossTestComp
void CrossTestComp::Update() {
	static bool isVis = true;

	if (Object->Pos.y + (Object->Size.y * 0.5f) >= HEIGHT) {
		Object->Pos.y -= HEIGHT;
	}

	static bool isPlaySound = false;
	if (keyboard->GetKey(KC_SPACE)) {
		if (!isPlaySound) {
			isVis = !isVis;
			isPlaySound = true;
		}
	}
	else isPlaySound = false;

	if (isVis) Object->isVisible = true;
	else Object->isVisible = false;

	Object->Pos.y += graphic->deltatime * speed;
}

// AudioTestComp
void AudioTestComp::Awake() {
	audio = Object->CompHolder.RequireComponent<Audio>();

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

