#include "SceneGame.h"
#include "SceneManager.h"

SceneGame::SceneGame()
{
	m_physics = std::make_shared<Physics>();
	m_player = std::make_shared<Player>();
	m_enemy1 = std::make_shared<EnemySmallFish>();
	m_enemy2 = std::make_shared<EnemyMidle>();
	m_camera = std::make_shared<Camera>();
	m_ground = std::make_shared<Ground>();
	m_skyDome = std::make_shared<SkyDome>();
	m_light = std::make_shared<LightManager>();
//	m_command = std::make_shared<Command>();
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_Idm.get()->Init();

	m_skyDome.get()->Init();
	m_player.get()->Init(m_physics);
	m_enemy1.get()->Init(m_physics);
	m_enemy2.get()->Init(m_physics);
	m_camera.get()->Init();
	m_ground.get()->Init();
	m_light.get()->Init();
	//m_command.get()->Init();

}

void SceneGame::Update()
{
	m_Idm.get()->Update();

#ifdef _DEBUG
	DebugDraw3D::Clear();
#endif // _DEBUG
	m_physics.get()->Update();

	m_skyDome.get()->Update();
	m_enemy1.get()->Update(m_physics);
	m_enemy2.get()->Update(m_physics);
	m_player.get()->Update(m_physics, m_camera.get()->GetHAngle(), m_camera.get()->GetVAngle(), m_camera.get()->GetSinParam(), m_camera.get()->GetCosParam());
	m_camera.get()->Update(m_player.get()->GetPosition());
	m_ground.get()->Update();
	m_light.get()->Update();

	//m_command.get()->Update();


	if (CheckHitKey(KEY_INPUT_G))
	{
		SceneManager::GetInstance().ChangeScene(SceneType::Result);
	}
}

void SceneGame::Draw()
{
	DebugDraw();
	m_skyDome.get()->Draw();

#ifdef _DEBUG
	DebugDraw3D::Draw3D();
#endif // _DEBUG
	m_enemy1.get()->Draw(m_physics);
	m_enemy2.get()->Draw(m_physics);
	m_player.get()->Draw();
	m_ground.get()->Draw();
	m_light.get()->Draw();

	//m_command.get()->Draw();
}

void SceneGame::Final()
{
	m_skyDome.get()->Final();
	m_player.get()->Final(m_physics);
	m_enemy1.get()->Final(m_physics);
	m_enemy2.get()->Final(m_physics);
	//m_command.get()->Final();

	m_ground.get()->Final();

	m_light.get()->Final();
}

void SceneGame::DebugDraw()
{
#ifdef _DEBUG
	DrawString(0, 20, "GameScene", 0xffffff, 16);
	
	debugWindow.UpdateDebugInfo(5, "gameScene");
#endif // _DEBUG
}
