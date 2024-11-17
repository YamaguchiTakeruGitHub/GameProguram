#pragma once
#include <string>
#include <vector>

class Animation
{
public:
	Animation(std::string _name, int _animIndex, float _totalTime, float _speed);

	void Update(float _deltaTime);

	int GetAnimIndex() const { return m_animIndex; }
	
	float GetCurrentTime() const { return m_curretnTime; }

private:
	std::string m_name;
	int m_animIndex;
	float m_totalTime;
	float m_speed;
	float m_curretnTime;


};

