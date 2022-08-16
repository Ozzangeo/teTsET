#include "Objects.h"

using namespace Objects;

using namespace DCs;
using namespace CCs;

// CrossTest
void CrossTest::Awake() {
	CompHolder.RequireComponent<Sprite>()->object = this;
	CompHolder.RequireComponent<CrossTestComp>()->object = this;

	CompHolder.Awake();
}

// AudioTest
void AudioTest::Awake() {
	CompHolder.RequireComponent<Sprite>()->object = this;
	CompHolder.RequireComponent<CrossTestComp>()->object = this;
	CompHolder.RequireComponent<AudioTestComp>()->object = this;

	CompHolder.Awake();
}

// Sprite2DTest
void Sprite2DTest::Awake() {
	CompHolder.RequireComponent<Sprite2D>()->object = this;
	CompHolder.RequireComponent<CrossTestComp>()->object = this;
	CompHolder.RequireComponent<AudioTestComp>()->object = this;

	CompHolder.Awake();

	#pragma region Sprite2D
	Sprite2D* sprite = CompHolder.GetComponent<Sprite2D>();
	sprite->sprite = "\
@@@@ @@@@\
@@@@ @@@@\
    @    \
@@@@ @@@@\
@@@@ @@@@";
	sprite->object->Size = { 9, 5 };
	#pragma endregion
}

void Player::Awake()
{
	CompHolder.RequireComponent<Sprite2D>()->object = this;
	CompHolder.RequireComponent<PlayerComp>()->object = this;

#pragma region Sprite2D
	Sprite2D* sprite = CompHolder.GetComponent<Sprite2D>();
	sprite->sprite = "\
@@@@ @@@@\
@@@@ @@@@\
    @    \
@@@@ @@@@\
@@@@ @@@@";
	sprite->object->Size = { 9, 5 };
#pragma endregion
}
