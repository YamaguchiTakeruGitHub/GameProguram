#pragma once
#include "../ColliderData.h"

/// <summary>
/// �����蔻��f�[�^�F3D��
/// </summary>
class ColliderDataOBB3D : public ColliderData
{
public:
	ColliderDataOBB3D();

	VECTOR extents;//���_�̈ʒu
	MATRIX rotation;//��]�s��
};

