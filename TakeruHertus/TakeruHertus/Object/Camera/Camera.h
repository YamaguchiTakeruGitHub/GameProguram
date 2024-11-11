#pragma once
#include <DxLib.h>
#include <memory>
#include "../../InputDevice/InputDeviceManager.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update(VECTOR _target);
	void SetCom(VECTOR& _target);


private:
	VECTOR m_position;

	std::shared_ptr<InputDeviceManager> m_Idm;

};

