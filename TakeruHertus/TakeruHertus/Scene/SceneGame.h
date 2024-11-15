#pragma once
#include "SceneBase.h"
#include "SceneGameCommon.h"
#include "../Object/Ground/Ground.h"
#include <memory>
#include "../DebugWindow/DebugWindow.h"

class SceneGame : public SceneBase
{
public:
	SceneGame();
	~SceneGame();

	void Init();
	void Update();
	void Draw();
	void Final();
	void DebugDraw();

private:
	DebugWindow debugWindow;

	std::shared_ptr<Player> m_player;
	std::shared_ptr<EnemySmallFish> m_enemy1;
	std::shared_ptr<EnemyMidle> m_enemy2;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Ground> m_ground;
	std::shared_ptr<Physics> m_physics;
	std::shared_ptr<SkyDome> m_skyDome;
	std::shared_ptr<LightManager> m_light;
	//std::shared_ptr<Command> m_command;
};

