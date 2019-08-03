#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_Divergence : public Material
{
public:
	LiquidMaterial_Simulation_Divergence();
	~LiquidMaterial_Simulation_Divergence();


	void SetSourceSRV(ID3D11ShaderResourceView* pAdvectionForceSRV) { m_pAdvectionForceSRV = pAdvectionForceSRV; }
	//void SetSourceAdvectedQuantitySRV(ID3D11ShaderResourceView* pAdvectedQuantitySRV) { m_pAdvectedQuantitySRV = pAdvectedQuantitySRV; }
	//void SetDiffuseTexture(const std::wstring& assetFile);
	void UpdateVariables(); 
	void PublicLoadEffectVariables(); 
protected:
	void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent) override;
	virtual void LoadEffectVariables();
	//virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:


	static ID3DX11EffectShaderResourceVariable* m_pAdvectionForceSRVvariable;
	ID3D11ShaderResourceView* m_pAdvectionForceSRV = nullptr;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation_Divergence(const LiquidMaterial_Simulation_Divergence &obj);
	LiquidMaterial_Simulation_Divergence& operator=(const LiquidMaterial_Simulation_Divergence& obj);
	
};

