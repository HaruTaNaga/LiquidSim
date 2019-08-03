#pragma once
#include "Singleton.h"

enum class DeferredBufferIDs
{
	COLOR = 0,
	NORMAL = 1,
	SPECULAR = 2,
	LIGHT_ACCUMULATION = 3
};

enum class LiquidSimBufferIDs
{
	COLOR = 0,
	VELOCITY = 1,
	PRESSURE = 2,
	VELOCITY2 = 3,
	PRESSURE2 = 4,
	COLOR2 = 5,
};

enum class BufferIDs
{
	DiffuseInitial = 0,
	NormalInitial = 1,
	Color0 = 2,
	Pressure0 = 3,
	Velocity0 = 4,
	Color1 = 5,
	Pressure1 = 6,
	Velocity1 = 7

};
enum class BufferIDs2
{
	Boundary = 0,
	InflowVelocitySeed = 1,
	Outflow = 2,
	Temperature = 3,
	NotInUse1 = 4,
	NotInUse2 = 5,
	InflowTemperatureSeed = 6,
	InflowColorSeed = 7

};


class OverlordGame;
class QuadDrawer;

class LiquidMaterial;
class LiquidSeedMaterial; 
class LiquidScalarMaterial;
class DiffuseMaterial_Deferred;
class LiquidMaterial_Simulation; 
class LiquidMaterial_Simulation_DrawMouseVel; 
class LiquidMaterial_Simulation_Advect;
class LiquidMaterial_Simulation_Jacobi;
class LiquidMaterial_Simulation_Divergence; 
class LiquidMaterial_Simulation_TexToRT;
class LiquidMaterial_Simulation_TexToRTScalar;
class LiquidMaterial_Simulation_Projection; 
class LiquidMaterial_Simulation_Boundary;
class LiquidMaterial_Simulation_DrawBoundary; 
class LiquidMaterial_Simulation_IsoContour;
class LiquidMaterial_Simulation_LineIntegralConvulution;
class LiquidMaterial_Simulation_IsoContourVelocity;
class LiquidMaterial_Simulation_IsoLineVelocity;
class LiquidMaterial_Simulation_DrawMouseInflow; 
class LiquidMaterial_Simulation_Inflow;
class LiquidMaterial_Simulation_DrawMouseColorInflow;
class LiquidMaterial_Simulation_IsoLineScalar; 
class LiquidMaterial_Simulation_VelocityGradient; 
class LiquidRenderer : public Singleton<LiquidRenderer>
{
public:
	LiquidRenderer();
	virtual ~LiquidRenderer();
	LiquidRenderer(const LiquidRenderer& other) = delete;
	LiquidRenderer(LiquidRenderer&& other) noexcept = delete;
	LiquidRenderer& operator=(const LiquidRenderer& other) = delete;
	LiquidRenderer& operator=(LiquidRenderer&& other) noexcept = delete;

	void InitRenderer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, OverlordGame* pGame);
	ID3D11ShaderResourceView* GetShaderResourceView(DeferredBufferIDs id) const { return m_pShaderResourceViews1[int(id)]; }

	void SetGameSettings(GameSettings gamesettings) { m_pGameSettings = gamesettings; }
	void SetDrawBoundary(bool drawboundary) { m_pDrawBoundary = drawboundary; }
	void Begin();
	void End();


	void SimulationStep(); 
	void SwapRenderTargetBindings(); 
	void SwapVelocityRTBinding(); 
	void SwapPressureRTBinding(); 
	void SwapColorRTBinding();
	void RenderFrameToSeedRT(); 
	void Advection();
	void PressureProjection(); 
	void Diffusion(); 
	void BoundaryProjection(); 
	void Inflow();

	void RenderMouseToRT(GameContext gameContext);
	void DrawGui();

