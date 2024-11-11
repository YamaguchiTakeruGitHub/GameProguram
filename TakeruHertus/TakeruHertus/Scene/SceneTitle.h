#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	~SceneTitle();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

private:
	void DebugDraw();




};

