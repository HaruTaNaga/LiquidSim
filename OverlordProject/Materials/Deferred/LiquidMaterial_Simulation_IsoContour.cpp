
#include "stdafx.h"

#include "LiquidMaterial_Simulation_IsoContour.h"

#include "ContentManager.h"
#include "TextureData.h"




ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_IsoContour::m_pDiffuseSRVvariable = nullptr;


LiquidMaterial_Simulation_IsoContour::LiquidMaterial_Simulation_IsoContour() :
	Material(L"./Resources/Effects/Deferred/LiquidSimIsoContour.fx")
{
}


LiquidMaterial_Simulation_IsoContour::~LiquidMaterial_Simulation_IsoContour()
{

}



void LiquidMaterial_Simulation_IsoContour::LoadEffectVariables()
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


void LiquidMaterial_Simulation_IsoContour::UpdateVariables() const
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
}



void LiquidMaterial_Simulation_IsoContour::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);


}