#include "Player.h"
#include <string>

Player::Player()
	: Collidable(Collidable::Priority::Static, GameObjectTag::Player, ColliderData::Kind::Sphere)
	, m_position(m_righdbody.GetPosition())
	, m_direction(m_righdbody.GetDireciton())
	, m_velocity(m_righdbody.GetVelocity())
	, m_radius(5.0f)

	
	//, m_position	(VGet(0.0f, 20.0f, 0.0f))
	//, m_direction	(VGet(0.0f, 0.0f, 0.0f))
	//, m_velocity	(VGet(0.0f, 0.0f, 0.0f))
	//, m_radius		(5.0f)
	, m_frame		()
	, m_modelHandle (MV1LoadModel("../Asset/3D/Character/Player/Player.mv1"))
	, m_scale		(VGet(0.1f, 0.1f, 0.1f))
	, m_start		(VAdd(m_position, VGet(0.0f, 10.0f, 0.0f)))
	, m_end			(VSub(m_position, VGet(0.0f, 10.0f, 0.0f)))
	, isMove		(false)
	, speed			(2.0f)
	, m_angle		(0.0f)
	, tempMoveVector(VGet(0.0f, 0.0f, 0.0f))
	
	


	, m_Anim_MoveFrameIndex(-1)
	, m_Anim_AttachIndex(MV1AttachAnim(m_modelHandle, 4))
	, m_Anim_PlayTime(0.0f)
	, m_Anim_TotalTime(0.0f)
	, m_Anim_NowTime(0.0f)
	, m_IsRun(false)

	, m_anim_AttachIndex()
	, m_roring()
	, m_attack()
{
	auto sphereColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(m_colliderData);
	sphereColliderData->radius = 50.0f;




	//m_csvLib = std::make_shared<CSVLib>();
	m_Idm = std::make_shared<InputDeviceManager>();
	m_camera = std::make_shared<Camera>();
	m_command = std::make_shared<Command>();
	m_effectLib = std::make_shared<EffectLib>("../Asset/3D/Effect/kaihitest.efkefc");
	m_effectLib2 = std::make_shared<EffectLib>("../Asset/3D/Effect/rigiTest.efkefc");

 

	
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

	/*m_animAttachIndex.IdelIndex		 = MV1AttachAnim(m_modelHandle, 4);
	m_animAttachIndex.WalkIndex		 = MV1AttachAnim(m_modelHandle, 10);
	m_animAttachIndex.RunIndex		 = MV1AttachAnim(m_modelHandle, 8);
	m_animAttachIndex.RollingIndex	 = MV1AttachAnim(m_modelHandle, 7);
	m_animAttachIndex.Attack1Index;
	m_animAttachIndex.Attack2Index;
	m_animAttachIndex.Attack3Index;
	m_animAttachIndex.Attack4Index;*/

	m_roring.isRoring = false;
	m_roring.isRoringNow = false;
	m_roring.count = 0;

	m_attack.isAttack = false;
	m_attack.isAttackNow = false;
	m_attack.attackCount = 0;
	m_attack.attackTime = 0;
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

void Player::Init(std::shared_ptr<Physics> _physics)
{
	m_Idm.get()->Init();

	m_effectLib.get()->Init("../Asset/3D/Effect/kaihitest.efkefc");
	m_effectLib2.get()->Init("../Asset/3D/Effect/rigiTest.efkefc");


	m_command.get()->Init();

	Collidable::Init(_physics);
	m_righdbody.Init(false);
	m_position = m_righdbody.GetPosition();
	m_direction = m_righdbody.GetDireciton();
	m_velocity = m_righdbody.GetVelocity();;


	isMove = false;
	speed = 2.0f;
	m_angle = 0.0f;
	tempMoveVector = VGet(0.0f, 0.0f, 0.0f);

	/*m_position = VGet(0.0f, 20.0f, 0.0f);
	m_direction = VGet(0.0f, 0.0f, 0.0f);
	m_velocity = VGet(0.0f, 0.0f, 0.0f);*/
	




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





	m_Anim_MoveFrameIndex = 0.0f;
	m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 4);
	m_Anim_PlayTime = 0.0f;
	m_Anim_TotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_Anim_AttachIndex);
	m_Anim_NowTime;
	//loadData("../GameData/PlayerData.csv");

	/*m_animAttachIndex.IdelIndex = MV1AttachAnim(m_modelHandle, 4);
	m_animAttachIndex.WalkIndex = MV1AttachAnim(m_modelHandle, 10);
	m_animAttachIndex.RunIndex = MV1AttachAnim(m_modelHandle, 8);
	m_animAttachIndex.RollingIndex = MV1AttachAnim(m_modelHandle, 7);
	m_animAttachIndex.Attack1Index;
	m_animAttachIndex.Attack2Index;
	m_animAttachIndex.Attack3Index;
	m_animAttachIndex.Attack4Index;*/

	m_roring.isRoring = false;
	m_roring.isRoringNow = false;
	m_roring.count = 0;


	m_attack.isAttack = false;
	m_attack.isAttackNow = false;
	m_attack.attackCount = 0;
	m_attack.attackTime = 0;
}

