#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_LineIntegralConvulution : public Material
{
public:
	LiquidMaterial_Simulation_LineIntegralConvulution();
	~LiquidMaterial_Simulation_LineIntegralConvulution();

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
	LiquidMaterial_Simulation_LineIntegralConvulution(const LiquidMaterial_Simulation_LineIntegralConvulution &obj);
	LiquidMaterial_Simulation_LineIntegralConvulution& operator=(const LiquidMaterial_Simulation_LineIntegralConvulution& obj);
};

