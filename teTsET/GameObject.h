#pragma once

// CustomComponents.h

#include "System.h"

using namespace std;

class GameObject;

class Component {
protected:
	Graphic* graphic;
	Keyboard* keyboard;

public:
	bool isActivate;
	GameObject* object;

	Component();

	virtual void Awake() {};
	virtual void Update() = 0;
	virtual void Remove() {};
};
class ComponentHolder {
private:
	list<Component*> Components;

public:
	void Awake();
	void Update();

	template<typename T> T* AddComponent() {
		Component* Comp = new T;
		Components.push_back(Comp);

		return dynamic_cast<T*>(Comp);
	}
	template<typename T> T* GetComponent() {
		for (Component* Temp : Components) {
			if (typeid(*Temp) == typeid(T)) return dynamic_cast<T*>(Temp);
		}
		return nullptr;
	}
	template<typename T> void RemoveComponent() {
		T* Comp = GetComponent<T>();

		if (Comp == nullptr) return;

		Comp->Remove();
		Components.remove(Comp);

		delete Comp;
	}
	template<typename T> T* RequireComponent() {
		for (Component* Temp : Components) {
			if (typeid(*Temp) == typeid(T)) return dynamic_cast<T*>(Temp);
		}
		return AddComponent<T>();
	}

	void Clear();
};
class GameObject
{
public:
	string name;
	string tag;
	bool isVisible = true;

	ComponentHolder CompHolder;
	Vector3<float> Pos;
	Vector2<float> Size;

	// Awake : Insert Component List
	virtual void Awake() = 0;
	virtual void Update();
	virtual void Remove();
};
class Scene {
public:
	list<GameObject*> Objects;

	template<typename T> T* AddGameObject(string name = "", string tag = "") {
		// 만약 이미 같은 이름과 타입의 오브젝트가 있다면
		if (GetGameObject<T>(name) != nullptr) return nullptr;

		GameObject* Temp = new T();
		if(name != "") Temp->name = name;
		if (tag != "") Temp->tag = tag;
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
	GameObject* GetGameObject(string name);
	list<GameObject*> GetGameObjectList(string tag);
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

// Default Components
namespace DCs {
	class Sprite : public Component {
	public:
		char sprite = '@';

		void Awake() {};
		void Update();
	};
	class Sprite2D : public Component {
	public:
		string sprite;

		void Awake() {};
		void Update();
	};
	class Audio : public Component {
	private:
		struct SoundInfo {
			DWORD Sound;
			UINT ID;
			SoundInfo(DWORD Sound = NULL, UINT ID = 0) {
				this->Sound = Sound;
				this->ID = ID;
			}
		};

		MCI_OPEN_PARMS mciOpen;
		MCI_PLAY_PARMS mciPlay;

		// mpegvideo : .mp3
		// waveaudio : .wav
		// avivideo  : .avi
		CString AudioType = "mpegvideo";
		list<SoundInfo> SoundList;

	public:
		void Awake() {};
		void Update() {};
		void Remove();

		void SetAudioType(string Type);

		void LoadAudio(CString path);
		void PlayAudio(UINT ID, bool isLoop = false);
		void RePlayAudio(UINT ID);
		void PauseAudio(UINT ID);
	};
	class Collider : public Component {
	private:
		SceneManager* SceneManager_;

	public:
		void Awake();
		void Update() {};

		bool isCollision(string tag) {
			list<GameObject*> objects = SceneManager_->UpdateScene->GetGameObjectList(tag);

			if (object == nullptr) return false;

			// Pos < Pos + Size
			// <= : 널널한 판정
			// < : 빡센 판정
			for (auto Item : objects) {
				for (int x = (int)object->Pos.x, X = (int)(object->Pos.x + object->Size.x); x < X; x++) {
				for (int y = (int)object->Pos.y, Y = (int)(object->Pos.y + object->Size.y); y < Y; y++) {
					for (int x_ = (int)Item->Pos.x, X_ = (int)(Item->Pos.x + Item->Size.x); x_ < X_; x_++) {
					for (int y_ = (int)Item->Pos.y, Y_ = (int)(Item->Pos.y + Item->Size.y); y_ < Y_; y_++) {
						if (x == x_ && y == y_) return true;
					}}
				}}
			}

			return false;
		}
	};
}
