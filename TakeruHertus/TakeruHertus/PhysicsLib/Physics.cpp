#include "Physics.h"

void Physics::Entry(std::shared_ptr<Collidable> _collidable)
{
	//�w�肳�ꂽ�l���������Ĉ�ԍŌ�ȊO
	bool found = (std::find(m_collidables.begin(), m_collidables.end(), _collidable) != m_collidables.end());
	
	//�o�^����ĂȂ��ꍇ
	if (!found)
	{
		m_collidables.emplace_back(_collidable);
	}
	else//�o�^����Ă����ꍇ�̓G���[��Ԃ�
	{
		assert(0 && "�w���collidable�͓o�^�ς݂ł��B");
	}
}

void Physics::Exit(std::shared_ptr<Collidable> _collidable)
{
	bool found = (std::find(m_collidables.begin(), m_collidables.end(), _collidable) != m_collidables.end());

	//�o�^�̉���
	if (found)
	{
		m_collidables.remove(_collidable);
	}
	else//�o�^����Ă��Ȃ��ꍇ�G���[���o��
	{
		assert(0 && "�w���collidable���o�^����Ă��܂���B");
	}

}

void Physics::Update()
{
	//m_collidables�͈͎̔w��
	for (auto& item : m_collidables)
	{
		auto pos = item->m_righdbody.GetPosition();//�e�I�u�W�F�N�g����|�W�V�������擾
		auto velocity = item->m_righdbody.GetVelocity();//�e�I�u�W�F�N�g����x���V�e�B���擾

		//�d�͂�K������I�u�W�F�N�g�ɑ΂���
		if (item->m_righdbody.UseGravity())
		{
			velocity = VAdd(velocity, VGet(0, m_gravity, 0));//�x���V�e�B�ɏd�͂����Z

			//�x���V�e�BY���W���ő�d�͉����x��������Ă�����
			if (velocity.y < m_maxGravityAccel)
			{
				//����ȏ�������Ȃ��悤�ɂ���
				velocity = VGet(velocity.x, m_maxGravityAccel, velocity.z);
			}
		}

		auto nextPos = VAdd(pos, velocity);//�X�V���W���i�[

		//�x���V�e�B�ƃf�B���N�V�����������ϊ�
		item->m_righdbody.SetVelocity(velocity);

#ifdef _DEBUG
		//�e�I�u�W�F�N�g�̎�ނ��擾
		auto kind = item->m_colliderData->GetKind();
		
		//�I�u�W�F�N�g�����̂̏ꍇ
		if (kind == ColliderData::Kind::Sphere)
		{
			//���̃f�[�^�̃|�C���^���L
			std::shared_ptr<ColliderDataSphere3D> sphereData;
			//�Q�Ƃ����ꉹ����ϊ�����
			sphereData = std::dynamic_pointer_cast<ColliderDataSphere3D>(item->m_colliderData);
			//���a���擾
			float radius = sphereData.get()->radius;

			/*���̂̃f�o�b�N�\�����s��*/
			DebugDraw3D::DrawSphere(pos, radius, BeforFixInfoColor);
			DebugDraw3D::DrawLine3D(pos, nextPos, AimInfoColor);
			DebugDraw3D::DrawSphere(nextPos, radius, AimInfoColor);
		}
#endif // _DEBUG

		//���W���X�V����
		item->m_nextPos = nextPos;
	}

	//�Փ˂��m�F
	std::vector<OnCollideInfo> onCollideInfo = CheckColide();

	//�ʒu�̊m��
	FixPosition();

	//�����蔻���ʒm
	for (auto& item : onCollideInfo)
	{
		item.owner->OnCollide(item.colider);
	}

}

