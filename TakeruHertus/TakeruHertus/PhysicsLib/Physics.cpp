#include "Physics.h"

void Physics::Entry(std::shared_ptr<Collidable> _collidable)
{
	//指定された値を検索して一番最後以外
	bool found = (std::find(m_collidables.begin(), m_collidables.end(), _collidable) != m_collidables.end());
	
	//登録されてない場合
	if (!found)
	{
		m_collidables.emplace_back(_collidable);
	}
	else//登録されていた場合はエラーを返す
	{
		assert(0 && "指定のcollidableは登録済みです。");
	}
}

void Physics::Exit(std::shared_ptr<Collidable> _collidable)
{
	bool found = (std::find(m_collidables.begin(), m_collidables.end(), _collidable) != m_collidables.end());

	//登録の解除
	if (found)
	{
		m_collidables.remove(_collidable);
	}
	else//登録されていない場合エラーを出す
	{
		assert(0 && "指定のcollidableが登録されていません。");
	}

}

void Physics::Update()
{
	//m_collidablesの範囲指定
	for (auto& item : m_collidables)
	{
		auto pos = item->m_righdbody.GetPosition();//各オブジェクトからポジションを取得
		auto velocity = item->m_righdbody.GetVelocity();//各オブジェクトからベロシティを取得

		//重力を適応するオブジェクトに対して
		if (item->m_righdbody.UseGravity())
		{
			velocity = VAdd(velocity, VGet(0, m_gravity, 0));//ベロシティに重力を加算

			//ベロシティY座標が最大重力加速度を下回っていたら
			if (velocity.y < m_maxGravityAccel)
			{
				//それ以上加速しないようにする
				velocity = VGet(velocity.x, m_maxGravityAccel, velocity.z);
			}
		}

		auto nextPos = VAdd(pos, velocity);//更新座標を格納

		//ベロシティとディレクションを自動変換
		item->m_righdbody.SetVelocity(velocity);

#ifdef _DEBUG
		//各オブジェクトの種類を取得
		auto kind = item->m_colliderData->GetKind();
		
		//オブジェクトが球体の場合
		if (kind == ColliderData::Kind::Sphere)
		{
			//球体データのポインタ共有
			std::shared_ptr<ColliderDataSphere3D> sphereData;
			//参照をしつつポインタを変換する
			sphereData = std::dynamic_pointer_cast<ColliderDataSphere3D>(item->m_colliderData);
			//半径を取得
			float radius = sphereData.get()->radius;

			/*球体のデバック表示を行う*/
			DebugDraw3D::DrawSphere(pos, radius, BeforFixInfoColor);
			DebugDraw3D::DrawLine3D(pos, nextPos, AimInfoColor);
			DebugDraw3D::DrawSphere(nextPos, radius, AimInfoColor);
		}
		//オブジェクトがカプセルの場合
		else if (kind == ColliderData::Kind::Capsule)
		{
			//カプセルデータをポインタ共有
			std::shared_ptr<ColliderDataCapsule3D> capsuleData;
			//参照しつつポインタを変換する
			capsuleData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(item->m_colliderData);
			
			//カプセル頭を取得
			VECTOR start = capsuleData.get()->start;
			//カプセルの足元を取得
			VECTOR end = capsuleData.get()->end;
			//カプセルの上下の長さを取得
			float size = capsuleData.get()->size;
			//半径を取得
			float radius = capsuleData.get()->radius;

			/*カプセルのデバック表示を行う*/
			DebugDraw3D::DrawCapsule(pos, start, end, size, radius, BeforFixInfoColor);
			DebugDraw3D::DrawLine3D(pos, nextPos, AimInfoColor);
			DebugDraw3D::DrawCapsule(pos, start, end, size, radius, AimInfoColor);
		}


#endif // _DEBUG

		//座標を更新する
		item->m_nextPos = nextPos;
	}

	//衝突を確認
	std::vector<OnCollideInfo> onCollideInfo = CheckColide();

	//位置の確定
	FixPosition();

	//当たり判定を通知
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
			printfDx("当たり判定の繰り返しチェックが基底数を超えた\n");
#endif // _DEBUG
			break;
		}
	}
	return onCollideInfo;
}

