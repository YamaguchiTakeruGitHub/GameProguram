#include "EnemySmallFish.h"

EnemySmallFish::EnemySmallFish()
	: Collidable(Collidable::Priority::High , GameObjectTag::Enemy, ColliderData::Kind::Sphere)
	, modelHandle(-1)
	, scale(VGet(0,0,0))
	, helth()
{
	auto sphereColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(m_colliderData);
	sphereColliderData->radius = 50.0f;
}

EnemySmallFish::~EnemySmallFish()
{
}

void EnemySmallFish::Init(std::shared_ptr<Physics> _physics)
{
	Collidable::Init(_physics);
	m_righdbody.Init(false);
	m_righdbody.SetPosition(VGet(0.0f, 0.0f, 30.0f));
	modelHandle = MV1LoadModel("../Asset/3D/Character/Enemy/EnemySmole/Enemy_fox.mv1");
	scale = VGet(0.2f, 0.2f, 0.2f);
}

void EnemySmallFish::Final(std::shared_ptr<Physics> _physics)
{
	Collidable::Final(_physics);
	MV1DeleteModel(modelHandle);
}

void EnemySmallFish::Update(std::shared_ptr<Physics> _physics)
{
	auto sphereData = std::dynamic_pointer_cast<ColliderDataSphere3D>(m_colliderData);
	VECTOR start = m_righdbody.GetPosition();
	VECTOR END = VAdd(start, VGet(0, -sphereData->radius, 0));
	
	// 矢印キーを押していたらプレイヤーを移動させる
	// 向きを決定する.
	VECTOR dir = VGet(0, 0, 0);
	dir.x = 0;
	dir.y = 0;
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		dir.z = 3;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		dir.z = -3;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		dir.x = -3;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		dir.x = 3;
	}

	// 余計な数値が入るので、純粋に長さ１の向きとして正規化する
	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}

	
	m_righdbody.SetVelocity(VGet(dir.x, dir.y, dir.z));

	m_righdbody.SetPosition(m_righdbody.GetPosition());
	MV1SetPosition(modelHandle, m_righdbody.GetPosition());
	MV1SetScale(modelHandle, scale);
}

void EnemySmallFish::Draw(std::shared_ptr<Physics> _physics)
{
	MV1DrawModel(modelHandle);
}

void EnemySmallFish::OnCollide(const std::shared_ptr<Collidable>& _colider)
{
#ifdef _DEBUG
	std::string message = "小敵が";
	if (_colider->GetTag() == GameObjectTag::Enemy)
	{
		message += "敵";
	}
	else if (_colider->GetTag() == GameObjectTag::EnemyMidle)
	{
		message += "中敵";
	}
	else if (_colider->GetTag() == GameObjectTag::Player)
	{
		message += "プレイヤー";
	}

	message += "と当たった！\n";
	printfDx(message.c_str());
#endif // _DEBUG
}
