#pragma once
#include <DxLib.h>
#include <memory>
#include <string>
//#include "../../LibCom/CSVLib/CSVLib.h"


/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	~Player();

	//void loadData(const std::string& _filename);


	void Init();
	void Update();
	void Draw();
	void Final();

	void SetPosition(const VECTOR& _position) { this->m_position = _position; }
	VECTOR GetPosition() const { return  this->m_position; }

	

private:

	//モデルのハンドルを格納
	int m_modelHandle;

	//モデルのポジションを格納
	VECTOR m_position;
	
	//半径
	float m_radius;
	
	//カプセルの一番上
	VECTOR m_start;

	//カプセルの一番下
	VECTOR m_end;

	//std::shared_ptr<CSVLib> m_csvLib;

};

