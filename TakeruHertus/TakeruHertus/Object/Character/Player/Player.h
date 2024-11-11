#pragma once
#include <DxLib.h>
#include "../../../Collider/Capsule/Capsule.h"
#include <memory>

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();
	void Final();

	void SetPosition(const VECTOR& _position) { this->m_position = _position; }
	VECTOR GetPosition() const { return  this->m_position; }



private:

	//���f���̃n���h�����i�[
	int m_modelHandle;

	//���f���̃|�W�V�������i�[
	VECTOR m_position;
	
	//���a
	float m_radius;
	
	//�J�v�Z���̈�ԏ�
	VECTOR m_start;

	//�J�v�Z���̈�ԉ�
	VECTOR m_end;


};

