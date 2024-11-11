#include "Camera.h"

// カメラの回転速度
#define CAMERA_ANGLE_SPEED			1.5f

Camera::Camera()
	: m_position(VGet(0.0f, 0.0f, 50.0f))

{
    m_Idm = std::make_shared<InputDeviceManager>();
}

Camera::~Camera()
{
}

void Camera::Init()
{
    m_Idm.get()->Init();

    m_position = VGet(0.0f, 0.0f, 50.0f);
}

void Camera::Update(VECTOR _target)
{
    m_Idm.get()->Update();
 

    //左スティックの召喚
    float rightStickX = m_Idm.get()->joyPad->GetRightStickX();
    float rightStickY = m_Idm->joyPad->GetRightStickY();

    if (rightStickX != 0 && rightStickX >= -0.030519f && rightStickX <= 0.0f)
    {
  

    }
    if (rightStickX != 0 && rightStickX <= 0.030519f && rightStickX >= 0.0f)
    {
      
    }
    if (rightStickY != 0 && rightStickY <= 0.030519f && rightStickY >= 0.0f)
    {
   
    }
    if (rightStickY != 0 && rightStickY >= -0.030519f && rightStickY <= 0.0f)
    {
       
    }


	SetCom(_target);
}

void Camera::SetCom(VECTOR& _target)
{
	SetCameraNearFar(0.1f, 10000.0f);
	SetCameraPositionAndTarget_UpVecY(m_position, _target);
}


