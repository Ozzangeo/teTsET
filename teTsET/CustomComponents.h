#pragma once

// Objects.h

#include "GameObject.h"

using namespace GS;
using namespace DCs;

class Scene {
private:
	list<GameObject*> Objects;

public:
	template<typename T> T* AddGameObject(string name) {
		// 만약 이미 같은 이름과 타입의 오브젝트가 있다면
		if (GetGameObject<T>(name) != nullptr) return nullptr;
		
		GameObject* Temp = new T();
		Temp->name = name;
		Temp->Awake();

		Objects.push_back(Temp);
		return dynamic_cast<T*>(Temp);
	}
	template<typename T> T* GetGameObject(string name) {
		for (GameObject* Temp : Objects) {
			if (Temp->name == name && typeid(*Temp) == typeid(T)) return dynamic_cast<T*>(Temp);
		}
		return nullptr;
	}
	template<typename T> void RemoveGameObject(string name) {
		GameObject* obj = GetGameObject<T>(name);
		if (obj == nullptr) return;

		obj->Remove();
		Objects.remove(obj);

		delete obj;
	}
	void Clear();

	void Update();
};
class SceneManager {
#pragma region Singleton
private:
	SceneManager() {};
	SceneManager(const SceneManager& ref) {
		Scenes;
	}
	SceneManager& operator=(const SceneManager& ref) {}

public:
	static SceneManager& GetInstance();

#pragma endregion
private:
	struct TagScene {
		string Tag;
		Scene* Scene_;

		TagScene(Scene* _Scene, string Tag) {
			this->Tag = Tag;
			this->Scene_ = _Scene;
		}
	};

public:
	list<TagScene> Scenes;
	Scene* UpdateScene;

	void AddScene(Scene* Scene_, string Tag);
	void SetScene(string Tag);

	void Update();
	void Clear();
};

// Custom Components
namespace CCs {
	class CrossTestComp : public Component {
	public:
		float speed = 10.0f;

		void Awake() {};
		void Update();
	};
	class AudioTestComp : public Component {
	private:
		Audio* audio;

	public:
		void Awake();
		void Update();
	};
}
