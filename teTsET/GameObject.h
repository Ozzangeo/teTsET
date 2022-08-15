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
	GameObject* Object;

	Component();

	virtual void Awake() = 0;
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
	bool isVisible = true;

	ComponentHolder CompHolder;
	Vector3<float> Pos;
	Vector2<int> Size;

	// Awake : Insert Component List
	virtual void Awake() = 0;
	virtual void Update();
	virtual void Remove();
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
}
