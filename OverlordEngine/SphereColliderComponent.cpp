#include "stdafx.h"
#include "SphereColliderComponent.h"
#include <PhysxManager.h>
#include <PhysxProxy.h>
#include <ColliderComponent.h>
#include <GameObject.h>
#include <TransformComponent.h>
#include <DirectXCollision.h>
#include <DirectXDebugDraw.h>
#include <AssetManager.h>
#include <Serialization.h>

using namespace DirectX;
SphereColliderComponent::SphereColliderComponent():
	m_Radius(1),
	m_pPhysxMaterial{nullptr},
	m_pColliderComponent{nullptr},
	m_EulerAngles{0,0,0},
	m_IsTrigger{false},
	m_MaterialAssetID{},
	m_DidConvert{false}
{
}



void SphereColliderComponent::SetRadius(float radius)
{
	m_Radius = radius;
}

void SphereColliderComponent::SetAngles(physx::PxVec3 axis)
{
	m_EulerAngles = axis;
}





void SphereColliderComponent::SetTrigger(bool isTrigger)
{
	m_IsTrigger = isTrigger;
}

void SphereColliderComponent::SetMaterialAssID(int id)
{
	m_MaterialAssetID = id;
}



void SphereColliderComponent::ConvertToLowLvl()
{
	ParseMaterial();
	auto physX = PhysxManager::GetInstance()->GetPhysics();
	std::shared_ptr<physx::PxGeometry> pGeom(
		new physx::PxSphereGeometry(m_Radius));

	physx::PxVec4 axisAngle{};
	OVLFunc::PxEulerToAxisAngle(m_EulerAngles, axisAngle);
	m_pColliderComponent =
		new ColliderComponent(pGeom, *m_pPhysxMaterial,
			physx::PxTransform(physx::PxQuat(axisAngle.w, axisAngle.getXYZ())));
	m_pColliderComponent->EnableTrigger(m_IsTrigger);
	m_pGameObject->AddComponent(m_pColliderComponent);
	m_pGameObject->RemoveComponent(this);

	m_DidConvert = true;
}

void SphereColliderComponent::OnPlay()
{
	

	
}

void SphereColliderComponent::Serialize(YAML::Emitter & out)
{

	out << YAML::Anchor("component:" + to_string(m_ID));

	out << YAML::BeginMap;
	out << YAML::Key << "Type";
	out << YAML::Value << "SphereColliderComponent";
	SERIALIZE_VAR(m_IsTrigger,out);
	SERIALIZE_VAR(m_Radius,out);
	SERIALIZE_VAR(m_MaterialAssetID,out);
	SERIALIZE_VAR(m_EulerAngles,out);


	out << YAML::EndMap;
}

void SphereColliderComponent::ParseFromNode(YAML::Node & Info)
{
	PARSE_VAR(m_IsTrigger, Info);
	PARSE_VAR(m_Radius, Info);
	PARSE_VAR(m_MaterialAssetID, Info);
	PARSE_VAR(m_EulerAngles, Info);

}

void SphereColliderComponent::Update(const GameContext & context)
{
	UNREFERENCED_PARAMETER(context);
}

void SphereColliderComponent::Draw(const GameContext & context)
{
	UNREFERENCED_PARAMETER(context);
	if (!m_pEffect)
		return;
	auto trnsf = GetTransform();

	DirectX::XMFLOAT3 pos = trnsf->GetPosition();
	
	auto rot = DirectX::XMQuaternionRotationRollPitchYaw(
			DirectX::XMConvertToRadians(m_EulerAngles.x),
			DirectX::XMConvertToRadians(m_EulerAngles.y),
			DirectX::XMConvertToRadians(m_EulerAngles.z));
	auto scale = trnsf->GetScale();
	auto world = 
		DirectX::XMMatrixTranslation(-pos.x, -pos.y, -pos.z)*
		DirectX::XMMatrixScaling(scale.x, scale.y, scale.z)*
		DirectX::XMMatrixRotationQuaternion(rot) *
		DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&trnsf->GetRotation()))*
			DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);

	GameObject* pParent = m_pGameObject->GetParent();
	if (pParent)
	{
		const auto parentWorld = DirectX::XMLoadFloat4x4(&pParent->GetTransform()->GetWorld());
		world *= parentWorld ;

	}

	m_pEffect->SetWorld(world);
	auto projection = context.pCamera->GetProjection();
	m_pEffect->SetProjection(XMLoadFloat4x4(&projection));

	auto view = context.pCamera->GetView();
	m_pEffect->SetView(XMLoadFloat4x4(&view));
	m_pEffect->Apply(context.pDeviceContext);

	context.pDeviceContext->IASetInputLayout(m_InputLayout.Get());

	m_pBatch->Begin();

	BoundingSphere sphere{ GetTransform()->GetPosition(),m_Radius };
	DXDebugDraw::Draw(m_pBatch.get(), sphere, Colors::Blue); // BoundingSphere

	m_pBatch->End();

}

void SphereColliderComponent::Initialize(const GameContext & gameContext)
{
	
	auto pDevice = gameContext.pDevice;
	auto pDeviceContext = gameContext.pDeviceContext;
	m_pStates = std::make_unique<CommonStates>(pDevice);
	m_pBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(pDeviceContext);

	m_pEffect = std::make_unique<BasicEffect>(pDevice);
	m_pEffect->SetVertexColorEnabled(true);


	void const* shaderByteCode;
	size_t byteCodeLength;

	m_pEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	HRESULT hr =
		pDevice->CreateInputLayout(VertexPositionColor::InputElements,
			VertexPositionColor::InputElementCount,
			shaderByteCode, byteCodeLength,
			m_InputLayout.ReleaseAndGetAddressOf());
	if (FAILED(hr))
	{
		Logger::LogHResult(hr, L" At Initializing spherecollidercomp");
	}


	m_pBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(pDeviceContext);


}

void SphereColliderComponent::ParseMaterial()
{

	string file = AssetManager::GetInstance()->GetFile(m_MaterialAssetID)
		.absoluteFilePath().toStdString();

	auto physX = PhysxManager::GetInstance()->GetPhysics();
	m_pPhysxMaterial = physX->createMaterial(0, 0, 0);

	YAML::Node material = YAML::LoadFile(file);
	PARSE_VAR(*m_pPhysxMaterial, material);

}
