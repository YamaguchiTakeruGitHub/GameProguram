#pragma once
#include "SceneBase.h"
#include "SceneGameCommon.h"
#include "../Object/Ground/Ground.h"
#include <memory>

class SceneGame : public SceneBase
{
public:
	SceneGame();
	~SceneGame();

	void Init();
	void Update();
	void Draw();
	void Final();

private:
	void DebugDraw();

	std::shared_ptr<Player> m_player;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Ground> m_ground;

};

