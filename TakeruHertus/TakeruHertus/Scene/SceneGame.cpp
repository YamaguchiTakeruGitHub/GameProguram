#include "SceneGame.h"
#include "SceneManager.h"

SceneGame::SceneGame()
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_Idm.get()->Init();
}

void SceneGame::Update()
{
	m_Idm.get()->Update();


	if (CheckHitKey(KEY_INPUT_G))
	{
		SceneManager::GetInstance().ChangeScene(SceneType::Result);
	}
}

void SceneGame::Draw()
{
	DebugDraw();
}

void SceneGame::Final()
{
}

void SceneGame::DebugDraw()
{
#ifdef _DEBUG
	DrawString(0, 20, "GameScene", 0xffffff, 16);

#endif // _DEBUG
}
