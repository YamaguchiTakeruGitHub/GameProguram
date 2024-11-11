#pragma once
#include "../ColliderBase.h"

/// <summary>
/// 軸並行ボックス
/// </summary>
class AABB : public ColliderBase
{
public:

	AABB(VECTOR _start, VECTOR _end);
	~AABB() {};

	/*void SetAABBStart(const VECTOR& _SetStart) { start = _SetStart; }
	VECTOR GetAABBStart() const { return start; }

	void SetAABBEnd(const VECTOR& _SetEnd) { end = _SetEnd; }
	VECTOR GetAABBEnd() const { return end; }*/

private:
	VECTOR m_start;
	VECTOR m_end;
};

