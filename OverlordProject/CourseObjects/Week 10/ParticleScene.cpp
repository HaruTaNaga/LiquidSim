
#include "stdafx.h"

#include "ParticleScene.h"
#include "GameObject.h"

#include "ModelAnimator.h"
#include "TransformComponent.h"
#include "ParticleEmitterComponent.h"
#include "ModelComponent.h"
#include "../../Materials/LiquidMaterial.h"
#include "../../Materials/SkinnedDiffuseMaterial.h"
#include "..\..\Materials\Deferred/LiquidMaterial_Simulation.h"
#include "SpriteComponent.h"
#include "SpriteRenderer.h"
ParticleScene::ParticleScene(void) :
	GameScene(L"ParticleScene"),
	m_pParticleEmitter(nullptr),
	m_pModel(nullptr)
{
}


ParticleScene::~ParticleScene(void)
{
}

void ParticleScene::Initialize()
{
	const auto gameContext = GetGameContext();
	UNREFERENCED_PARAMETER(gameContext);

	//gameContext.pInput->ForceMouseToCenter(true);
	gameContext.pGameTime->ForceElapsedUpperbound(true);

	

	auto mat = new SkinnedDiffuseMaterial;
	mat->SetDiffuseTexture(L"./Resources/Textures/Knight.jpg");
	auto diffusemat = new LiquidMaterial_Simulation();
	diffusemat->SetDiffuseTexture(L"./Resources/Textures/Knight.jpg");
	gameContext.pMaterialManager->AddMaterial(mat, diffusemat, 0);

	auto obj2 = new GameObject();
	m_pModel = new ModelComponent(L"./Resources/Meshes/Knight.ovm");
	m_pModel->SetMaterial(0);
	obj2->AddComponent(m_pModel);
	AddChild(obj2);
	m_pModel->GetAnimator()->Play();
	obj2->GetTransform()->Scale(.35f, .35f, .35f);
	obj2->GetTransform()->Translate(0.f,-60.f,30.f);

	auto DiffuseColorSeed = new GameObject();
	DiffuseColorSeed->AddComponent(new SpriteComponent(L"./Resources/Textures/fractal.jpg", DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1.0f)));
	AddChild(DiffuseColorSeed);
	DiffuseColorSeed->GetTransform()->Translate(0.f, 0.f, 1.f);
	DiffuseColorSeed->GetTransform()->Scale(DirectX::XMFLOAT3(0.8f,1.f, 1));
	gameContext.pInput->AddInputAction(InputAction(0, Down, VK_RIGHT));
	gameContext.pInput->AddInputAction(InputAction(1, Down, VK_LEFT));
	gameContext.pInput->AddInputAction(InputAction(2, Down, VK_UP));
	gameContext.pInput->AddInputAction(InputAction(3, Down, VK_DOWN));
	
}

void ParticleScene::Update()
{
	const auto gameContext = GetGameContext();
	UNREFERENCED_PARAMETER(gameContext);
	
	
}

void ParticleScene::Draw()
{
	const auto gameContext = GetGameContext();
	UNREFERENCED_PARAMETER(gameContext);
}
