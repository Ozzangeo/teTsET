#pragma once

// Objects.h

#include "GameObject.h"

using namespace GS;
using namespace DCs;

// Custom Components
namespace CCs {
	class CrossTestComp : public Component {
	public:
		float speed = 50.0f;

		void Update();
	};
	class AudioTestComp : public Component {
	private:
		Audio* audio;

	public:
		void Awake();
		void Update();
	};
	class PlayerComp : public Component {
	private:
		Collider* Col;
		float PlayerSpeed = 20.0f;
		bool isCollision;

	public:
		void Awake();
		void Update();
	};
}
