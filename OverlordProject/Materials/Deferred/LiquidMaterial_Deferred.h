#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Deferred : public Material
{
public:
	LiquidMaterial_Deferred();
	~LiquidMaterial_Deferred();

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
	LiquidMaterial_Deferred(const LiquidMaterial_Deferred &obj);
	LiquidMaterial_Deferred& operator=(const LiquidMaterial_Deferred& obj);
};

