#include "Player.h"

Player::Player()
	: m_position	(VGet(0.0f, 0.0f, 0.0f))
	, m_modelHandle (MV1LoadModel(""))
	, m_radius		(5.0f)
	, m_start		(VAdd(m_position, VGet(0.0f, 10.0f, 0.0f)))
	, m_end			(VSub(m_position, VGet(0.0f, 10.0f, 0.0f)))
{
}

Player::~Player()
{
	MV1DeleteModel(m_modelHandle);
}

void Player::Init()
{
	m_position = VGet(0.0f, 0.0f, 0.0f);
	m_modelHandle = MV1LoadModel("");
	m_radius = 5.0f;
	m_start = VAdd(m_position, VGet(0.0f, 13.0f, 0.0f));
	m_end = VSub(m_position, VGet(0.0f, 13.0f, 0.0f));
}

void Player::Update()
{
	MV1SetPosition(m_modelHandle, m_position);
}

void Player::Draw()
{
	DrawCapsule3D(m_start, m_end, m_radius, 5, 0xffffff, 0xffffff, false);
}

void Player::Final()
{
	MV1DeleteModel(m_modelHandle);
}
