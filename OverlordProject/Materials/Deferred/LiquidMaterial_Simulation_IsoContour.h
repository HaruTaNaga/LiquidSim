#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_IsoContour : public Material
{
public:
	LiquidMaterial_Simulation_IsoContour();
	~LiquidMaterial_Simulation_IsoContour();

	void SetDiffuseSRV(ID3D11ShaderResourceView* pDiffuseSRV) { m_pDiffuseSRV = pDiffuseSRV; }
	void UpdateVariables() const;
protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:

	static ID3DX11EffectShaderResourceVariable* m_pDiffuseSRVvariable;
	ID3D11ShaderResourceView* m_pDiffuseSRV = nullptr;
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation_IsoContour(const LiquidMaterial_Simulation_IsoContour &obj);
	LiquidMaterial_Simulation_IsoContour& operator=(const LiquidMaterial_Simulation_IsoContour& obj);
};

