
#include "stdafx.h"

//#include "LiquidMaterial_Simulation_DrawMouseColorInflow.h"
#include "LiquidMaterial_Simulation_DrawMouseColorInflow.h"
#include "ContentManager.h"
#include "TextureData.h"

//old effect: ./Resources/Effects/Deferred/LiquidShaderSRVtoRT.fx

ID3DX11EffectShaderResourceVariable* LiquidMaterial_Simulation_DrawMouseColorInflow::m_pDiffuseSRVvariable = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseColorInflow::m_pXposSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseColorInflow::m_pYposSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseColorInflow::m_pXvelSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseColorInflow::m_pYvelSRV = nullptr;


ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawMouseColorInflow::m_pSizeSRV = nullptr;
ID3DX11EffectVectorVariable* LiquidMaterial_Simulation_DrawMouseColorInflow::m_pColorSRV = nullptr;

LiquidMaterial_Simulation_DrawMouseColorInflow::LiquidMaterial_Simulation_DrawMouseColorInflow() :
	Material(L"./Resources/Effects/Deferred/LiquidSimDrawInflowColorSeed.fx"),
	m_pDiffuseTexture(nullptr)
{
}


LiquidMaterial_Simulation_DrawMouseColorInflow::~LiquidMaterial_Simulation_DrawMouseColorInflow()
{

}

/*
void LiquidMaterial_Simulation_DrawMouseColorInflow::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}
*/
void LiquidMaterial_Simulation_DrawMouseColorInflow::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}

void LiquidMaterial_Simulation_DrawMouseColorInflow::UpdateVariables() 
{
	m_pDiffuseSRVvariable->SetResource(m_pDiffuseSRV);
}
void LiquidMaterial_Simulation_DrawMouseColorInflow::UpdateMousePosVariables(int x, int y, float xvel, float yvel,float color[3], float size )
{
	m_pColorSRV->SetFloatVector(color); 
	m_pXposSRV->SetFloat((float)x);
	m_pYposSRV->SetFloat((float)y);
	m_pXvelSRV->SetFloat((float)xvel);
	m_pYvelSRV->SetFloat((float)yvel);
	m_pSizeSRV->SetFloat(size);


}
void LiquidMaterial_Simulation_DrawMouseColorInflow::PublicLoadEffectVariables()
{
	LoadEffectVariables(); 
}


void LiquidMaterial_Simulation_DrawMouseColorInflow::LoadEffectVariables()
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
	
	m_pColorSRV = GetEffect()->GetVariableByName("gColor")->AsVector();
	m_pXposSRV = GetEffect()->GetVariableByName("gXpos")->AsScalar();
	m_pYposSRV = GetEffect()->GetVariableByName("gYpos")->AsScalar();
	m_pXvelSRV = GetEffect()->GetVariableByName("gXvel")->AsScalar();
	m_pYvelSRV = GetEffect()->GetVariableByName("gYvel")->AsScalar();
	m_pSizeSRV = GetEffect()->GetVariableByName("gSize")->AsScalar();
}

/*
void LiquidMaterial_Simulation_DrawMouseColorInflow::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}
*/