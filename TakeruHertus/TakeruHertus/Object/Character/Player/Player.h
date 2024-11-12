#pragma once
#include <DxLib.h>
#include <memory>
#include <string>
#include "../../../InputDevice/InputDeviceManager.h"
#include "../../Camera/Camera.h"
//#include "../../LibCom/CSVLib/CSVLib.h"


/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	~Player();

	//void loadData(const std::string& _filename);


	void Init();
	void Update(float _cHAngle, float  _cVAngle, float _SinParam, float _CosParam);
	void Draw();
	void Final();
	void SetFrame();

	void SetPosition(const VECTOR& _position) { this->m_position = _position; }
	VECTOR GetPosition() const { return  this->m_position; }

private:
	float NormalizeAngle(float _angle);
	float targetRotationY;
	VECTOR targetDirection;
	VECTOR targetPos;
	float rotationY;

	void DebugDraw();

	std::shared_ptr<InputDeviceManager> m_Idm;
	std::shared_ptr<Camera> m_camera;




	bool isMove;
	float speed;
	float m_angle;


	VECTOR tempMoveVector;





	//���f���̃n���h�����i�[
	int m_modelHandle;

	//���f���̃|�W�V�������i�[
	VECTOR m_position;
	VECTOR m_velocity;
	VECTOR m_direction;

	/// <summary>
	/// ���f���̃t���[���|�W�V����
	/// </summary>
	struct FramPos
	{
		VECTOR head;		//��

		VECTOR leftHand;	//����
		VECTOR rightHand;	//�E��

		VECTOR leftElbow;	//���I
		VECTOR rightElbow;	//�E�I

		VECTOR leftShoulder;//����
		VECTOR rightShoulder;//�E��

		VECTOR rightfeet;	//�E��
		VECTOR leftfeet;	//����

		VECTOR rightKnees;	//�E�G
		VECTOR leftKnees;	//���G


		VECTOR crotch;		//��



	}m_frame;


	//���f���̃X�P�[��
	VECTOR m_scale;

	//���a
	float m_radius;
	
	//�J�v�Z���̈�ԏ�
	VECTOR m_start;

	//�J�v�Z���̈�ԉ�
	VECTOR m_end;

	//std::shared_ptr<CSVLib> m_csvLib;

};

