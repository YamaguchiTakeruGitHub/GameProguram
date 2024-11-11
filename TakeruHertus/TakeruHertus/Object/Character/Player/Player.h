#pragma once
#include <DxLib.h>
#include <memory>
#include <string>
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

	//std::shared_ptr<CSVLib> m_csvLib;

};

