#pragma once
#include <DxLib.h>

class Ground
{
public:
	Ground();
	~Ground();

	void Init();
	void Update();
	void Draw();
	void Final();

private:
	void DebugDraw();

	int i;
	VECTOR Pos1;
	VECTOR Pos2;

};

