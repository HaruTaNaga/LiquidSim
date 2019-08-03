
#include "stdafx.h"

#include "LiquidMaterial_Simulation_VelocityGradient.h"

#include "ContentManager.h"
#include "TextureData.h"




ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_VelocityGradient::m_pDiffuseSRVvariable = nullptr;

ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_VelocityGradient::m_pAdvectionSRVvariable = nullptr;
LiquidMaterial_Simulation_VelocityGradient::LiquidMaterial_Simulation_VelocityGradient() :
	Material(L"./Resources/Effects/Deferred/LiquidSimVelocityGradient.fx")
{
}


LiquidMaterial_Simulation_VelocityGradient::~LiquidMaterial_Simulation_VelocityGradient()
{

}



void LiquidMaterial_Simulation_VelocityGradient::LoadEffectVariables()
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
	if (!m_pAdvectionSRVvariable)
	{
		m_pAdvectionSRVvariable = GetEffect()->GetVariableByName("gAdvectionMap")->AsShaderResource();
		if (!m_pAdvectionSRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gAdvectionMap\' variable not found!");
			m_pAdvectionSRVvariable = nullptr;
		}
	}
}


void LiquidMaterial_Simulation_VelocityGradient::UpdateVariables() const
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
	m_pAdvectionSRVvariable->SetResource(m_pAdvectionSRV); 
}



void LiquidMaterial_Simulation_VelocityGradient::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);


}