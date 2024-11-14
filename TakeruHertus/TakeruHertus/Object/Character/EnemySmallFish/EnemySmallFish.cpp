#include "EnemySmallFish.h"

EnemySmallFish::EnemySmallFish()
	: Collidable(Collidable::Priority::High , GameObjectTag::Enemy, ColliderData::Kind::Sphere)
	, modelHandle(-1)
{
	auto sphereColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(m_colliderData);
	sphereColliderData->radius = 10.0f;
}
//	: Collidable(Collidable::Priority::High, GameObjectTag::Enemy, ColliderData::Kind::Capsule)
//{
//	auto capsuleColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(m_colliderData);
//	capsuleColliderData.get()->size = 10.0f;
//	capsuleColliderData.get()->start = VAdd(m_righdbody.GetPosition(), VGet(0.0f, capsuleColliderData->size, 0.0f));
//	capsuleColliderData.get()->end = VSub(m_righdbody.GetPosition(), VGet(0.0f, capsuleColliderData->size, 0.0f));
//	capsuleColliderData.get()->radius = 10.0f;
//}

EnemySmallFish::~EnemySmallFish()
{
}

void EnemySmallFish::Init(std::shared_ptr<Physics> _physics)
{
	Collidable::Init(_physics);
	m_righdbody.Init(false);
	m_righdbody.SetPosition(VGet(0.0f, 20.0f, 60.0f));

	modelHandle = -1;
}

void EnemySmallFish::Final(std::shared_ptr<Physics> _physics)
{
	Collidable::Final(_physics);
}

void EnemySmallFish::Update(std::shared_ptr<Physics> _physics)
{
	
	// ���L�[�������Ă�����v���C���[���ړ�������
	// ���������肷��.
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

	// �]�v�Ȑ��l������̂ŁA�����ɒ����P�̌����Ƃ��Đ��K������
	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}

	
	m_righdbody.SetVelocity(VGet(dir.x, dir.y, dir.z));

	MV1SetPosition(modelHandle, m_righdbody.GetPosition());

}

void EnemySmallFish::Draw(std::shared_ptr<Physics> _physics)
{
}

void EnemySmallFish::OnCollide(const std::shared_ptr<Collidable>& _colider)
{
	std::string message = "���G��";
	if (_colider->GetTag() == GameObjectTag::Enemy)
	{
		message += "���G";
	}
	else if (_colider->GetTag() == GameObjectTag::EnemyMIdle)
	{
		message += "���G";
	}
	else if (_colider->GetTag() == GameObjectTag::Player)
	{
		message += "�v���C���[";
	}
	
	message += "�Ɠ��������I\n";
	printfDx(message.c_str());
}
