#pragma once

// Main.cpp

#include "CustomComponents.h"

namespace Objects {
	class CrossTest : public GameObject {
	private:
	public:
		void Awake();
	};
	class AudioTest : public GameObject {
	public:
		void Awake();
	};
	class Sprite2DTest : public GameObject {
	private:
	public:
		void Awake();
	};
	class Player : public GameObject {
	private:
	public:
		void Awake();
	};
}