#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_Jacobi : public Material
{
public:
	LiquidMaterial_Simulation_Jacobi();
	~LiquidMaterial_Simulation_Jacobi();
	void SetAlphaBetaConstants(float alpha, float beta) { m_pAlpha = alpha ; m_pBeta = beta;  }
	
	void SetXVectorSRV(ID3D11ShaderResourceView* pXvecSRV) { m_pXvec_SRV = pXvecSRV; }
	void SetBVectorSRV(ID3D11ShaderResourceView* pBvecSRV) { m_pBvec_SRV = pBvecSRV; }

	//void SetDiffuseTexture(const std::wstring& assetFile);
	void UpdateVariables(); 
	void PublicLoadEffectVariables(); 
protected:
	void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent) override;
	virtual void LoadEffectVariables();
	//virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:

	TextureData* m_pDiffuseTexture;

	static ID3DX11EffectShaderResourceVariable* m_pXvec_SRVvariable;
	ID3D11ShaderResourceView* m_pXvec_SRV = nullptr;
	static ID3DX11EffectShaderResourceVariable* m_pBvec_SRVvariable;
	ID3D11ShaderResourceView* m_pBvec_SRV = nullptr;
	static ID3DX11EffectScalarVariable * m_pTimeStep;
	float m_pFloatTimeStep = 1.f;
	static ID3DX11EffectScalarVariable * m_pAlphaSRV;
	float m_pAlpha = 1.f;
	static ID3DX11EffectScalarVariable * m_pBetaSRV;
	float m_pBeta = 0.2f; // 1/(4+(dx/dt))
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation_Jacobi(const LiquidMaterial_Simulation_Jacobi &obj);
	LiquidMaterial_Simulation_Jacobi& operator=(const LiquidMaterial_Simulation_Jacobi& obj);
	
};

