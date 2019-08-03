#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_DrawBoundary : public Material
{
public:
	LiquidMaterial_Simulation_DrawBoundary();
	~LiquidMaterial_Simulation_DrawBoundary();


	
	//void SetDiffuseTexture(const std::wstring& assetFile);
	void UpdateVariables(); 
	void SetBoundaryPositionVariables(int xmin, int ymin, int xmax, int ymax, float color[4]);
	void PublicLoadEffectVariables(); 
protected:
	void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent) override;
	virtual void LoadEffectVariables();
	//virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:


	static ID3DX11EffectScalarVariable * m_pXminSRV, *m_pYminSRV, *m_pXmaxSRV, *m_pYmaxSRV;

	int m_ppmin = 0, m_pYmin = 0, m_pXmax = 0, m_pYmax = 0;

	static ID3DX11EffectVectorVariable* m_pColorSRVvariable; 
	
	float m_pColor[4] = { 1,1,0,1 };
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation_DrawBoundary(const LiquidMaterial_Simulation_DrawBoundary &obj);
	LiquidMaterial_Simulation_DrawBoundary& operator=(const LiquidMaterial_Simulation_DrawBoundary& obj);
	
};

