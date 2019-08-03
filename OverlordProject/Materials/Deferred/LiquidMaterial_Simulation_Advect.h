#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_Advect : public Material
{
public:
	LiquidMaterial_Simulation_Advect();
	~LiquidMaterial_Simulation_Advect();

	void SetSourceDiffuseSRV(ID3D11ShaderResourceView* pDiffuseSRV) { m_pDiffuseSRV = pDiffuseSRV; }
	void SetSourceAdvectionForceSRV(ID3D11ShaderResourceView* pAdvectionForceSRV) { m_pAdvectionForceSRV = pAdvectionForceSRV; }
	void SetSourceAdvectedQuantitySRV(ID3D11ShaderResourceView* pAdvectedQuantitySRV) { m_pAdvectedQuantitySRV = pAdvectedQuantitySRV; }
	//void SetDiffuseTexture(const std::wstring& assetFile);
	void UpdateVariables(); 
	void PublicLoadEffectVariables(); 
protected:
	void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent) override;
	virtual void LoadEffectVariables();
	//virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:

	TextureData* m_pDiffuseTexture;
	static ID3DX11EffectShaderResourceVariable* m_pDiffuseSRVvariable;
	ID3D11ShaderResourceView* m_pDiffuseSRV = nullptr;
	static ID3DX11EffectShaderResourceVariable* m_pAdvectionForceSRVvariable;
	ID3D11ShaderResourceView* m_pAdvectionForceSRV = nullptr;
	static ID3DX11EffectShaderResourceVariable* m_pAdvectedQuantitySRVvariable;
	ID3D11ShaderResourceView* m_pAdvectedQuantitySRV = nullptr;
	static ID3DX11EffectScalarVariable * m_pTimeStep;
	float m_pFloatTimeStep = 1.f;
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation_Advect(const LiquidMaterial_Simulation_Advect &obj);
	LiquidMaterial_Simulation_Advect& operator=(const LiquidMaterial_Simulation_Advect& obj);
	
};

