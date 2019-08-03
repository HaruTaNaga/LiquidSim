#pragma once
#include "Material.h"

class LiquidMaterial : public Material
{
public:
	LiquidMaterial();
	virtual ~LiquidMaterial() = default;
	LiquidMaterial(const LiquidMaterial& other) = delete;
	LiquidMaterial(LiquidMaterial&& other) noexcept = delete;
	LiquidMaterial& operator=(const LiquidMaterial& other) = delete;
	LiquidMaterial& operator=(LiquidMaterial&& other) noexcept = delete;

	void SetDiffuseSRV(ID3D11ShaderResourceView* pDiffuseSRV) { m_pDiffuseSRV = pDiffuseSRV; }
	void SetNormalSRV(ID3D11ShaderResourceView* pNormalSRV) { m_pNormalSRV = pNormalSRV; }
	
	void SetSRV(ID3D11ShaderResourceView* pVelocitySRV, ID3D11ShaderResourceView* pPressureSRV, ID3D11ShaderResourceView* pColorSRV, ID3D11ShaderResourceView* pVelocity2SRV, ID3D11ShaderResourceView* pPressure2SRV, ID3D11ShaderResourceView* pColor2SRV)
	{
		m_pVelocitySRV = pVelocitySRV; m_pPressureSRV = pPressureSRV; m_pColorSRV = pColorSRV; m_pVelocity2SRV = pVelocity2SRV; m_pPressure2SRV = pPressure2SRV; m_pColor2SRV = pColor2SRV;
	}

	
	void UpdateVariables() const;

protected:
	void LoadEffectVariables() override;
	void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent) override;

private:

	ID3D11ShaderResourceView* m_pDiffuseSRV = nullptr;
	
    ID3D11ShaderResourceView* m_pNormalSRV = nullptr;
	
	static ID3DX11EffectShaderResourceVariable* m_pDiffuseSRVvariable;
	static ID3DX11EffectShaderResourceVariable* m_pNormalSRVvariable;


	ID3D11ShaderResourceView* m_pVelocitySRV = nullptr;
	ID3D11ShaderResourceView* m_pPressureSRV = nullptr;
	ID3D11ShaderResourceView* m_pColorSRV = nullptr;
	ID3D11ShaderResourceView* m_pVelocity2SRV = nullptr;
	ID3D11ShaderResourceView* m_pPressure2SRV = nullptr;
	ID3D11ShaderResourceView* m_pColor2SRV = nullptr;
	static ID3DX11EffectShaderResourceVariable* m_pVelocitySRVvariable;
	static ID3DX11EffectShaderResourceVariable* m_pPressureSRVvariable;
	static ID3DX11EffectShaderResourceVariable* m_pColorSRVvariable;
	static ID3DX11EffectShaderResourceVariable* m_pVelocity2SRVvariable;
	static ID3DX11EffectShaderResourceVariable* m_pPressure2SRVvariable;
	static ID3DX11EffectShaderResourceVariable* m_pColor2SRVvariable;
	
};
