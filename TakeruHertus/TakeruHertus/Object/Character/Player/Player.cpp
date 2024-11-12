#include "Player.h"


Player::Player()
	: m_position	(VGet(0.0f, 100.0f, 0.0f))
	, m_direction	(VGet(0.0f, 0.0f, 0.0f))
	, m_velocity	(VGet(0.0f, 0.0f, 0.0f))
	, m_frame		()
	, m_modelHandle (MV1LoadModel("../Asset/3D/Character/Player/Player.mv1"))
	, m_scale		(VGet(0.1f, 0.1f, 0.1f))
	, m_radius		(5.0f)
	, m_start		(VAdd(m_position, VGet(0.0f, 10.0f, 0.0f)))
	, m_end			(VSub(m_position, VGet(0.0f, 10.0f, 0.0f)))
	, isMove		(false)
	, speed			(2.0f)
	, m_angle		(0.0f)
	, tempMoveVector(VGet(0.0f, 0.0f, 0.0f))
	, targetRotationY(0.0f)
	, targetDirection(VGet(0,0,0))
	, targetPos(VGet(0,0,0))
	, rotationY(0.0f)
	
{
	//m_csvLib = std::make_shared<CSVLib>();
	m_Idm = std::make_shared<InputDeviceManager>();
	m_camera = std::make_shared<Camera>();
	
	m_frame.leftHand	 = VGet(0.0f, 0.0f, 0.0f);	//左手
	m_frame.rightHand	 = VGet(0.0f, 0.0f, 0.0f);	//右手
	m_frame.head		 = VGet(0.0f, 0.0f, 0.0f);		//頭
	m_frame.rightfeet	 = VGet(0.0f, 0.0f, 0.0f);	//右足
	m_frame.leftfeet	 = VGet(0.0f, 0.0f, 0.0f);	//左足
	m_frame.crotch		 = VGet(0.0f, 0.0f, 0.0f);		//股

	m_frame.rightElbow = MV1GetFramePosition(m_modelHandle, 54);	//右肘
	m_frame.rightShoulder = MV1GetFramePosition(m_modelHandle, 52);//右肩
	m_frame.leftElbow = MV1GetFramePosition(m_modelHandle, 20);	//左肘
	m_frame.leftShoulder = MV1GetFramePosition(m_modelHandle, 18);//左肩
	m_frame.rightKnees = MV1GetFramePosition(m_modelHandle, 94);	//右膝
	m_frame.leftKnees = MV1GetFramePosition(m_modelHandle, 87);	//左膝
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
	m_Idm.get()->Init();

	isMove = false;
	speed = 2.0f;
	m_angle = 0.0f;
	tempMoveVector = VGet(0.0f, 0.0f, 0.0f);

	m_position = VGet(0.0f, 100.0f, 0.0f);
	m_direction = VGet(0.0f, 0.0f, 0.0f);
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	m_modelHandle = MV1LoadModel("../Asset/3D/Character/Player/Player.mv1");
	m_scale = VGet(0.1f, 0.1f, 0.1f);
	m_radius = 5.0f;
	m_start = VAdd(m_position, VGet(0.0f, 13.0f, 0.0f));
	m_end = VSub(m_position, VGet(0.0f, 13.0f, 0.0f));

	m_frame.leftHand	 = MV1GetFramePosition(m_modelHandle, 55);	//左手
	m_frame.rightHand	 = MV1GetFramePosition(m_modelHandle, 21);	//右手
	m_frame.head		 = MV1GetFramePosition(m_modelHandle, 9);	//頭
	m_frame.rightfeet	 = MV1GetFramePosition(m_modelHandle, 95);	//右足
	m_frame.leftfeet	 = MV1GetFramePosition(m_modelHandle, 88);	//左足
	m_frame.crotch		 = MV1GetFramePosition(m_modelHandle, 3);	//股

	m_frame.rightElbow = MV1GetFramePosition(m_modelHandle, 54);	//右肘
	m_frame.rightShoulder = MV1GetFramePosition(m_modelHandle, 52);//右肩
	m_frame.leftElbow = MV1GetFramePosition(m_modelHandle, 20);	//左肘
	m_frame.leftShoulder = MV1GetFramePosition(m_modelHandle, 18);//左肩
	m_frame.rightKnees = MV1GetFramePosition(m_modelHandle, 94);	//右膝
	m_frame.leftKnees = MV1GetFramePosition(m_modelHandle, 87);	//左膝

	targetRotationY = 0.0f;
	targetDirection = VGet(0, 0, 0);
	targetPos = VGet(0, 0, 0);
	rotationY = 0.0f;

	//loadData("../GameData/PlayerData.csv");
}