/// <summary>
/// 指定ラインがオブジェクトとぶつかっているかどうか判定し、ぶつかっているオブジェクトを返す
/// </summary>
/// <param name="_start"></param>
/// <param name="_end"></param>
/// <returns></returns>
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
		//ラインとカプセル
		else if (kind == ColliderData::Kind::Capsule)
		{
			auto capsuleColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(obj->m_colliderData);
			float capsuleLength = VSize(VSub(capsuleColliderData->start, capsuleColliderData->end));
			bool isHit = (Segment_Point_MinLength(_start, _end, obj->m_righdbody.GetPosition()) < capsuleLength + capsuleColliderData->radius);
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
	//カプセルとカプセル
	else if (aKind == ColliderData::Kind::Capsule && bKind == ColliderData::Kind::Capsule)
	{
		//auto closestPoint1, closestPoint2;
		auto objAColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(_objA->m_colliderData);
		auto objBColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(_objB->m_colliderData);
		
		auto objAStart = objAColliderData->start;
		auto objAEnd = objAColliderData->end;

		auto objBStart = objBColliderData->start;
		auto objBEnd = objBColliderData->end;


		isHit = (DistanceBetweenSegments(objAStart, objAEnd, objBStart, objBEnd) <= (objAColliderData->radius + objBColliderData->radius));
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
	else if (primaryKind == ColliderData::Kind::Capsule && secondaryKind == ColliderData::Kind::Capsule)
	{

	}

	else
	{
		assert(0 && "許可されていない当たり判定です");
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

float Physics::DistanceBetweenSegments(const VECTOR _p1, const VECTOR _q1, const VECTOR _p2, const VECTOR _q2) const
{
	VECTOR d1 = VSub(_q1, _p1);
	VECTOR d2 = VSub(_q2, _p2);
	VECTOR r = VSub(_p1, _p2);

	float a = VDot(d1, d1);
	float e = VDot(d2, d2);
	float f = VDot(d2, r);

	float s, t;
	float c = VDot(d1, r);
	float b = VDot(d1, d2);
	
	float denom = a * e - b * b;

	if (denom != 0.0f)
	{
		s = (b * f - c * e) / denom;
		s = Clamp(s, 0.0f, 1.0f);
	}
	else
	{
		s = 0.0f;
	}

	t = (b * s + f) / e;
	t = Clamp(t, 0.0f, 1.0f);
	
	s = (b * t - c) / a;
	s = Clamp(s, 0.0f, 1.0f);
	
	VECTOR closePoint1 = VAdd(_p1, VScale(d1, s));
	VECTOR closePoint2 = VAdd(_p2, VScale(d2, t));
	VECTOR diff = VSub(closePoint1, closePoint2);

	return VSize(diff);
}

//void Physics::ResolveCapsuleCollision(VECTOR _capsuleStartPos1, VECTOR _capsuleEndPos1, VECTOR _capsuleStartPos2, VECTOR _capsuleEndPos2, float _r1, float _r2)
//{
//	VECTOR closestPoint1, closestPoint2;
//	float distance = DistanceBetweenSegments(_capsuleEndPos1, _capsuleEndPos1, _capsuleStartPos2, _capsuleEndPos2, closestPoint1, closestPoint2);
//	
//	float overlap = _r1 + _r2 - distance;
//
//	if (overlap <= 0.0f)
//	{
//		return;
//	}
//
//	VECTOR pushDir = VNorm(VSub(closestPoint1, closestPoint2));
//
//	VECTOR pushVector = VScale(pushDir, overlap / 2.0f);
//
//	
//
//
//}

void Physics::OnCollideInfo::OnCollide()
{
	owner.get()->OnCollide(colider);
}