std::vector<Physics::OnCollideInfo> Physics::CheckColide() const
{
	std::vector<OnCollideInfo> onCollideInfo;
	bool doCheck = true;
	int checkCount = 0;

	while (doCheck)
	{
		doCheck = false;
		++checkCount;

		for (auto& objA : m_collidables)
		{
			for (auto& objB : m_collidables)
			{
				if (objA != objB)
				{
					if (IsCollide(objA, objB))
					{
						auto priorityA = objA->GetPriority();
						auto priorityB = objB->GetPriority();

						std::shared_ptr<Collidable> primary = objA;
						std::shared_ptr<Collidable> secondary = objB;
						if (priorityA < priorityB)
						{
							primary = objB;
							primary = objA;
						}
						FixNextPosition(primary, secondary);

						bool hasPrimaryInfo = false;
						bool hasSecondaryInfo = false;
						for (const auto& item : onCollideInfo)
						{
							if (item.owner == primary)
							{
								hasPrimaryInfo = true;
							}
							if (item.owner == secondary)
							{
								hasSecondaryInfo = true;
							}
						}
						if (!hasPrimaryInfo)
						{
							onCollideInfo.push_back({ primary, secondary });
						}
						if (!hasSecondaryInfo)
						{
							onCollideInfo.push_back({ secondary, primary });
						}

						doCheck = true;
						break;
					}
				}
			}
			if (doCheck)
			{
				break;
			}
		}

		if (checkCount > 1000 && doCheck)
		{
#ifdef _DEBUG
			printfDx("�����蔻��̌J��Ԃ��`�F�b�N����ꐔ�𒴂���\n");
#endif // _DEBUG
			break;
		}
	}
	return onCollideInfo;
}

std::list<std::shared_ptr<Collidable>> Physics::IsCollideLine(const VECTOR& _start, const VECTOR& _end) const
{
	std::list<std::shared_ptr<Collidable>> ret;
	for (auto& obj : m_collidables)
	{
		auto kind = obj->m_colliderData->GetKind();
		if (kind == ColliderData::Kind::Sphere)
		{
			auto circleColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(obj->m_colliderData);
			bool isHit = (Segment_Point_MinLength(_start, _end, obj->m_righdbody.GetPosition()) < circleColliderData->radius);
			if (isHit)
			{
				ret.emplace_back(obj);
			}
		}
	}

	return ret;
}

bool Physics::IsCollide(const std::shared_ptr<Collidable> _objA, const std::shared_ptr<Collidable> _objB) const
{
	bool isHit = false;
	auto aKind = _objA->m_colliderData->GetKind();
	auto bKind = _objB->m_colliderData->GetKind();

	if (aKind == ColliderData::Kind::Sphere && bKind == ColliderData::Kind::Sphere)
	{
		auto atob = VSub(_objB->m_nextPos, _objA->m_nextPos);
		auto atobLength = VSize(atob);

		auto objAColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(_objA->m_colliderData);
		auto objBColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(_objB->m_colliderData);
		isHit = (atobLength < objAColliderData->radius + objBColliderData->radius);
	}

	return isHit;
}

void Physics::FixNextPosition(std::shared_ptr<Collidable> _primary, std::shared_ptr<Collidable> _secondary) const
{
	auto primaryKind = _primary->m_colliderData->GetKind();
	auto secondaryKind = _secondary->m_colliderData->GetKind();

	if (primaryKind == ColliderData::Kind::Sphere && secondaryKind == ColliderData::Kind::Sphere)
	{
		VECTOR primaryToSecondary = VSub(_secondary->m_nextPos, _primary->m_nextPos);
		VECTOR primaryToSecondaryN = VNorm(primaryToSecondary);

		auto primaryColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(_primary->m_colliderData);
		auto secondaryColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(_secondary->m_colliderData);
		float awayDist = primaryColliderData->radius + secondaryColliderData->radius + 0.0001f;
		VECTOR primaryToNewSecndaryPos = VScale(primaryToSecondaryN, awayDist);
		VECTOR fixedPos = VAdd(_primary->m_nextPos, primaryToNewSecndaryPos);
		_secondary->m_nextPos = fixedPos;
	}
	else
	{
		assert(0 && "������Ă��Ȃ������蔻��ł�");
	}


}

void Physics::FixPosition()
{
	for (auto& item : m_collidables)
	{
#ifdef _DEBUG
		DebugDraw3D::DrawLine3D(item->m_righdbody.GetPosition(), item->m_nextPos, AfterFixInfoColor);

		if (item->m_colliderData->GetKind() == ColliderData::Kind::Sphere)
		{
			auto itemCircleData = std::dynamic_pointer_cast<ColliderDataSphere3D>(item->m_colliderData);
			DebugDraw3D::DrawSphere(item->m_nextPos, itemCircleData->radius, AfterFixInfoColor);
		}
#endif // _DEBUG

		VECTOR toFixedPos = VSub(item->m_nextPos, item->m_righdbody.GetPosition());
		item->m_righdbody.SetVelocity(toFixedPos);

		item->m_righdbody.SetPosition(item->m_nextPos);
	}
}

void Physics::OnCollideInfo::OnCollide()
{
	owner.get()->OnCollide(colider);
}
