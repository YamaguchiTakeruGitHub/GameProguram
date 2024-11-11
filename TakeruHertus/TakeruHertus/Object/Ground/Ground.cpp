#include "Ground.h"

// ƒ‰ƒCƒ“‚ğ•`‚­”ÍˆÍ
#define LINE_AREA_SIZE				10000.0f

// ƒ‰ƒCƒ“‚Ì”
#define LINE_NUM					50

Ground::Ground()
{
}

Ground::~Ground()
{
}

void Ground::Init()
{
}

void Ground::Update()
{
}

void Ground::Draw()
{
    DebugDraw();
}

void Ground::Final()
{
}

void Ground::DebugDraw()
{
  

    SetUseZBufferFlag(TRUE);

    Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
    Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
    for (i = 0; i <= LINE_NUM; i++)
    {
        DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
        Pos1.x += LINE_AREA_SIZE / LINE_NUM;
        Pos2.x += LINE_AREA_SIZE / LINE_NUM;
    }

    Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
    Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
    for (i = 0; i < LINE_NUM; i++)
    {
        DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
        Pos1.z += LINE_AREA_SIZE / LINE_NUM;
        Pos2.z += LINE_AREA_SIZE / LINE_NUM;
    }

    SetUseZBufferFlag(FALSE);
}
