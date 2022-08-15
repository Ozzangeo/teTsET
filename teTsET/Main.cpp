/* 코딩 일지
* 2022-08-11
* 자고 일어났을때  할거
* 움직이는 오브젝트 갱신하기
* 1. char과 bool형으로 이루어진 struct Layer를 만들어서
*    갱신된곳만 true로 바꿔서 갱신하기(?)
*
* 2. 일일히 컴포넌트에서 노가다로 잔상 없애주기
*
* 3. 그냥 다 초기화하깈ㅋㅋㅋㅋㅋㅋㅋ
*
* 4. 고정레이어를 만들고 그 부분을 제외한 그냥 다 초기화하기 ( 채택 )
* 
* 2022-08-12
* 이거 분명히 미래의 나는
* 코드 한달만 안봐도 작동원리 다 까먹는다.
* 과거의 내가 보증하지
* 
* 2022-08-12
* 델타타임 왜 안맞지 ( 2022-08-14 해결함 )
* 
* 2022-08-14
* GetAsyncKeyState가 여러개 있을 때
* 단일 클릭으로는 하나밖에 작동하지 않는다.
* 이거 Key 클래스 따로 하나 만들어야하는 각인가?
* 
* 2022-08-14 PM 7:47
* 자고일어나면 Sprite2D 만들기
*/

// 와새늦

#include "Objects.h"

using namespace std;
using namespace chrono;

using namespace Objects;

int main() {
	SceneManager* manager = &SceneManager::GetInstance();
	Keyboard* keyboard = &Keyboard::GetInstance();
	Graphic* graphic = &Graphic::GetInstance();

#pragma region Scenes
#pragma region Scene1
	Scene NewScene;
	
	for (int i = 0; i < 50; i++) {
		Sprite2DTest* so = NewScene.AddGameObject<Sprite2DTest>("Audio" + to_string(i));
		so->Pos = { (float)(i * 2), (float)i, 0};
	}

	for (int i = 50; i > 0; i--) {
		Sprite2DTest* so = NewScene.AddGameObject<Sprite2DTest>("Audio" + to_string(i + 50));
		so->Pos = { (float)(i * 2), (float)50 - i, 0 };
	}

	manager->AddScene(&NewScene, "NewScene");
#pragma endregion
#pragma endregion

	manager->SetScene("NewScene");

	int FPS = 0;

	float MAX_FPS = 1000.0f / 60;
	float ExecutionTime = 0.0f;

	system_clock::time_point FPS_Start = system_clock::now();
	while (true) {
		system_clock::time_point start = system_clock::now();

		// 프레임 측정
		if (duration<float>(start - FPS_Start).count() >= 1.0f) {
			graphic->Text("[ FPS : " + to_string(FPS) + " ] ", {1, 1, 1}, true);

			FPS_Start = start;
			FPS = 0;
		}
		
		// 키보드 입력 받기
		keyboard->Update();

		// 오브젝트 업데이트
		manager->Update();

		// 그래픽 업데이트
		graphic->Draw();
		FPS++;

		graphic->Text("[ DeltaTime : " + to_string(graphic->deltatime) + " ]    ", { 1, 3, 1 }, true);
		graphic->Text("[ ExecutionTime : " + to_string(ExecutionTime) + " ]    ", { 1, 5, 1 }, true);
		graphic->Text("[ SleepTIme : " + to_string(MAX_FPS - ExecutionTime) + " ]    ", { 1, 7, 1 }, true);

		ExecutionTime = duration<float>(system_clock::now() - start).count() * 1000;
		if (MAX_FPS > ExecutionTime) {
			Stop((MAX_FPS - ExecutionTime));
		}

		// deltatime 측정
		graphic->deltatime = duration<float>(system_clock::now() - start).count();
	}

	// 씬 정리
	manager->Clear();

	// 메모리 할당 해제
	delete manager;
	delete graphic;

	return 0;
}