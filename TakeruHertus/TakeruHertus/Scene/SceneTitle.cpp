#include "SceneTitle.h"
#include "SceneManager.h"

SceneTitle::SceneTitle()
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_Idm.get()->Init();
}

void SceneTitle::Update()
{
	m_Idm.get()->Update();

	if (CheckHitKey(KEY_INPUT_T))
	{
		SceneManager::GetInstance().ChangeScene(SceneType::Game);
	}
	
}

void SceneTitle::Draw()
{
	DebugDraw();
}

void SceneTitle::Final()
{
}

void SceneTitle::DebugDraw()
{
#ifdef _DEBUG
	DrawString(0, 20, "TitleScene", 0xffffff, 16);
#endif // _DEBUG

}
