#include "Player.h"

Player::Player()
	: m_position	(VGet(0.0f, 0.0f, 0.0f))
	, m_modelHandle (MV1LoadModel(""))
	, m_radius		(5.0f)
	, m_start		(VAdd(m_position, VGet(0.0f, 10.0f, 0.0f)))
	, m_end			(VSub(m_position, VGet(0.0f, 10.0f, 0.0f)))
{
	//m_csvLib = std::make_shared<CSVLib>();
}

Player::~Player()
{
	MV1DeleteModel(m_modelHandle);
}

//void Player::loadData(const std::string& _filename)
//{
//	auto parsePlayerData = [this](const std::vector<std::string>& _tokens)
//	{
//			if (_tokens.size() >= 5)
//			{
//				m_position.x = std::stof(_tokens[2]);
//				m_position.y = std::stof(_tokens[3]);
//				m_position.z = std::stof(_tokens[4]);
//
//			}
//	};
//
//	auto data = m_csvLib->loadCSV<std::vector<std::string>>(_filename, [](const std::vector<std::string>& _tokens) 
//	{
//			return _tokens;
//	});
//
//	if (!data.empty())
//	{
//		parsePlayerData(data[0]);//最初の行を使用してメンバー変数にデータを格納
//	}
//
//}

void Player::Init()
{

	m_position = VGet(0.0f, 0.0f, 0.0f);
	m_modelHandle = MV1LoadModel("");
	m_radius = 5.0f;
	m_start = VAdd(m_position, VGet(0.0f, 13.0f, 0.0f));
	m_end = VSub(m_position, VGet(0.0f, 13.0f, 0.0f));

	//loadData("../GameData/PlayerData.csv");
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
