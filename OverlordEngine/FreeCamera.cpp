#include "stdafx.h"
#include "FreeCamera.h"
#include "TransformComponent.h"

FreeCamera::FreeCamera():
	m_TotalPitch(0),
	m_TotalYaw(0),
	m_MoveSpeed(10),
	m_RotationSpeed(90.f),
	m_SpeedMultiplier(10.0f),
	m_pCamera(nullptr)
{
	SetTag(L"FreeCamera");
}

void FreeCamera::Initialize(const GameContext& )
{
	m_pCamera = new CameraComponent();
	AddComponent(m_pCamera);
}

void FreeCamera::SetRotation(float pitch, float yaw)
{
	m_TotalPitch = pitch;
	m_TotalYaw = yaw;
}

void FreeCamera::Update(const GameContext& gameContext)
{
	// see https://stackoverflow.com/questions/21688529/binary-directxxmvector-does-not-define-this-operator-or-a-conversion
	using namespace DirectX;

	if (m_pCamera->IsActive())
	{
		//HANDLE INPUT
		auto move = XMFLOAT2(0, 0);
		move.y = InputManager::IsKeyboardKeyDown('W') ? 1.0f : 0.0f;
		if (move.y == 0) move.y = -(InputManager::IsKeyboardKeyDown('S') ? 1.0f : 0.0f);
		if (move.y == 0) move.y = InputManager::GetThumbstickPosition().y;

		move.x = InputManager::IsKeyboardKeyDown('D') ? 1.0f : 0.0f;
		if (move.x == 0) move.x = -(InputManager::IsKeyboardKeyDown('A') ? 1.0f : 0.0f);
		if (move.x == 0) move.x = InputManager::GetThumbstickPosition().x;

		auto currSpeed = m_MoveSpeed;
		if (InputManager::IsKeyboardKeyDown(VK_LSHIFT))
			currSpeed *= m_SpeedMultiplier;

		auto look = XMFLOAT2(0, 0);
		if (InputManager::IsMouseButtonDown(VK_RBUTTON))
		{
			const auto mouseMove = InputManager::GetMouseMovement();
			look.x = static_cast<float>(mouseMove.x);
			look.y = static_cast<float>(mouseMove.y);
		}

		if (look.x == 0 && look.y == 0)
		{
			look = InputManager::GetThumbstickPosition(false);
		}

		//CALCULATE TRANSFORMS
		const auto forward = XMLoadFloat3(&GetTransform()->GetForward());
		const auto right = XMLoadFloat3(&GetTransform()->GetRight());
		auto currPos = XMLoadFloat3(&GetTransform()->GetPosition());

		currPos += forward * move.y * currSpeed * gameContext.pGameTime->GetElapsed();
		currPos += right * move.x * currSpeed * gameContext.pGameTime->GetElapsed();

		m_TotalYaw += look.x * m_RotationSpeed * gameContext.pGameTime->GetElapsed();
		m_TotalPitch += look.y * m_RotationSpeed * gameContext.pGameTime->GetElapsed();

		GetTransform()->Rotate(m_TotalPitch, m_TotalYaw, 0);
		GetTransform()->Translate(currPos);
	}
}

void FreeCamera::Serialize(YAML::Emitter & out)
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Serialize(out);
	}

	out << YAML::Anchor("gameobject:" + to_string(m_UniqueID));

	out << YAML::BeginMap;
	out << YAML::Key << "Type";
	out << YAML::Value << "FreeCamera";
	out << YAML::Key << "Tag";
	out << YAML::Value << string{ m_Tag.begin(),m_Tag.end() };
	out << YAML::Key << "m_pParent";
	if (m_pParentObject)
	{
		out << YAML::Alias("gameobject:" + to_string(m_pParentObject->GetID()));

	}
	else
	{
		out << YAML::Value << YAML::Null;

	}
	out << YAML::Key << "ID";
	out << YAML::Value << m_UniqueID;
	out << YAML::Key << "m_pComponents";
	out << YAML::BeginSeq;
	for (BaseComponent* pComp : m_pComponents)
	{
		out << YAML::Alias("component:" + to_string(pComp->GetID()));
	}
	out << YAML::EndSeq;

	out << YAML::EndMap;

	std::cout << "Emitter error: " << out.GetLastError() << "\n";


	for (GameObject* pChild : m_pChildren)
	{
		pChild->Serialize(out);
	}
}
