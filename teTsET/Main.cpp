/* �ڵ� ����
* 2022-08-11
* �ڰ� �Ͼ����  �Ұ�
* �����̴� ������Ʈ �����ϱ�
* 1. char�� bool������ �̷���� struct Layer�� ����
*    ���ŵȰ��� true�� �ٲ㼭 �����ϱ�(?)
*
* 2. ������ ������Ʈ���� �밡�ٷ� �ܻ� �����ֱ�
*
* 3. �׳� �� �ʱ�ȭ�σ���������������
*
* 4. �������̾ ����� �� �κ��� ������ �׳� �� �ʱ�ȭ�ϱ� ( ä�� )
* 
* 2022-08-12
* �̰� �и��� �̷��� ����
* �ڵ� �Ѵ޸� �Ⱥ��� �۵����� �� ��Դ´�.
* ������ ���� ��������
* 
* 2022-08-12
* ��ŸŸ�� �� �ȸ��� ( 2022-08-14 �ذ��� )
* 
* 2022-08-14
* GetAsyncKeyState�� ������ ���� ��
* ���� Ŭ�����δ� �ϳ��ۿ� �۵����� �ʴ´�.
* �̰� Key Ŭ���� ���� �ϳ� �������ϴ� ���ΰ�?
* 
* 2022-08-14 PM 7:47
* �ڰ��Ͼ�� Sprite2D �����
*/

// �ͻ���

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

		// ������ ����
		if (duration<float>(start - FPS_Start).count() >= 1.0f) {
			graphic->Text("[ FPS : " + to_string(FPS) + " ] ", {1, 1, 1}, true);

			FPS_Start = start;
			FPS = 0;
		}
		
		// Ű���� �Է� �ޱ�
		keyboard->Update();

		// ������Ʈ ������Ʈ
		manager->Update();

		// �׷��� ������Ʈ
		graphic->Draw();
		FPS++;

		graphic->Text("[ DeltaTime : " + to_string(graphic->deltatime) + " ]    ", { 1, 3, 1 }, true);
		graphic->Text("[ ExecutionTime : " + to_string(ExecutionTime) + " ]    ", { 1, 5, 1 }, true);
		graphic->Text("[ SleepTIme : " + to_string(MAX_FPS - ExecutionTime) + " ]    ", { 1, 7, 1 }, true);

		ExecutionTime = duration<float>(system_clock::now() - start).count() * 1000;
		if (MAX_FPS > ExecutionTime) {
			Stop((MAX_FPS - ExecutionTime));
		}

		// deltatime ����
		graphic->deltatime = duration<float>(system_clock::now() - start).count();
	}

	// �� ����
	manager->Clear();

	// �޸� �Ҵ� ����
	delete manager;
	delete graphic;

	return 0;
}