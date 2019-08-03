#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_Boundary : public Material
{
public:
	LiquidMaterial_Simulation_Boundary();
	~LiquidMaterial_Simulation_Boundary();

	void SetSourceDiffuseSRV(ID3D11ShaderResourceView* pDiffuseSRV) { m_pDiffuseSRV = pDiffuseSRV; }
	void SetSourceBoundarySRV(ID3D11ShaderResourceView* pBoundarySRV) { m_pBoundarySRV = pBoundarySRV; }
	//void SetDiffuseTexture(const std::wstring& assetFile);
	void UpdateVariables(); 
	void SetIsPressure(float IsPressure) { m_pIsPressure = IsPressure; }
	void PublicLoadEffectVariables(); 
protected:
	void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent) override;
	virtual void LoadEffectVariables();
	//virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:


	static ID3DX11EffectShaderResourceVariable* m_pDiffuseSRVvariable;
	ID3D11ShaderResourceView* m_pDiffuseSRV = nullptr;
	static ID3DX11EffectShaderResourceVariable* m_pBoundarySRVvariable;
	ID3D11ShaderResourceView* m_pBoundarySRV = nullptr;
	static ID3DX11EffectScalarVariable * m_pIsPressureSV;
	float m_pFloatTimeStep = 1.f;
	float m_pIsPressure = -1; 
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation_Boundary(const LiquidMaterial_Simulation_Boundary &obj);
	LiquidMaterial_Simulation_Boundary& operator=(const LiquidMaterial_Simulation_Boundary& obj);
	
};

