
#include "stdafx.h"

#include "LiquidMaterial_Simulation.h"

#include "ContentManager.h"
#include "TextureData.h"



ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation::m_pDiffuseSRVvariable = nullptr;

LiquidMaterial_Simulation::LiquidMaterial_Simulation() :
	Material(L"./Resources/Effects/Deferred/LiquidSim.fx"),
	m_pDiffuseTexture(nullptr)
{
}


LiquidMaterial_Simulation::~LiquidMaterial_Simulation()
{

}

void LiquidMaterial_Simulation::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}

void LiquidMaterial_Simulation::LoadEffectVariables()
{
	if (!m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable = GetEffect()->GetVariableByName("gDiffuseMap")->AsShaderResource();
		if (!m_pDiffuseSRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gDiffuseMap\' variable not found!");
			m_pDiffuseSRVvariable = nullptr;
		}
	}
}

void LiquidMaterial_Simulation::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}