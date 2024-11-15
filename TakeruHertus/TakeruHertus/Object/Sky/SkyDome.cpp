#include "SkyDome.h"

SkyDome::SkyDome()
	: modelHandle(-1)
	, position(VGet(0,0,0))
{
}

SkyDome::~SkyDome()
{
	MV1DeleteModel(modelHandle);
}

void SkyDome::Init()
{
	modelHandle = MV1LoadModel("../Asset/3D/SkyDome/Skydome.mv1");
	position = VGet(0, 0, 0);
}

void SkyDome::Update()
{
	MV1SetPosition(modelHandle, position);
}

void SkyDome::Draw()
{
	MV1DrawModel(modelHandle);
}

void SkyDome::Final()
{
	MV1DeleteModel(modelHandle);
}
