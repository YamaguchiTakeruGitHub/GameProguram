#pragma once
#include <vector>
#include <DxLib.h>

class DebugDraw3D
{
public:

	static void Clear();
	static void Draw3D();


	/// <summary>
	/// 3D���C���̃f�o�b�N�\��
	/// </summary>
	/// <param name="_start">���̊J�n�_</param>
	/// <param name="_end">���̏I�_</param>
	/// <param name="_color">�f�o�b�N�\���̐F</param>
	static void DrawLine3D(const VECTOR& _start, const VECTOR& _end, int _color);

	/// <summary>
	/// ���̂̃f�o�b�N�\��
	/// </summary>
	/// <param name="_center">:�|�W�V����</param>
	/// <param name="_radius">�F���a</param>
	/// <param name="color">�F�f�o�b�N�\���̐F</param>
	/// <param name="alpha">�F�����x</param>
	/// <param name="isWire">�F���C���[�\�������邩�ۂ�</param>
	static void DrawSphere(const VECTOR& _center, float _radius, int _color, float _alpha = 1.0f, bool _isWire = true);

private:

	struct Line3DInfo
	{
		VECTOR start;
		VECTOR end;
		int color;
	};

	struct SphereInfo
	{
		VECTOR center;
		float radius;
		int color;
		float alpha;
		bool isWire;
	};

	
	static std::vector<SphereInfo> sphereInfo;
	static std::vector<Line3DInfo> line3DInfo;


};
