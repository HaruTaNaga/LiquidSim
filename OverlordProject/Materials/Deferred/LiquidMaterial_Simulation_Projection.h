#pragma once
#include "Material.h"

class TextureData;

class LiquidMaterial_Simulation_Projection : public Material
{
public:
	LiquidMaterial_Simulation_Projection();
	~LiquidMaterial_Simulation_Projection();
	
	void SetVelocitySRV(ID3D11ShaderResourceView* pXvecSRV) { m_pVelocityMap_SRV = pXvecSRV; }
	void SetPressureSRV(ID3D11ShaderResourceView* pBvecSRV) { m_pPressureMap_SRV = pBvecSRV; }

	//void SetDiffuseTexture(const std::wstring& assetFile);
	void UpdateVariables(); 
	void PublicLoadEffectVariables(); 
protected:
	void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent) override;
	virtual void LoadEffectVariables();
	//virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:


	static ID3DX11EffectShaderResourceVariable* m_pVelocityMap_SRVvariable;
	ID3D11ShaderResourceView* m_pVelocityMap_SRV = nullptr;
	static ID3DX11EffectShaderResourceVariable* m_pPressureMap_SRVvariable;
	ID3D11ShaderResourceView* m_pPressureMap_SRV = nullptr;

	
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	LiquidMaterial_Simulation_Projection(const LiquidMaterial_Simulation_Projection &obj);
	LiquidMaterial_Simulation_Projection& operator=(const LiquidMaterial_Simulation_Projection& obj);
	
};

