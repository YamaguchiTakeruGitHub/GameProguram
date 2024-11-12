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
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Ground> m_ground;

};

