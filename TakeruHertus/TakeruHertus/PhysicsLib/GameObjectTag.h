#pragma once

/// <summary>
/// 衝突したオブジェクトの判別を行うためのタグ
/// </summary>
enum class GameObjectTag
{
	Player,	//プレイヤー
	Enemy,	//敵
	Wall,	//壁
	Ground,	//地面
};