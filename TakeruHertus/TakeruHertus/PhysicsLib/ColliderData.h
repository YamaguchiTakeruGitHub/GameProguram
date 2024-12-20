#pragma once
#include <DxLib.h>

/// <summary>
/// 当たり判定のデータ
/// </summary>
class ColliderData
{
public:

	/// <summary>
	/// 当たり判定の種類
	/// </summary>
	enum class Kind
	{
		Sphere,
		Capsule,
		AABB,
		OBB,
	};

	ColliderData(Kind _kind) { this->m_kind = _kind; }
	virtual ~ColliderData(){}

	/// <summary>
	/// 当たり判定の種類を取得する
	/// </summary>
	/// <returns></returns>
	Kind GetKind() const { return m_kind; }

private:
	Kind m_kind;

};