void Player::Update(std::shared_ptr<Physics> _physics, float _cHAngle, float  _cVAngle, float _SinParam, float _CosParam)
{
	m_Idm.get()->Update();
	m_command.get()->Update();

	auto sphereColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(m_colliderData);
	VECTOR start = m_righdbody.GetPosition();
	VECTOR end = VAdd(start, VGet(0, -sphereColliderData->radius, 0));
	auto  hitObjects = _physics->IsCollideLine(start, end);

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




	if (VSquareSize(m_direction) > 0)
	{
		m_direction = VNorm(m_direction);
	}


	if (isMove == true)
	{
		//m_velocity = VGet(m_direction.x * speed, 0.0f, m_direction.z * speed);

		m_righdbody.SetVelocity(VGet(m_direction.x * speed, 0.0f, m_direction.z * speed));

		m_velocity = m_righdbody.GetVelocity();

		_SinParam = sin(_cHAngle / 180.0f * DX_PI_F);
		_CosParam = cos(_cHAngle / 180.0f * DX_PI_F);

		tempMoveVector.x = m_velocity.x * _CosParam - m_velocity.z * _SinParam;
		tempMoveVector.y = 0.0f;
		tempMoveVector.z = m_velocity.x * _SinParam + m_velocity.z * _CosParam;

		m_position = VAdd(m_position, tempMoveVector);


		//m_position = VAdd(m_velocity, m_position);
	}





	m_righdbody.SetPosition(m_position);

	



	SetFrame();
	MV1SetPosition(m_modelHandle, m_position);
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle / 180.0f * DX_PI_F, 0.0f));
	/*MV1SetRotationXYZ(m_modelHandle, VGet(m_angle,m_angle, m_angle));*/
	MV1SetScale(m_modelHandle, m_scale);

	/*コマンドアクション(start)*/


	//攻撃ボタンが押された
	if (m_command.get()->GetIsAttack() == true)
	{
		//現在攻撃しているフラグをtrueにする
		m_attack.isAttackNow = true;

		//攻撃コンボが４以下の時はカウントを加算し
		if (m_attack.attackCount <= 4)
		{
			m_attack.attackCount++;
		}
		else
		{
			//攻撃コンボが４以上になったらコンボを戻す
			m_attack.attackCount = 2;

		}

	}

	/*コマンドアクション(end)*/




	/*ローリングアクション（start）*/

	if (m_Idm->joyPad->isX == true)
	{
		m_roring.isRoringNow = true;
	}

	if (m_roring.isRoring == true)
	{
		speed = 3.3f;
		
		m_effectLib.get()->PlayEffectLib();
		//m_effectLib2.get()->PlayEffectLib();

		if (m_Anim_PlayTime >= 8.0f)
		{
			MV1SetPosition(m_modelHandle, VGet(m_angle / m_direction.x + speed, m_angle / m_direction.y + speed, m_angle / m_direction.z + speed));
		}
	}
	else
	{
		speed = 2.0f;
	}

	/*ローリングアクション（end）*/




	/*アニメーション（start）*/

	bool isAnimation = false;


	

	if (m_IsRun != isMove)
	{
		m_IsRun = isMove;
		
		MV1DetachAnim(m_modelHandle, m_Anim_AttachIndex);

		if (m_IsRun == true)
		{
			isAnimation = true;
			m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 8);
		}
		else if(m_IsRun == false)
		{
			isAnimation = true;
			m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 4);
		}
	
		m_Anim_TotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_Anim_AttachIndex);

		m_Anim_PlayTime = 0.0f;
		m_roring.isRoringNow = false;

	}
	else
	if (m_roring.isRoring != m_roring.isRoringNow)
	{
		m_roring.isRoring = m_roring.isRoringNow;

		MV1DetachAnim(m_modelHandle, m_Anim_AttachIndex);


		if (m_roring.isRoring == true)
		{
			isAnimation = true;
			m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 7);
		}
		else
		if (m_IsRun == true)
		{
			isAnimation = true;
			m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 8);
		}
		else
		{
			isAnimation = true;
			m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 4);
		}
	

		m_Anim_TotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_Anim_AttachIndex);
		m_Anim_PlayTime = 0.0f;
		m_roring.isRoringNow = false;
	}
	else
	if (m_attack.isAttack != m_attack.isAttackNow)
	{
		m_attack.isAttack = m_attack.isAttackNow;

		MV1DetachAnim(m_modelHandle, m_Anim_AttachIndex);

		if (m_attack.attackCount == 1)
		{
			isAnimation = true;
			m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 0);
		}
		else
		if (m_attack.attackCount == 2)
		{
			isAnimation = true;
			m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 1);
		}
		else
		if (m_attack.attackCount == 3)
		{
			isAnimation = true;
			m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 2);
		}
		else
		if (m_attack.attackCount == 4)
		{
			isAnimation = true;
			m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 3);
		}
		else
			if (m_IsRun == true)
			{
				isAnimation = true;
				m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 8);
			}
			else
			{
				isAnimation = true;
				m_Anim_AttachIndex = MV1AttachAnim(m_modelHandle, 4);
			}



		m_Anim_TotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_Anim_AttachIndex);

		m_Anim_PlayTime = 0.0f;
		m_attack.isAttackNow = false;

	}
	else
	{
		m_Anim_PlayTime += 0.5f;

		if (m_Anim_PlayTime >= m_Anim_TotalTime)
		{
			m_Anim_PlayTime -= m_Anim_TotalTime;
			m_roring.isRoring = false;
		}
	}

	MV1SetAttachAnimTime(m_modelHandle, m_Anim_AttachIndex, m_Anim_PlayTime);

	/*アニメーション（end）*/

	m_effectLib.get()->Update(m_position);
	m_effectLib2.get()->Update(m_position);

}

void Player::Draw()
{
	m_command.get()->Draw();

	MV1DrawModel(m_modelHandle);
	
	m_effectLib.get()->Draw();
	m_effectLib2.get()->Draw();

	DebugDraw();
}

void Player::Final(std::shared_ptr<Physics> _physics)
{
	m_command.get()->Final();
	m_effectLib.get()->Final();
	m_effectLib2.get()->Final();


	MV1DeleteModel(m_modelHandle);
	Collidable::Final(_physics);
}

void Player::OnCollide(const std::shared_ptr<Collidable>& _colider)
{
#ifdef _DEBUG
	std::string message = "プレイヤーが";
	if (_colider->GetTag() == GameObjectTag::Player)
	{
		message += "プレイヤー";
	}
	else if (_colider->GetTag() == GameObjectTag::Enemy)
	{
		message += "敵";
	}
	else if (_colider->GetTag() == GameObjectTag::EnemyMidle)
	{
		message += "中敵";
	}

	message += "と当たった！\n";
	printfDx(message.c_str());
#endif // _DEBUG
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
	//DrawLine3D(targetPos, m_position, 0x00ff00);

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
