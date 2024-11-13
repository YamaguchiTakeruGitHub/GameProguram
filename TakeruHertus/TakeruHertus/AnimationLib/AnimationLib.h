#pragma once
#include <map>
#include <string>

class AnimationLib
{
private:
	std::map<std::string, int> animations;//アニメーションの名前とモデルのハンドルのマップ
	int currentAnimHandle;				  //現在再生中のアニメーションハンドル
	bool isAnimating;					  //アニメーションが再生中か否か
	float animSpeed;					  //アニメーションの再生速度
	float currentTime;					  //現在のアニメーション再生時間

public:
	AnimationLib();
	~AnimationLib();

	void LoadAnimation(const std::string& _animName, int _modelHandle, const std::string& _animFilePath);
	void PlayAnimation(const std::string& _animName, bool _loop = true);
	void StopAnimation();
	void SetAnimationSpeed(float _speed);
	void Update(float _deltaTime, int _modelHandle);

};

