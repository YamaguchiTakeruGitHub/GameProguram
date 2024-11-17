#pragma once
#include <memory>
#include <unordered_map>
#include "Animation.h"

class AnimationManager
{
public:
	void AddAnimation(const Animation& _animation);

	void SetCurrentAnimation(int _animIndex);

	void UpdateCurrentAnimation(float _deltaTime);

	int GetCurrentAnimIndex() const;

private:
	std::unordered_map<int, Animation> m_animations;
	int m_curretnAnimIndex = -1;

};

