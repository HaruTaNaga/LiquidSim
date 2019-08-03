
#include "stdafx.h"

#include "LiquidMaterial_Simulation_Projection.h"

#include "ContentManager.h"
#include "TextureData.h"

//old effect: ./Resources/Effects/Deferred/LiquidShaderSRVtoRT.fx


ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_Projection::m_pVelocityMap_SRVvariable = nullptr;

ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_Projection::m_pPressureMap_SRVvariable = nullptr;



LiquidMaterial_Simulation_Projection::LiquidMaterial_Simulation_Projection() :
	Material(L"./Resources/Effects/Deferred/LiquidSimProjection.fx")

{
}


LiquidMaterial_Simulation_Projection::~LiquidMaterial_Simulation_Projection()
{

}

/*
void LiquidMaterial_Simulation_Projection::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}
*/
void LiquidMaterial_Simulation_Projection::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}

void LiquidMaterial_Simulation_Projection::UpdateVariables() 
{
	
	m_pVelocityMap_SRVvariable->SetResource(m_pVelocityMap_SRV);
	m_pPressureMap_SRVvariable->SetResource(m_pPressureMap_SRV);

	//m_pFloatTimeStep += 0.000001f;
	//m_pTimeStep->SetFloat(m_pFloatTimeStep);
}

void LiquidMaterial_Simulation_Projection::PublicLoadEffectVariables()
{
	LoadEffectVariables(); 
}


void LiquidMaterial_Simulation_Projection::LoadEffectVariables()
{
	/*if (!m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable = GetEffect()->GetVariableByName("gDiffuseMap")->AsShaderResource();
		if (!m_pDiffuseSRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gDiffuseMap\' variable not found!");
			m_pDiffuseSRVvariable = nullptr;
		}
	}*/
	if (!m_pVelocityMap_SRVvariable)
	{
		m_pVelocityMap_SRVvariable = GetEffect()->GetVariableByName("gVelocityMap")->AsShaderResource();
		if (!m_pVelocityMap_SRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gVelocityMap\' variable not found!");
			m_pVelocityMap_SRVvariable = nullptr;
		}
	}
	if (!m_pPressureMap_SRVvariable)
	{
		m_pPressureMap_SRVvariable = GetEffect()->GetVariableByName("gPressureMap")->AsShaderResource();
		if (!m_pPressureMap_SRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gPressureMap\' variable not found!");
			m_pPressureMap_SRVvariable = nullptr;
		}
	}


}

/*
void LiquidMaterial_Simulation_Projection::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}
*/