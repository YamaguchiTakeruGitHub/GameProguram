#pragma once
#include "../ColliderBase.h"

class OBB : public ColliderBase
{
public:

	OBB(VECTOR& _extents, MATRIX& _rotation);
	~OBB() {}

	/*void SetOBBExtents(const VECTOR& _extents) { this->m_extents = _extents; }
	VECTOR GetOBBExtens() const { return this->m_extents; }

	void SetOBBRotation(const MATRIX& _rotation) { this->m_rotation = _rotation; }
	MATRIX GetOBBRotation() const { return this->m_rotation; }*/

private:
	
	VECTOR m_extents;//OBBの半分のサイズ
	MATRIX m_rotation;//OBBの回転行列
};

