#pragma once
#include <vector>
#include <DxLib.h>

class DebugDraw3D
{
public:

	static void Clear();
	static void Draw3D();


	/// <summary>
	/// 3Dラインのデバック表示
	/// </summary>
	/// <param name="_start">線の開始点</param>
	/// <param name="_end">線の終点</param>
	/// <param name="_color">デバック表示の色</param>
	static void DrawLine3D(const VECTOR& _start, const VECTOR& _end, int _color);

	/// <summary>
	/// 球体のデバック表示
	/// </summary>
	/// <param name="_center">:ポジション</param>
	/// <param name="_radius">：半径</param>
	/// <param name="color">：デバック表示の色</param>
	/// <param name="alpha">：透明度</param>
	/// <param name="isWire">：ワイヤー表示をするか否か</param>
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

