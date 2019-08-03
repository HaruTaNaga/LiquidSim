#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_Inflow : public Material
{
public:
	LiquidMaterial_Simulation_Inflow();
	~LiquidMaterial_Simulation_Inflow();

	void SetSourceInflowSRV(ID3D11ShaderResourceView* pSourceSRV) { m_pSourceSRV = pSourceSRV; }
	//void SetDiffuseTexture(const std::wstring& assetFile);
	void UpdateVariables(); 
	void SetIsPressure(float IsPressure) { m_pIsPressure = IsPressure; }
	void PublicLoadEffectVariables(); 
protected:
	void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent) override;
	virtual void LoadEffectVariables();
	//virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:

	static ID3DX11EffectShaderResourceVariable* m_pSourceSRVvariable;
	ID3D11ShaderResourceView* m_pSourceSRV = nullptr;
	static ID3DX11EffectScalarVariable * m_pIsPressureSV;
	float m_pFloatTimeStep = 1.f;
	float m_pIsPressure = -1; 
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation_Inflow(const LiquidMaterial_Simulation_Inflow &obj);
	LiquidMaterial_Simulation_Inflow& operator=(const LiquidMaterial_Simulation_Inflow& obj);
	
};

