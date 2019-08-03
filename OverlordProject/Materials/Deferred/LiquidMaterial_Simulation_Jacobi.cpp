
#include "stdafx.h"

#include "LiquidMaterial_Simulation_Jacobi.h"

#include "ContentManager.h"
#include "TextureData.h"

//old effect: ./Resources/Effects/Deferred/LiquidShaderSRVtoRT.fx


ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_Jacobi::m_pXvec_SRVvariable = nullptr;

ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_Jacobi::m_pBvec_SRVvariable = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_Jacobi::m_pTimeStep = nullptr; 
ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_Jacobi::m_pAlphaSRV = nullptr;
ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_Jacobi::m_pBetaSRV = nullptr;

LiquidMaterial_Simulation_Jacobi::LiquidMaterial_Simulation_Jacobi() :
	Material(L"./Resources/Effects/Deferred/LiquidSimJacobi.fx"),
	m_pDiffuseTexture(nullptr)
{
}


LiquidMaterial_Simulation_Jacobi::~LiquidMaterial_Simulation_Jacobi()
{

}

/*
void LiquidMaterial_Simulation_Jacobi::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}
*/
void LiquidMaterial_Simulation_Jacobi::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}

void LiquidMaterial_Simulation_Jacobi::UpdateVariables() 
{
	
	m_pXvec_SRVvariable->SetResource(m_pXvec_SRV);
	m_pBvec_SRVvariable->SetResource(m_pBvec_SRV);
	m_pAlphaSRV->SetFloat(m_pAlpha); 
	m_pBetaSRV->SetFloat(m_pBeta);
	//m_pFloatTimeStep += 0.000001f;
	//m_pTimeStep->SetFloat(m_pFloatTimeStep);
}

void LiquidMaterial_Simulation_Jacobi::PublicLoadEffectVariables()
{
	LoadEffectVariables(); 
}


void LiquidMaterial_Simulation_Jacobi::LoadEffectVariables()
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
	if (!m_pXvec_SRVvariable)
	{
		m_pXvec_SRVvariable = GetEffect()->GetVariableByName("gVariableMap")->AsShaderResource();
		if (!m_pXvec_SRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gVariableMap\' variable not found!");
			m_pXvec_SRVvariable = nullptr;
		}
	}
	if (!m_pBvec_SRVvariable)
	{
		m_pBvec_SRVvariable = GetEffect()->GetVariableByName("gConstantMap")->AsShaderResource();
		if (!m_pBvec_SRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gConstantMap\' variable not found!");
			m_pBvec_SRVvariable = nullptr;
		}
	}
	m_pAlphaSRV = GetEffect()->GetVariableByName("gAlpha")->AsScalar();
	m_pBetaSRV = GetEffect()->GetVariableByName("gBeta")->AsScalar();

}

/*
void LiquidMaterial_Simulation_Jacobi::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}
*/