#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_TexToRTScalar : public Material
{
public:
	LiquidMaterial_Simulation_TexToRTScalar();
	~LiquidMaterial_Simulation_TexToRTScalar();

	void SetSourceDiffuseSRV(ID3D11ShaderResourceView* pDiffuseSRV) { m_pDiffuseSRV = pDiffuseSRV; }
	//void SetDiffuseTexture(const std::wstring& assetFile);
	void UpdateVariables(); 
protected:
	void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent) override;
	virtual void LoadEffectVariables();
	//virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:

	TextureData* m_pDiffuseTexture;
	static ID3DX11EffectShaderResourceVariable* m_pDiffuseSRVvariable;
	ID3D11ShaderResourceView* m_pDiffuseSRV = nullptr;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation_TexToRTScalar(const LiquidMaterial_Simulation_TexToRTScalar &obj);
	LiquidMaterial_Simulation_TexToRTScalar& operator=(const LiquidMaterial_Simulation_TexToRTScalar& obj);
	
};

