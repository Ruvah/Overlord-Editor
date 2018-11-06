#include "stdafx.h"
#include "FixedCamera.h"
#include "TransformComponent.h"

void FixedCamera::Initialize(const GameContext& )
{
	AddComponent(new CameraComponent());
	SetTag(L"FixedCamera");

	//TODO: remove magic transform/value
	GetTransform()->Translate(0,0,-10);
}