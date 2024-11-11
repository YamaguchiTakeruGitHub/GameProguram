#pragma once
#include "ColliderCommon.h"//�����蔻��̎�ނ܂Ƃ�

/// <summary>
/// �����蔻��̏W�񁕒ʒm���X�V
/// </summary>
class ColliderManager
{
public:
	ColliderManager();
	~ColliderManager();

	void CheckCollider();
	void HitCollider();
	void Update();

private:
	//�����蔻���ނ��i�[���邽�߂̃����o
	std::vector<std::shared_ptr<ColliderBase>> m_colliders;

};

