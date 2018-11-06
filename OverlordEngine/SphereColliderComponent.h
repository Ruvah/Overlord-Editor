#pragma once
#include <BaseComponent.h>
#include <PrimitiveBatch.h>
#include <memory>
#include <VertexTypes.h>
#include <CommonStates.h>
#include <Effects.h>
#include <wrl/client.h>
class ColliderComponent;
class SphereColliderComponent: public BaseComponent
{
public:
	SphereColliderComponent(const SphereColliderComponent& other) = delete;
	SphereColliderComponent(SphereColliderComponent&& other) noexcept = delete;
	SphereColliderComponent& operator=(const SphereColliderComponent& other) = delete;
	SphereColliderComponent& operator=(SphereColliderComponent&& other) noexcept = delete;
	SphereColliderComponent();
	virtual ~SphereColliderComponent() = default;

	float GetRadius() { return m_Radius; };
	bool IsTrigger() { return m_IsTrigger; };

	physx::PxVec3 GetRotation(){ return m_EulerAngles; };
	physx::PxMaterial* GetMaterial() { return m_pPhysxMaterial; }

	void SetRadius(float radius);
	void SetAngles(physx::PxVec3 axis);
	void SetTrigger(bool isTrigger);
	void SetMaterialAssID(int id);

	int GetMaterialAssetId()const { return m_MaterialAssetID; }

	void ConvertToLowLvl();

	virtual void OnPlay();

	virtual void Serialize(YAML::Emitter & out)override;
	virtual void ParseFromNode(YAML::Node& Info) override;
	
protected:

	void Update(const GameContext& context) override;
	void Draw(const GameContext& context) override;
	void Initialize(const GameContext& gameContext) override;

private:
	ColliderComponent* m_pColliderComponent;

	float m_Radius;
	int m_MaterialAssetID;
	physx::PxMaterial* m_pPhysxMaterial;
	physx::PxVec3 m_EulerAngles;
	bool m_IsTrigger, m_DidConvert;

	unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_pBatch;
	unique_ptr<DirectX::CommonStates> m_pStates;
	unique_ptr<DirectX::BasicEffect> m_pEffect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;



	void ParseMaterial();
};

