
#include "stdafx.h"

//#include "LiquidMaterial_Simulation_Boundary.h"
#include "LiquidMaterial_Simulation_Boundary.h"
#include "ContentManager.h"
#include "TextureData.h"

//old effect: ./Resources/Effects/Deferred/LiquidShaderSRVtoRT.fx

ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_Boundary::m_pDiffuseSRVvariable = nullptr;
ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_Boundary::m_pBoundarySRVvariable = nullptr;
ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_Boundary::m_pIsPressureSV = nullptr;

LiquidMaterial_Simulation_Boundary::LiquidMaterial_Simulation_Boundary() :
	Material(L"./Resources/Effects/Deferred/LiquidSimBoundary.fx")
{
}


LiquidMaterial_Simulation_Boundary::~LiquidMaterial_Simulation_Boundary()
{

}

/*
void LiquidMaterial_Simulation_Boundary::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}
*/
void LiquidMaterial_Simulation_Boundary::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}

void LiquidMaterial_Simulation_Boundary::UpdateVariables() 
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
	m_pBoundarySRVvariable->SetResource(m_pBoundarySRV);
	m_pIsPressureSV->SetFloat(m_pIsPressure); 
}

void LiquidMaterial_Simulation_Boundary::PublicLoadEffectVariables()
{
	LoadEffectVariables(); 
}


void LiquidMaterial_Simulation_Boundary::LoadEffectVariables()
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
	
	if (!m_pBoundarySRVvariable)
	{
		m_pBoundarySRVvariable = GetEffect()->GetVariableByName("gBoundaryMap")->AsShaderResource();
		if (!m_pBoundarySRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gBoundaryMap\' variable not found!");
			m_pBoundarySRVvariable = nullptr;
		}
	}


	m_pIsPressureSV = GetEffect()->GetVariableByName("gIsPressure")->AsScalar();


}

/*
void LiquidMaterial_Simulation_Boundary::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}
*/