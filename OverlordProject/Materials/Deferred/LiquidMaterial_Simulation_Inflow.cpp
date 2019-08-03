
#include "stdafx.h"

//#include "LiquidMaterial_Simulation_Inflow.h"
#include "LiquidMaterial_Simulation_Inflow.h"
#include "ContentManager.h"
#include "TextureData.h"

//old effect: ./Resources/Effects/Deferred/LiquidShaderSRVtoRT.fx


ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_Inflow::m_pSourceSRVvariable = nullptr;
ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_Inflow::m_pIsPressureSV = nullptr;

LiquidMaterial_Simulation_Inflow::LiquidMaterial_Simulation_Inflow() :
	Material(L"./Resources/Effects/Deferred/LiquidSimInflow.fx")
{
}


LiquidMaterial_Simulation_Inflow::~LiquidMaterial_Simulation_Inflow()
{

}

/*
void LiquidMaterial_Simulation_Inflow::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}
*/
void LiquidMaterial_Simulation_Inflow::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}

void LiquidMaterial_Simulation_Inflow::UpdateVariables() 
{

	m_pSourceSRVvariable->SetResource(m_pSourceSRV);
	m_pIsPressureSV->SetFloat(m_pIsPressure); 
}

void LiquidMaterial_Simulation_Inflow::PublicLoadEffectVariables()
{
	LoadEffectVariables(); 
}


void LiquidMaterial_Simulation_Inflow::LoadEffectVariables()
{
	
	if (!m_pSourceSRVvariable)
	{
		m_pSourceSRVvariable = GetEffect()->GetVariableByName("gSourceMap")->AsShaderResource();
		if (!m_pSourceSRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gSourceMap\' variable not found!");
			m_pSourceSRVvariable = nullptr;
		}
	}


	m_pIsPressureSV = GetEffect()->GetVariableByName("gIsPressure")->AsScalar();


}

/*
void LiquidMaterial_Simulation_Inflow::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}
*/