#pragma once
#include "ColliderCommon.h"//当たり判定の種類まとめ

/// <summary>
/// 当たり判定の集約＆通知＆更新
/// </summary>
class ColliderManager
{
public:
	ColliderManager();
	~ColliderManager();

	void CheckCollider();
	void HitCollider();
	void Update();

private:
	//当たり判定種類を格納するためのメンバ
	std::vector<std::shared_ptr<ColliderBase>> m_colliders;

};