void Player::Update(float _cHAngle, float  _cVAngle, float _SinParam, float _CosParam)
{
	m_Idm.get()->Update();

	m_direction = VGet(0.0f, 0.0f, 0.0f);
	m_velocity = VGet(0.0f, 0.0f, 0.0f);
	isMove = false;


	//左スティックの召喚
	float leftStickX = m_Idm.get()->joyPad->GetLeftStickX();
	float leftStickY = m_Idm.get()->joyPad->GetLeftStickY();

	bool Left = leftStickX != 0 && leftStickX >= -0.030519f && leftStickX <= 0.0f;
	bool Right = leftStickX != 0 && leftStickX <= 0.030519f && leftStickX >= 0.0f;
	bool Up = leftStickY != 0 && leftStickY <= 0.030519f && leftStickY >= 0.0f;
	bool Down = leftStickY != 0 && leftStickY >= -0.030519 && leftStickY <= 0.0f;

	if (Left)
	{
		m_angle = 90.0f - _cHAngle;
		m_direction.x = 1.0f;
		isMove = true;
	}
	if (Right)
	{
		m_angle = -90.0f - _cHAngle;
		m_direction.x = -1.0f;
		isMove = true;
	}
	if (Up)
	{
		m_angle = 0.0f - _cHAngle;
		m_direction.z = 1.0f;
		isMove = true;
	}
	if (Down)
	{
		m_angle = 180.0f - _cHAngle;
		m_direction.z = -1.0f;
		isMove = true;
	}

	if (m_position.y <= 20.0f)
	{
		m_position.y = 20.0f;
	}
	else
	{
		m_position.y--;
	}

	


	//targetDirection.x = sin(m_angle);
	//targetDirection.z = cos(m_angle);

	//targetPos = VAdd(m_position, VScale(targetDirection, 20.0f));

	//


	if (m_direction.x > 0.0f ||
		m_direction.z > 0.0f ||
		m_direction.x < 0.0f ||
		m_direction.z < 0.0f)
	{
		m_direction = VNorm(m_direction);
	}


	if (isMove == true)
	{
		m_velocity = VGet(m_direction.x * speed, 0.0f, m_direction.z * speed);

		_SinParam = sin(_cHAngle / 180.0f * DX_PI_F);
		_CosParam = cos(_cHAngle / 180.0f * DX_PI_F);
		tempMoveVector.x = m_velocity.x * _CosParam - m_velocity.z * _SinParam;
		tempMoveVector.y = 0.0f;
		tempMoveVector.z = m_velocity.x * _SinParam + m_velocity.z * _CosParam;

		m_position = VAdd(m_position, tempMoveVector);


		//m_position = VAdd(m_velocity, m_position);
	}



	SetFrame();
	MV1SetPosition(m_modelHandle, m_position);
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, /*NormalizeAngle(m_angle)*/m_angle / 180.0f * DX_PI_F, 0.0f));
	MV1SetScale(m_modelHandle, m_scale);
}

void Player::Draw()
{
	MV1DrawModel(m_modelHandle);
	DebugDraw();
}

void Player::Final()
{
	MV1DeleteModel(m_modelHandle);
}

void Player::SetFrame()
{
	m_frame.head = MV1GetFramePosition(m_modelHandle, 9);	//頭
	m_frame.leftHand = MV1GetFramePosition(m_modelHandle, 55);	//左手
	m_frame.rightHand = MV1GetFramePosition(m_modelHandle, 21);	//右手
	m_frame.rightElbow = MV1GetFramePosition(m_modelHandle, 54);	//右肘
	m_frame.rightShoulder = MV1GetFramePosition(m_modelHandle, 52);//右肩
	m_frame.leftElbow = MV1GetFramePosition(m_modelHandle, 20);	//左肘
	m_frame.leftShoulder = MV1GetFramePosition(m_modelHandle, 18);//左肩
	m_frame.rightKnees = MV1GetFramePosition(m_modelHandle, 94);	//右膝
	m_frame.leftKnees = MV1GetFramePosition(m_modelHandle, 87);	//左膝
	m_frame.rightfeet = MV1GetFramePosition(m_modelHandle, 95);	//右足
	m_frame.leftfeet = MV1GetFramePosition(m_modelHandle, 88);	//左足
	m_frame.crotch = MV1GetFramePosition(m_modelHandle, 3);	//股
}

float Player::NormalizeAngle(float _angle)
{
	while (_angle > DX_PI_F) _angle -= DX_PI_F * 2;
	while (_angle < -DX_PI_F) _angle += DX_PI_F * 2;
	
	return _angle;
}


void Player::DebugDraw()
{
#ifdef _DEBUG
	DrawLine3D(targetPos, m_position, 0x00ff00);

	DrawCapsule3D(m_start, m_end, m_radius, 5, 0xffffff, 0xffffff, false);

	DrawSphere3D(m_frame.leftfeet, 4, 5, 0xffffff, 0xffffff, false);
	DrawSphere3D(m_frame.rightfeet, 4, 5, 0xffffff, 0xffffff, false);
	DrawSphere3D(m_frame.leftHand, 4, 5, 0xffffff, 0xffffff, false);
	DrawSphere3D(m_frame.rightHand, 4, 5, 0xffffff, 0xffffff, false);
	DrawSphere3D(m_frame.crotch, 4, 5, 0xffffff, 0xffffff, false);
	DrawSphere3D(m_frame.leftShoulder, 4, 5, 0xffffff, 0xffffff, false);
	DrawSphere3D(m_frame.rightShoulder, 4, 5, 0xffffff, 0xffffff, false);
	DrawSphere3D(m_frame.leftElbow, 4, 5, 0xffffff, 0xffffff, false);
	DrawSphere3D(m_frame.rightElbow, 4, 5, 0xffffff, 0xffffff, false);
	DrawSphere3D(m_frame.leftKnees, 4, 5, 0xffffff, 0xffffff, false);
	DrawSphere3D(m_frame.rightKnees, 4, 5, 0xffffff, 0xffffff, false);


#endif // _DEBUG

}
