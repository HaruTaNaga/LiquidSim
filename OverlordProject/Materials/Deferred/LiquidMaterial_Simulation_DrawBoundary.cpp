
#include "stdafx.h"

//#include "LiquidMaterial_Simulation_DrawBoundary.h"
#include "LiquidMaterial_Simulation_DrawBoundary.h"
#include "ContentManager.h"
#include "TextureData.h"

//old effect: ./Resources/Effects/Deferred/LiquidShaderSRVtoRT.fx

ID3DX11EffectVectorVariable* LiquidMaterial_Simulation_DrawBoundary::m_pColorSRVvariable = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawBoundary::m_pXminSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawBoundary::m_pYminSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawBoundary::m_pXmaxSRV = nullptr;

ID3DX11EffectScalarVariable* LiquidMaterial_Simulation_DrawBoundary::m_pYmaxSRV = nullptr;

LiquidMaterial_Simulation_DrawBoundary::LiquidMaterial_Simulation_DrawBoundary() :
	Material(L"./Resources/Effects/Deferred/LiquidSimDrawBoundary.fx")
{
}


LiquidMaterial_Simulation_DrawBoundary::~LiquidMaterial_Simulation_DrawBoundary()
{

}


void LiquidMaterial_Simulation_DrawBoundary::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}

void LiquidMaterial_Simulation_DrawBoundary::UpdateVariables() 
{
	
}
void LiquidMaterial_Simulation_DrawBoundary::SetBoundaryPositionVariables(int xmin, int ymin, int xmax, int ymax, float color[4])
{
	m_pColorSRVvariable->SetFloatVector(color); 

	m_pXminSRV->SetInt(xmin);
	m_pYminSRV->SetInt(ymin);
	m_pXmaxSRV->SetInt(xmax);
	m_pYmaxSRV->SetInt(ymax);

}
void LiquidMaterial_Simulation_DrawBoundary::PublicLoadEffectVariables()
{
	LoadEffectVariables(); 
}


void LiquidMaterial_Simulation_DrawBoundary::LoadEffectVariables()
{

	
	m_pColorSRVvariable = GetEffect()->GetVariableByName("gColor")->AsVector(); 
	m_pXminSRV = GetEffect()->GetVariableByName("gXmin")->AsScalar();
	m_pYminSRV = GetEffect()->GetVariableByName("gYmin")->AsScalar();
	m_pXmaxSRV = GetEffect()->GetVariableByName("gXmax")->AsScalar();
	m_pYmaxSRV = GetEffect()->GetVariableByName("gYmax")->AsScalar();
	

}

