#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_IsoContourVelocity : public Material
{
public:
	LiquidMaterial_Simulation_IsoContourVelocity();
	~LiquidMaterial_Simulation_IsoContourVelocity();

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
	LiquidMaterial_Simulation_IsoContourVelocity(const LiquidMaterial_Simulation_IsoContourVelocity &obj);
	LiquidMaterial_Simulation_IsoContourVelocity& operator=(const LiquidMaterial_Simulation_IsoContourVelocity& obj);
};

