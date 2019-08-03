#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation : public Material
{
public:
	LiquidMaterial_Simulation();
	~LiquidMaterial_Simulation();

	void SetDiffuseTexture(const std::wstring& assetFile);

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:

	TextureData* m_pDiffuseTexture;
	static ID3DX11EffectShaderResourceVariable* m_pDiffuseSRVvariable;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation(const LiquidMaterial_Simulation &obj);
	LiquidMaterial_Simulation& operator=(const LiquidMaterial_Simulation& obj);
};

