#include "SceneGame.h"
#include "SceneManager.h"

SceneGame::SceneGame()
{
	m_player = std::make_shared<Player>();
	m_camera = std::make_shared<Camera>();
	m_ground = std::make_shared<Ground>();
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_Idm.get()->Init();

	m_player.get()->Init();
	m_camera.get()->Init();
	m_ground.get()->Init();
}

void SceneGame::Update()
{
	m_Idm.get()->Update();
	m_player.get()->Update(m_camera.get()->GetHAngle(), m_camera.get()->GetVAngle(), m_camera.get()->GetSinParam(), m_camera.get()->GetCosParam());
	m_camera.get()->Update(m_player.get()->GetPosition());
	m_ground.get()->Update();


	if (CheckHitKey(KEY_INPUT_G))
	{
		SceneManager::GetInstance().ChangeScene(SceneType::Result);
	}
}

void SceneGame::Draw()
{
	DebugDraw();
	m_player.get()->Draw();
	m_ground.get()->Draw();
}

void SceneGame::Final()
{
	m_player.get()->Final();
	m_ground.get()->Final();
}

void SceneGame::DebugDraw()
{
#ifdef _DEBUG
	DrawString(0, 20, "GameScene", 0xffffff, 16);
	debugWindow.UpdateDebugInfo(5, "gameScene");
#endif // _DEBUG
}
