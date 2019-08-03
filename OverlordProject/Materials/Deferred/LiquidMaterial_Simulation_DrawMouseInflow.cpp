
#include "stdafx.h"

//#include "LiquidMaterial_Simulation_DrawMouseInflow.h"
#include "LiquidMaterial_Simulation_DrawMouseInflow.h"
#include "ContentManager.h"
#include "TextureData.h"

//old effect: ./Resources/Effects/Deferred/LiquidShaderSRVtoRT.fx

ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_DrawMouseInflow::m_pDiffuseSRVvariable = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseInflow::m_pXposSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseInflow::m_pYposSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseInflow::m_pXvelSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseInflow::m_pYvelSRV = nullptr;


ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseInflow::m_pSizeSRV = nullptr;
ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseInflow::m_pColorSRV = nullptr;

LiquidMaterial_Simulation_DrawMouseInflow::LiquidMaterial_Simulation_DrawMouseInflow() :
	Material(L"./Resources/Effects/Deferred/LiquidSimDrawInflowSeed.fx"),
	m_pDiffuseTexture(nullptr)
{
}


LiquidMaterial_Simulation_DrawMouseInflow::~LiquidMaterial_Simulation_DrawMouseInflow()
{

}

/*
void LiquidMaterial_Simulation_DrawMouseInflow::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}
*/
void LiquidMaterial_Simulation_DrawMouseInflow::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}

void LiquidMaterial_Simulation_DrawMouseInflow::UpdateVariables() 
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
}
void LiquidMaterial_Simulation_DrawMouseInflow::UpdateMousePosVariables(int x, int y, float xvel, float yvel,float color[3], float size )
{
	m_pColorSRV->SetFloatArray(color,sizeof(float),3);
	m_pXposSRV->SetFloat((float)x);
	m_pYposSRV->SetFloat((float)y);
	m_pXvelSRV->SetFloat((float)xvel);
	m_pYvelSRV->SetFloat((float)yvel);
	m_pSizeSRV->SetFloat(size);


}
void LiquidMaterial_Simulation_DrawMouseInflow::PublicLoadEffectVariables()
{
	LoadEffectVariables(); 
}


void LiquidMaterial_Simulation_DrawMouseInflow::LoadEffectVariables()
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
	
	m_pColorSRV = GetEffect()->GetVariableByName("gColor")->AsScalar();
	m_pXposSRV = GetEffect()->GetVariableByName("gXpos")->AsScalar();
	m_pYposSRV = GetEffect()->GetVariableByName("gYpos")->AsScalar();
	m_pXvelSRV = GetEffect()->GetVariableByName("gXvel")->AsScalar();
	m_pYvelSRV = GetEffect()->GetVariableByName("gYvel")->AsScalar();
	m_pSizeSRV = GetEffect()->GetVariableByName("gSize")->AsScalar();
}

/*
void LiquidMaterial_Simulation_DrawMouseInflow::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}
*/