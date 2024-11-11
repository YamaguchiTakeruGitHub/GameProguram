#pragma once
#include "SceneBase.h"

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


};

