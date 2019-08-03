
#include "stdafx.h"

//#include "LiquidMaterial_Simulation_DrawMouseVel.h"
#include "LiquidMaterial_Simulation_DrawMouseVel.h"
#include "ContentManager.h"
#include "TextureData.h"

//old effect: ./Resources/Effects/Deferred/LiquidShaderSRVtoRT.fx

ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_DrawMouseVel::m_pDiffuseSRVvariable = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseVel::m_pXposSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseVel::m_pYposSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseVel::m_pXvelSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseVel::m_pYvelSRV = nullptr;


ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseVel::m_pSizeSRV = nullptr;

LiquidMaterial_Simulation_DrawMouseVel::LiquidMaterial_Simulation_DrawMouseVel() :
	Material(L"./Resources/Effects/Deferred/LiquidSimDrawMouseVelocitySeed.fx"),
	m_pDiffuseTexture(nullptr)
{
}


LiquidMaterial_Simulation_DrawMouseVel::~LiquidMaterial_Simulation_DrawMouseVel()
{

}

/*
void LiquidMaterial_Simulation_DrawMouseVel::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}
*/
void LiquidMaterial_Simulation_DrawMouseVel::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}

void LiquidMaterial_Simulation_DrawMouseVel::UpdateVariables() 
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
}
void LiquidMaterial_Simulation_DrawMouseVel::UpdateMousePosVariables(int x, int y, int xvel, int yvel, float size)
{

	m_pXposSRV->SetFloat((float)x);
	m_pYposSRV->SetFloat((float)y);
	m_pXvelSRV->SetFloat((float)xvel);
	m_pYvelSRV->SetFloat((float)yvel);
	m_pSizeSRV->SetFloat(size);

}
void LiquidMaterial_Simulation_DrawMouseVel::PublicLoadEffectVariables()
{
	LoadEffectVariables(); 
}


void LiquidMaterial_Simulation_DrawMouseVel::LoadEffectVariables()
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
	
	
	m_pXposSRV = GetEffect()->GetVariableByName("gXpos")->AsScalar();
	m_pYposSRV = GetEffect()->GetVariableByName("gYpos")->AsScalar();
	m_pXvelSRV = GetEffect()->GetVariableByName("gXvel")->AsScalar();
	m_pYvelSRV = GetEffect()->GetVariableByName("gYvel")->AsScalar();
	m_pSizeSRV = GetEffect()->GetVariableByName("gSize")->AsScalar();
}

/*
void LiquidMaterial_Simulation_DrawMouseVel::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}
*/