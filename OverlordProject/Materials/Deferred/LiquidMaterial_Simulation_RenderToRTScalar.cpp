
#include "stdafx.h"

#include "LiquidMaterial_Simulation_RenderToRTScalar.h"

#include "ContentManager.h"
#include "TextureData.h"



ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_TexToRTScalar::m_pDiffuseSRVvariable = nullptr;

LiquidMaterial_Simulation_TexToRTScalar::LiquidMaterial_Simulation_TexToRTScalar() :
	Material(L"./Resources/Effects/Deferred/LiquidShaderSRVtoRTScalar.fx"),
	m_pDiffuseTexture(nullptr)
{
}


LiquidMaterial_Simulation_TexToRTScalar::~LiquidMaterial_Simulation_TexToRTScalar()
{

}

/*
void LiquidMaterial_Simulation_TexToRTScalar::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}
*/
void LiquidMaterial_Simulation_TexToRTScalar::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}

void LiquidMaterial_Simulation_TexToRTScalar::UpdateVariables() 
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
}
void LiquidMaterial_Simulation_TexToRTScalar::LoadEffectVariables()
{
	if (!m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable = GetEffect()->GetVariableByName("gTextureDiffuse")->AsShaderResource();
		if (!m_pDiffuseSRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gTextureDiffuse\' variable not found!");
			m_pDiffuseSRVvariable = nullptr;
		}
	}
}

/*
void LiquidMaterial_Simulation_TexToRTScalar::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}
*/