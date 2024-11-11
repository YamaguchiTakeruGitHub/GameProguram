#pragma once
#include "JoyPad/JoyPad.h"

class InputDeviceManager
{
public:
	InputDeviceManager();
	~InputDeviceManager();

	/// <summary>
	/// 入力デバイスの初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 入力デバイスの更新
	/// （備考：これを追加しないと入力デバイスは反応しません。）
	/// </summary>
	void Update();


	//インスタンス系
	JoyPad* joyPad;

};
