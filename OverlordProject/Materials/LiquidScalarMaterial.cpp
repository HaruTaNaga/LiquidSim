#include "stdafx.h"
#include "LiquidScalarMaterial.h"

//Based Upon DeferredMaterial.cpp

ID3DX11EffectShaderResourceVariable* LiquidScalarMaterial::m_pDiffuseSRVvariable = nullptr;
ID3DX11EffectShaderResourceVariable* LiquidScalarMaterial::m_pNormalSRVvariable = nullptr;

ID3DX11EffectShaderResourceVariable* LiquidScalarMaterial::m_pVelocitySRVvariable = nullptr;
ID3DX11EffectShaderResourceVariable* LiquidScalarMaterial::m_pPressureSRVvariable = nullptr;

ID3DX11EffectShaderResourceVariable* LiquidScalarMaterial::m_pColorSRVvariable = nullptr;
ID3DX11EffectShaderResourceVariable* LiquidScalarMaterial::m_pVelocity2SRVvariable = nullptr;
ID3DX11EffectShaderResourceVariable* LiquidScalarMaterial::m_pPressure2SRVvariable = nullptr;
ID3DX11EffectShaderResourceVariable* LiquidScalarMaterial::m_pColor2SRVvariable = nullptr;

LiquidScalarMaterial::LiquidScalarMaterial() :
	Material(L"./Resources/Effects/Deferred/LiquidRendererScalar.fx")
{
}

void LiquidScalarMaterial::LoadEffectVariables()
{
	if (!m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable = GetEffect()->GetVariableByName("gTextureDiffuse")->AsShaderResource();
		if (!m_pDiffuseSRVvariable->IsValid())
		{
			Logger::LogWarning(L"LiquidScalarMaterial::LoadEffectVariables() > \'gTextureDiffuse\' variable not found!");
			m_pDiffuseSRVvariable = nullptr;
		}
	}
	
	if (!m_pNormalSRVvariable)
	{
		m_pNormalSRVvariable = GetEffect()->GetVariableByName("gTextureNormal")->AsShaderResource();
		if (!m_pNormalSRVvariable->IsValid())
		{
			Logger::LogWarning(L"LiquidScalarMaterial::LoadEffectVariables() > \'gTextureNormal\' variable not found!");
			m_pNormalSRVvariable = nullptr;
		}
	}

	if (!m_pVelocitySRVvariable)
	{
		m_pVelocitySRVvariable = GetEffect()->GetVariableByName("gTextureVelocity")->AsShaderResource();
		if (!m_pVelocitySRVvariable->IsValid())
		{
			Logger::LogWarning(L"LiquidScalarMaterial::LoadEffectVariables() > \'gTextureVelocity\' variable not found!");
			m_pVelocitySRVvariable = nullptr;
		}
	}

	if (!m_pPressureSRVvariable)
	{
		m_pPressureSRVvariable = GetEffect()->GetVariableByName("gTexturePressure")->AsShaderResource();
		if (!m_pPressureSRVvariable->IsValid())
		{
			Logger::LogWarning(L"LiquidScalarMaterial::LoadEffectVariables() > \'gTexturePressure\' variable not found!");
			m_pPressureSRVvariable = nullptr;
		}
	}
	
	if (!m_pColorSRVvariable)
	{
		m_pColorSRVvariable = GetEffect()->GetVariableByName("gTextureColor")->AsShaderResource();
		if (!m_pColorSRVvariable->IsValid())
		{
			Logger::LogWarning(L"LiquidScalarMaterial::LoadEffectVariables() > \'gTextureColor\' variable not found!");
			m_pColorSRVvariable = nullptr;
		}
	}
	if (!m_pVelocity2SRVvariable)
	{
		m_pVelocity2SRVvariable = GetEffect()->GetVariableByName("gTextureVelocity2")->AsShaderResource();
		if (!m_pVelocity2SRVvariable->IsValid())
		{
			Logger::LogWarning(L"LiquidScalarMaterial::LoadEffectVariables() > \'gTextureVelocity2\' variable not found!");
			m_pVelocity2SRVvariable = nullptr;
		}
	}

	if (!m_pPressure2SRVvariable)
	{
		m_pPressure2SRVvariable = GetEffect()->GetVariableByName("gTexturePressure2")->AsShaderResource();
		if (!m_pPressure2SRVvariable->IsValid())
		{
			Logger::LogWarning(L"LiquidScalarMaterial::LoadEffectVariables() > \'gTextureVelocity2\' variable not found!");
			m_pPressureSRVvariable = nullptr;
		}
	}
	if (!m_pColor2SRVvariable)
	{
		m_pColor2SRVvariable = GetEffect()->GetVariableByName("gTextureColor2")->AsShaderResource();
		if (!m_pColor2SRVvariable->IsValid())
		{
			Logger::LogWarning(L"LiquidScalarMaterial::LoadEffectVariables() > \'gTextureColor2\' variable not found!");
			m_pColor2SRVvariable = nullptr;
		}
	}
	//*/
}

void LiquidScalarMaterial::UpdateEffectVariables(const GameContext&, ModelComponent*)
{
}

void LiquidScalarMaterial::UpdateVariables() const
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
	m_pNormalSRVvariable->SetResource(m_pNormalSRV);
	m_pVelocitySRVvariable->SetResource(m_pVelocitySRV);
	
	
	m_pPressureSRVvariable->SetResource(m_pPressureSRV);
	m_pColorSRVvariable->SetResource(m_pColorSRV);
	m_pVelocity2SRVvariable->SetResource(m_pVelocity2SRV);
	m_pPressure2SRVvariable->SetResource(m_pPressure2SRV);
	m_pColor2SRVvariable->SetResource(m_pColor2SRV);
    
}
