﻿#pragma once

#include "Camera.h"
#include "Input.h"

// デバッグ用カメラ
class DebugCamera : public Camera
{
	// DirectX::を省略
	using XMMATRIX = DirectX::XMMATRIX;
public:
	// コンストラクタ
	DebugCamera(int window_width, int window_height, Input* input);

	// 更新
	void Update() override;

	void SetDistance(float distance) {
		this->distance = distance; viewDirty = true;
	}

private:
	// 入力クラスのポインタ
	Input* input;
	// カメラ注視点までの距離
	float distance = 20;
	// スケーリング
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	// 回転行列
	XMMATRIX matRot = DirectX::XMMatrixIdentity();
};