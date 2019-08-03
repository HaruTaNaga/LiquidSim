
#include "stdafx.h"

#include "LiquidMaterial_Simulation_Divergence.h"

#include "ContentManager.h"
#include "TextureData.h"

//old effect: ./Resources/Effects/Deferred/LiquidShaderSRVtoRT.fx



ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_Divergence::m_pAdvectionForceSRVvariable = nullptr;




LiquidMaterial_Simulation_Divergence::LiquidMaterial_Simulation_Divergence() :
	Material(L"./Resources/Effects/Deferred/LiquidSimDivergence.fx")
{
}


LiquidMaterial_Simulation_Divergence::~LiquidMaterial_Simulation_Divergence()
{

}

/*
void LiquidMaterial_Simulation_Divergence::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}
*/
void LiquidMaterial_Simulation_Divergence::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}

void LiquidMaterial_Simulation_Divergence::UpdateVariables() 
{
	
	m_pAdvectionForceSRVvariable->SetResource(m_pAdvectionForceSRV);

}

void LiquidMaterial_Simulation_Divergence::PublicLoadEffectVariables()
{
	LoadEffectVariables(); 
}


void LiquidMaterial_Simulation_Divergence::LoadEffectVariables()
{

	if (!m_pAdvectionForceSRVvariable)
	{
		m_pAdvectionForceSRVvariable = GetEffect()->GetVariableByName("gSourceMap")->AsShaderResource();
		if (!m_pAdvectionForceSRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gSourceMap\' variable not found!");
			m_pAdvectionForceSRVvariable = nullptr;
		}
	}
	
	

}

/*
void LiquidMaterial_Simulation_Divergence::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}
*/