private:
 
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr;
	OverlordGame* m_pGame = nullptr;
	GameSettings m_pGameSettings;
	//Geometric Buffer (GBuffer)
	void CreateBufferAndView(int width, int height, DXGI_FORMAT format, ID3D11Texture2D** outputBuffer,
	                         ID3D11RenderTargetView** outputRTview = nullptr,
	                         ID3D11ShaderResourceView** outputSRview = nullptr) const;
	void CreateDepthStencilBufferAndView(int width, int height);
	void ClearRenderTargets(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	void SetRenderTargets() const;

	static const int BUFFER_COUNT = 8;
	ID3D11Texture2D* m_pBuffers1[BUFFER_COUNT]{}; //Since only 8 can be bound at a time there are managed in two sets of 8 
	ID3D11RenderTargetView* m_pRenderTargetViews1[BUFFER_COUNT]{};
	ID3D11ShaderResourceView* m_pShaderResourceViews1[BUFFER_COUNT]{};
	ID3D11Texture2D* m_pBuffers2[BUFFER_COUNT]{};
	ID3D11RenderTargetView* m_pRenderTargetViews2[BUFFER_COUNT]{};
	ID3D11ShaderResourceView* m_pShaderResourceViews2[BUFFER_COUNT]{};
	ID3D11Texture2D* m_pDepthStencilBuffer = nullptr;
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;

	QuadDrawer* m_pQuadDrawer = nullptr;

	LiquidMaterial* m_pLiquidMat = nullptr;
	LiquidSeedMaterial* m_pLiquidSeedMat = nullptr; 
	LiquidScalarMaterial* m_pLiquidScalarMat = nullptr;
	DiffuseMaterial_Deferred* m_pDiffuseSeedMat = nullptr; 
	LiquidMaterial_Simulation* m_pLiquidMaterialSimulation = nullptr;
	LiquidMaterial_Simulation_DrawMouseVel* m_pLiquidDrawMouseVel = nullptr;
	LiquidMaterial_Simulation_TexToRT* m_pLiquidTexToRTMat = nullptr; 
	LiquidMaterial_Simulation_TexToRTScalar* m_pLiquidTexToRTScalarMat = nullptr;
	LiquidMaterial_Simulation_Divergence* m_pLiquidDivergenceMat = nullptr;
	LiquidMaterial_Simulation_Jacobi* m_pLiquidJacobiIterMat = nullptr;
	LiquidMaterial_Simulation_Projection* m_pLiquidProjectionMat = nullptr; 
	LiquidMaterial_Simulation_Boundary* m_pLiquidBoundaryMat = nullptr;
	LiquidMaterial_Simulation_DrawBoundary* m_pLiquidDrawBoundaryMat = nullptr;
	LiquidMaterial_Simulation_IsoContour* m_pLiquidIsoContourMat = nullptr;
	LiquidMaterial_Simulation_LineIntegralConvulution* m_pLiquidLICMat = nullptr; 
	LiquidMaterial_Simulation_IsoContourVelocity* m_pLiquidIsoContourVelMat = nullptr; 
	LiquidMaterial_Simulation_IsoLineVelocity* m_pLiquidIsoLineVelMat = nullptr; 
	LiquidMaterial_Simulation_IsoLineScalar* m_pLiquidIsoLineScalarMat = nullptr; 
	LiquidMaterial_Simulation_DrawMouseInflow* m_pLiquidDrawInflowMat = nullptr; 
	LiquidMaterial_Simulation_Inflow* m_pLiquidInflowMat = nullptr;
	LiquidMaterial_Simulation_DrawMouseColorInflow * m_pLiquidColorInflowMat = nullptr;
	LiquidMaterial_Simulation_VelocityGradient * m_pLiquidVelGradMat = nullptr; 

	bool m_pSwitchedRenderTargets = false, m_pIsVelocitySwitched = false, m_pIsPressureSwitched = false, m_pIsColorSwitched = false;
	bool m_pWasMouseDownPrevFrame, m_pWasKeyButtonDown, m_pSeedInflowWithColor = false, m_pSeedInflowWithVelocity = false, m_pSeedInflowWithTemperature = false;
	int m_pPrevX, m_pPrevY;
	int m_pVelX, m_pVelY;
	int m_pRenderState = 0;
	int m_pMaxRenderStates = 8;
	int m_pInputState = 0;
	int m_pMaxInputStates = 3;

	POINT m_pPrevPos, m_pPoint1, m_pPoint2;
	POINT m_pVel;
	bool IsEnabled = false;
	bool IsInitialized = false;
	bool IsNotFirstFrame = false;
	bool m_pHasClicked = false;
	bool m_pDrawBoundary = true;
	int m_pBufferIDs1[BUFFER_COUNT] = { 0,1,2,3,4,5,6,7 };
	int m_pBufferIDs2[BUFFER_COUNT] = { 0,1,2,3,4,5,6,7 };
	float m_pBrushColor[3] = { 0.2f,0.3f,0.4f };
	float *m_pBrushVelocity =  new float(0.3f);
	float *m_pBrushSize = new float(0.05f); 
	float m_pInflowVelocity[2] = { 0.5f,0.5f };

	LiquidMaterial_Simulation_Advect* m_pLiquidMatSim_Advect = nullptr; 
};
