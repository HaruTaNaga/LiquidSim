
#include "stdafx.h"

#include "LiquidMaterial_Deferred.h"

#include "ContentManager.h"
#include "TextureData.h"

ID3DX11EffectShaderResourceVariable* LiquidMaterial_Deferred::m_pDiffuseSRVvariable = nullptr;

LiquidMaterial_Deferred::LiquidMaterial_Deferred() :
	Material(L"./Resources/Effects/Deferred/LiquidSim.fx"),
	m_pDiffuseTexture(nullptr)
{
}


LiquidMaterial_Deferred::~LiquidMaterial_Deferred()
{

}

void LiquidMaterial_Deferred::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}

void LiquidMaterial_Deferred::LoadEffectVariables()
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

void LiquidMaterial_Deferred::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}