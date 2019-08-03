
#include "stdafx.h"

#include "LiquidMaterial_Simulation_IsoLineVelocity.h"

#include "ContentManager.h"
#include "TextureData.h"




ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_IsoLineVelocity::m_pDiffuseSRVvariable = nullptr;


LiquidMaterial_Simulation_IsoLineVelocity::LiquidMaterial_Simulation_IsoLineVelocity() :
	Material(L"./Resources/Effects/Deferred/LiquidSimIsoLineVelocity.fx")
{
}


LiquidMaterial_Simulation_IsoLineVelocity::~LiquidMaterial_Simulation_IsoLineVelocity()
{

}



void LiquidMaterial_Simulation_IsoLineVelocity::LoadEffectVariables()
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


void LiquidMaterial_Simulation_IsoLineVelocity::UpdateVariables() const
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
}



void LiquidMaterial_Simulation_IsoLineVelocity::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);


}