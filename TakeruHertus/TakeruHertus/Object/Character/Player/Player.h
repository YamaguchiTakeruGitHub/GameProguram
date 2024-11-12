#pragma once
#include <DxLib.h>
#include <memory>
#include <string>
#include "../../../InputDevice/InputDeviceManager.h"
#include "../../Camera/Camera.h"
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
	void Update(float _cHAngle, float  _cVAngle, float _SinParam, float _CosParam);
	void Draw();
	void Final();
	void SetFrame();

	void SetPosition(const VECTOR& _position) { this->m_position = _position; }
	VECTOR GetPosition() const { return  this->m_position; }

private:
	float NormalizeAngle(float _angle);
	float targetRotationY;
	VECTOR targetDirection;
	VECTOR targetPos;
	float rotationY;

	void DebugDraw();

	std::shared_ptr<InputDeviceManager> m_Idm;
	std::shared_ptr<Camera> m_camera;




	bool isMove;
	float speed;
	float m_angle;


	VECTOR tempMoveVector;





	//モデルのハンドルを格納
	int m_modelHandle;

	//モデルのポジションを格納
	VECTOR m_position;
	VECTOR m_velocity;
	VECTOR m_direction;

	/// <summary>
	/// モデルのフレームポジション
	/// </summary>
	struct FramPos
	{
		VECTOR head;		//頭

		VECTOR leftHand;	//左手
		VECTOR rightHand;	//右手

		VECTOR leftElbow;	//左肘
		VECTOR rightElbow;	//右肘

		VECTOR leftShoulder;//左肩
		VECTOR rightShoulder;//右肩

		VECTOR rightfeet;	//右足
		VECTOR leftfeet;	//左足

		VECTOR rightKnees;	//右膝
		VECTOR leftKnees;	//左膝


		VECTOR crotch;		//股



	}m_frame;


	//モデルのスケール
	VECTOR m_scale;

	//半径
	float m_radius;
	
	//カプセルの一番上
	VECTOR m_start;

	//カプセルの一番下
	VECTOR m_end;

	//std::shared_ptr<CSVLib> m_csvLib;

};

