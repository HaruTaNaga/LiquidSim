
#include "stdafx.h"

#include "LiquidMaterial_Simulation_IsoLineScalar.h"

#include "ContentManager.h"
#include "TextureData.h"




ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_IsoLineScalar::m_pDiffuseSRVvariable = nullptr;


LiquidMaterial_Simulation_IsoLineScalar::LiquidMaterial_Simulation_IsoLineScalar() :
	Material(L"./Resources/Effects/Deferred/LiquidSimIsoLineScalar.fx")
{
}


LiquidMaterial_Simulation_IsoLineScalar::~LiquidMaterial_Simulation_IsoLineScalar()
{

}



void LiquidMaterial_Simulation_IsoLineScalar::LoadEffectVariables()
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


void LiquidMaterial_Simulation_IsoLineScalar::UpdateVariables() const
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
}



void LiquidMaterial_Simulation_IsoLineScalar::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);


}