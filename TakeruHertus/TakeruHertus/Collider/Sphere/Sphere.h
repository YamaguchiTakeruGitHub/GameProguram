#pragma once
#include "../ColliderBase.h"

class Sphere : public ColliderBase
{
public:
	Sphere(float& _radius);
	~Sphere() {}

	void SetSphereRad(const float& _radius) { this->m_radius = _radius; }
	float GetSphereRad() const { return this->m_radius; }

private:
	float m_radius;

};

