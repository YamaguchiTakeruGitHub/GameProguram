#pragma once
#include "../ColliderBase.h"

/// <summary>
/// 
/// </summary>
class Capsule : public ColliderBase
{
public:

	Capsule(VECTOR& _start, VECTOR& _end, float& _radius);
	~Capsule() {};

	void SetCapsuleRad(const float& _radius) { this->m_radius = _radius; }
	float GetCapsuleRad() const { return this->m_radius; }

	void SetCapsuleStart(const VECTOR& _start) { this->m_start = _start; }
	VECTOR GetCapsuleStart() const { return this->m_start; }

	void SetCapsuleEnd(const VECTOR& _end) { this->m_end = _end; }
	VECTOR GetCapsuleEnd() const { return this->m_end; }

private:

	float m_radius;
	VECTOR m_start;
	VECTOR m_end;
};

