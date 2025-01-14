
#include "stdafx.h"

#include "SpikeyScene.h"
#include "GameObject.h"



#include "Prefabs.h"
#include "Components.h"
#include "PhysxProxy.h"
#include "PhysxManager.h"
#include "ContentManager.h"
#include "MeshFilter.h"
#include "../../Materials/SpikeyMaterial.h"
#include "ModelComponent.h"

#include "..\..\Materials\DiffuseMaterial.h"
#include "..\..\Materials\Deferred/DiffuseMaterial_Deferred.h"
#define FPS_COUNTER 1

SpikeyScene::SpikeyScene(void):
	GameScene(L"SpikeyScene"),
	m_FpsInterval(FPS_COUNTER)
{
}


SpikeyScene::~SpikeyScene(void)
{
}

void SpikeyScene::Initialize()
{
	
	const auto gameContext = GetGameContext();
	GetPhysxProxy()->EnablePhysxDebugRendering(true);
	gameContext.pGameTime->ForceElapsedUpperbound(true);

	// Create PhysX ground plane
	auto physX = PhysxManager::GetInstance()->GetPhysics();
	
	auto bouncyMaterial = physX->createMaterial(0, 0, 1);
	auto ground = new GameObject();
	ground->AddComponent(new RigidBodyComponent(true));
	
	std::shared_ptr<physx::PxGeometry> geom(new physx::PxPlaneGeometry());
	ground->AddComponent(new ColliderComponent(geom,*bouncyMaterial, physx::PxTransform(physx::PxQuat(DirectX::XM_PIDIV2, physx::PxVec3(0,0,1)))));
	AddChild(ground);


	//Material Test
	auto myMaterial = new SpikeyMaterial();
	myMaterial->SetDiffuseTexture(L"./Resources/Textures/Chair_Dark.dds");
	auto myMaterial_Deferred = new DiffuseMaterial_Deferred();
	gameContext.pMaterialManager->AddMaterial(myMaterial, myMaterial_Deferred, 60);
	
	auto model = new ModelComponent(L"./Resources/Meshes/Teapot.ovm");
	model->SetMaterial(60);

	auto teapot = new GameObject();
	teapot->AddComponent(model);
	AddChild(teapot);
	teapot->GetTransform()->Translate(0,0,20);
}

void SpikeyScene::Update()
{
	const auto gameContext = GetGameContext();
	m_FpsInterval += gameContext.pGameTime->GetElapsed();
	if (m_FpsInterval >= FPS_COUNTER)
	{
		m_FpsInterval -= FPS_COUNTER;
		Logger::LogFormat(LogLevel::Info, L"FPS: %i", gameContext.pGameTime->GetFPS());
	}
}

void SpikeyScene::Draw()
{
	const auto gameContext = GetGameContext();
	UNREFERENCED_PARAMETER(gameContext);
}
