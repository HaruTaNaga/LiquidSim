#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_VelocityGradient : public Material
{
public:
	LiquidMaterial_Simulation_VelocityGradient();
	~LiquidMaterial_Simulation_VelocityGradient();

	void SetDiffuseSRV(ID3D11ShaderResourceView* pDiffuseSRV) { m_pDiffuseSRV = pDiffuseSRV; }

	void SetAdvectionSRV(ID3D11ShaderResourceView* pAdvectionSRV) { m_pAdvectionSRV = pAdvectionSRV; }
	void UpdateVariables() const;
protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:

	static ID3DX11EffectShaderResourceVariable* m_pDiffuseSRVvariable;
	ID3D11ShaderResourceView* m_pDiffuseSRV = nullptr;
	static ID3DX11EffectShaderResourceVariable* m_pAdvectionSRVvariable;
	ID3D11ShaderResourceView* m_pAdvectionSRV = nullptr;
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation_VelocityGradient(const LiquidMaterial_Simulation_VelocityGradient &obj);
	LiquidMaterial_Simulation_VelocityGradient& operator=(const LiquidMaterial_Simulation_VelocityGradient& obj);
};

