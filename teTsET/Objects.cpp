#include "Objects.h"

using namespace Objects;

using namespace DCs;
using namespace CCs;

// CrossTest
void CrossTest::Awake() {
	CompHolder.RequireComponent<Sprite>()->Object = this;
	CompHolder.RequireComponent<CrossTestComp>()->Object = this;

	CompHolder.Awake();
}

// AudioTest
void AudioTest::Awake() {
	CompHolder.RequireComponent<Sprite>()->Object = this;
	CompHolder.RequireComponent<CrossTestComp>()->Object = this;
	CompHolder.RequireComponent<AudioTestComp>()->Object = this;

	CompHolder.Awake();
}

// Sprite2DTest
void Sprite2DTest::Awake() {
	CompHolder.RequireComponent<Sprite2D>()->Object = this;
	CompHolder.RequireComponent<CrossTestComp>()->Object = this;
	CompHolder.RequireComponent<AudioTestComp>()->Object = this;

	CompHolder.Awake();

	#pragma region Sprite2D
	Sprite2D* sprite = CompHolder.GetComponent<Sprite2D>();
	sprite->sprite = "\
@@@@ @@@@\
@@@@ @@@@\
    @    \
@@@@ @@@@\
@@@@ @@@@";
	sprite->Object->Size = { 9, 5 };
	#pragma endregion
}