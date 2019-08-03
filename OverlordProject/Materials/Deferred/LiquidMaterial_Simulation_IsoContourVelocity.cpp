
#include "stdafx.h"

#include "LiquidMaterial_Simulation_IsoContourVelocity.h"

#include "ContentManager.h"
#include "TextureData.h"




ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_IsoContourVelocity::m_pDiffuseSRVvariable = nullptr;


LiquidMaterial_Simulation_IsoContourVelocity::LiquidMaterial_Simulation_IsoContourVelocity() :
	Material(L"./Resources/Effects/Deferred/LiquidSimIsoContourVelocity.fx")
{
}


LiquidMaterial_Simulation_IsoContourVelocity::~LiquidMaterial_Simulation_IsoContourVelocity()
{

}



void LiquidMaterial_Simulation_IsoContourVelocity::LoadEffectVariables()
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


void LiquidMaterial_Simulation_IsoContourVelocity::UpdateVariables() const
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
}



void LiquidMaterial_Simulation_IsoContourVelocity::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);


}