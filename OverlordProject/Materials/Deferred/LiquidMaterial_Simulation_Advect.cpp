
#include "stdafx.h"

#include "LiquidMaterial_Simulation_Advect.h"

#include "ContentManager.h"
#include "TextureData.h"

//old effect: ./Resources/Effects/Deferred/LiquidShaderSRVtoRT.fx

ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_Advect::m_pDiffuseSRVvariable = nullptr;

ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_Advect::m_pAdvectionForceSRVvariable = nullptr;

ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_Advect::m_pAdvectedQuantitySRVvariable = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_Advect::m_pTimeStep = nullptr; 

LiquidMaterial_Simulation_Advect::LiquidMaterial_Simulation_Advect() :
	Material(L"./Resources/Effects/Deferred/LiquidSimAdvect.fx"),
	m_pDiffuseTexture(nullptr)
{
}


LiquidMaterial_Simulation_Advect::~LiquidMaterial_Simulation_Advect()
{

}

/*
void LiquidMaterial_Simulation_Advect::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}
*/
void LiquidMaterial_Simulation_Advect::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}

void LiquidMaterial_Simulation_Advect::UpdateVariables() 
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
	m_pAdvectionForceSRVvariable->SetResource(m_pAdvectionForceSRV);
	m_pAdvectedQuantitySRVvariable->SetResource(m_pAdvectedQuantitySRV);
	//m_pFloatTimeStep += 0.000001f;
	m_pTimeStep->SetFloat(m_pFloatTimeStep);
}

void LiquidMaterial_Simulation_Advect::PublicLoadEffectVariables()
{
	LoadEffectVariables(); 
}


void LiquidMaterial_Simulation_Advect::LoadEffectVariables()
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
	if (!m_pAdvectionForceSRVvariable)
	{
		m_pAdvectionForceSRVvariable = GetEffect()->GetVariableByName("gAdvectionForceMap")->AsShaderResource();
		if (!m_pAdvectionForceSRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gAdvectionForceMap\' variable not found!");
			m_pAdvectionForceSRVvariable = nullptr;
		}
	}
	if (!m_pAdvectedQuantitySRVvariable)
	{
		m_pAdvectedQuantitySRVvariable = GetEffect()->GetVariableByName("gAdvectedQuantityMap")->AsShaderResource();
		if (!m_pAdvectedQuantitySRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gAdvectedQuantityMap\' variable not found!");
			m_pAdvectedQuantitySRVvariable = nullptr;
		}
	}
	m_pTimeStep = GetEffect()->GetVariableByName("gTimeStep")->AsScalar(); 

}

/*
void LiquidMaterial_Simulation_Advect::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}
*/