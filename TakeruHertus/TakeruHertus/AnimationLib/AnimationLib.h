#pragma once
#include <map>
#include <string>

class AnimationLib
{
private:
	std::map<std::string, int> animations;//�A�j���[�V�����̖��O�ƃ��f���̃n���h���̃}�b�v
	int currentAnimHandle;				  //���ݍĐ����̃A�j���[�V�����n���h��
	bool isAnimating;					  //�A�j���[�V�������Đ������ۂ�
	float animSpeed;					  //�A�j���[�V�����̍Đ����x
	float currentTime;					  //���݂̃A�j���[�V�����Đ�����

public:
	AnimationLib();
	~AnimationLib();

	void LoadAnimation(const std::string& _animName, int _modelHandle, const std::string& _animFilePath);
	void PlayAnimation(const std::string& _animName, bool _loop = true);
	void StopAnimation();
	void SetAnimationSpeed(float _speed);
	void Update(float _deltaTime, int _modelHandle);

};

