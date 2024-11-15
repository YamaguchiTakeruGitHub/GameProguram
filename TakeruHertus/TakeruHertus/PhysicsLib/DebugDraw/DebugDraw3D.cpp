#include "DebugDraw3D.h"

std::vector<DebugDraw3D::SphereInfo>  DebugDraw3D::sphereInfo;
std::vector<DebugDraw3D::Line3DInfo>  DebugDraw3D::line3DInfo;
std::vector<DebugDraw3D::CapsuleInfo> DebugDraw3D::capsuleInfo;

void DebugDraw3D::Clear()
{
	line3DInfo.clear();
	sphereInfo.clear();
	capsuleInfo.clear();
}

void DebugDraw3D::Draw3D()
{
	for (const auto& item : line3DInfo)
	{
		DxLib::DrawLine3D(
			item.start,
			item.end,
			item.color
		);
	}

	for (const auto& item : sphereInfo)
	{
		DxLib::DrawSphere3D(
			item.center,
			item.radius,
			6,
			item.color,
			item.color,
			false
		);
	}

	for (const auto& item : capsuleInfo)
	{
		DxLib::DrawCapsule3D(
			item.start,
			item.end,
			item.radius,
			6,
			item.color,
			item.color,
			false
		);
	}

}

void DebugDraw3D::DrawLine3D(const VECTOR& _start, const VECTOR& _end, int _color)
{
	Line3DInfo newInfo;
	newInfo.start = _start;
	newInfo.end = _end;
	newInfo.color = _color;
	line3DInfo.emplace_back(newInfo);
}

void DebugDraw3D::DrawSphere(const VECTOR& _center, float _radius, int _color, float _alpha, bool _isWire)
{
	SphereInfo newInfo;
	newInfo.center = _center;
	newInfo.radius = _radius;
	newInfo.color = _color;
	newInfo.alpha = _alpha;
	newInfo.isWire = _isWire;
	sphereInfo.emplace_back(newInfo);
}

void DebugDraw3D::DrawCapsule(const VECTOR& _center, const VECTOR& _start, const VECTOR& _end, const float _size, float _radius, int _color, float _alpha, bool _isWire)
{
	CapsuleInfo newInfo;
	newInfo.center = _center;
	newInfo.size = _size;
	newInfo.start = VAdd(_center, VGet(0.0f, _size, 0.0f));
	newInfo.end = VSub(_center, VGet(0.0f, _size, 0.0f));
	newInfo.radius = _radius;
	newInfo.color = _color;
	newInfo.alpha = _alpha;
	newInfo.isWire = _isWire;
	capsuleInfo.emplace_back(newInfo);

}
