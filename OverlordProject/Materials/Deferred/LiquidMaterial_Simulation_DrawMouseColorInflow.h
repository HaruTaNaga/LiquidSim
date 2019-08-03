#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_DrawMouseColorInflow : public Material
{
public:
	LiquidMaterial_Simulation_DrawMouseColorInflow();
	~LiquidMaterial_Simulation_DrawMouseColorInflow();

	void SetSourceDiffuseSRV(ID3D11ShaderResourceView* pDiffuseSRV) { m_pDiffuseSRV = pDiffuseSRV; }
	
	//void SetDiffuseTexture(const std::wstring& assetFile);
	void UpdateVariables(); 
	void UpdateMousePosVariables(int x, int y, float xvel, float yvel, float color[3], float size = 0.1f );
	void PublicLoadEffectVariables(); 
protected:
	void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent) override;
	virtual void LoadEffectVariables();
	//virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:
	
	TextureData* m_pDiffuseTexture;
	static ID3DX11EffectShaderResourceVariable* m_pDiffuseSRVvariable;
	ID3D11ShaderResourceView* m_pDiffuseSRV = nullptr;
	static ID3DX11EffectVectorVariable * m_pColorSRV; 

	static ID3DX11EffectScalarVariable * m_pXposSRV, *m_pYposSRV, *m_pXvelSRV, *m_pYvelSRV, *m_pSizeSRV;
	float m_pFloatTimeStep = 1.f;
	int m_ppPos = 0, m_pYpos = 0, m_pXvel = 0, m_pYvel = 0;

	float m_pSize = 0.05f; 
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation_DrawMouseColorInflow(const LiquidMaterial_Simulation_DrawMouseColorInflow &obj);
	LiquidMaterial_Simulation_DrawMouseColorInflow& operator=(const LiquidMaterial_Simulation_DrawMouseColorInflow& obj);
	
};

