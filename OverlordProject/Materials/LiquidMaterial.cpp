#include "stdafx.h"
#include "LiquidMaterial.h"

//Based Upon DeferredMaterial.cpp

ID3DX11EffectShaderResourceVariable* LiquidMaterial::m_pDiffuseSRVvariable = nullptr;
ID3DX11EffectShaderResourceVariable* LiquidMaterial::m_pNormalSRVvariable = nullptr;

ID3DX11EffectShaderResourceVariable* LiquidMaterial::m_pVelocitySRVvariable = nullptr;
ID3DX11EffectShaderResourceVariable* LiquidMaterial::m_pPressureSRVvariable = nullptr;

ID3DX11EffectShaderResourceVariable* LiquidMaterial::m_pColorSRVvariable = nullptr;
ID3DX11EffectShaderResourceVariable* LiquidMaterial::m_pVelocity2SRVvariable = nullptr;
ID3DX11EffectShaderResourceVariable* LiquidMaterial::m_pPressure2SRVvariable = nullptr;
ID3DX11EffectShaderResourceVariable* LiquidMaterial::m_pColor2SRVvariable = nullptr;

LiquidMaterial::LiquidMaterial() :
	Material(L"./Resources/Effects/Deferred/LiquidRenderer.fx")
{
}

void LiquidMaterial::LoadEffectVariables()
{
	if (!m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable = GetEffect()->GetVariableByName("gTextureDiffuse")->AsShaderResource();
		if (!m_pDiffuseSRVvariable->IsValid())
		{
			Logger::LogWarning(L"LiquidMaterial::LoadEffectVariables() > \'gTextureDiffuse\' variable not found!");
			m_pDiffuseSRVvariable = nullptr;
		}
	}
	
	
	//*/
}

void LiquidMaterial::UpdateEffectVariables(const GameContext&, ModelComponent*)
{
}

void LiquidMaterial::UpdateVariables() const
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
	
    
}
