#include "stdafx.h"
#include "LiquidRenderer.h"
#include "QuadDrawer.h"
#include "../OverlordProject/Materials/Deferred/DiffuseMaterial_Deferred.h"
#include "../OverlordProject/Materials/LiquidMaterial.h"
#include "../OverlordProject/Materials/LiquidSeedMaterial.h"
#include "../OverlordProject/Materials/LiquidScalarMaterial.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_Advect.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_DrawMouseVel.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_RenderToRT.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_RenderToRTScalar.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_Jacobi.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_Divergence.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_Projection.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_Boundary.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_DrawBoundary.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_IsoContour.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_IsoContourVelocity.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_IsoLineVelocity.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_IsoLineScalar.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_LIC.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_DrawMouseInflow.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_Inflow.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_DrawMouseColorInflow.h"
#include "..\OverlordProject\Materials\Deferred/LiquidMaterial_Simulation_VelocityGradient.h"
#include "OverlordGame.h"

#include "..\Libs\imgui\imgui.h"
#include "..\Libs\imgui\imgui_impl_win32.h"
#include "..\Libs\imgui\imgui_impl_dx11.h"

LiquidRenderer::LiquidRenderer()
{
	for (auto i = 0; i < BUFFER_COUNT; i++)
	{
		m_pBuffers1[i] = nullptr;
		m_pRenderTargetViews1[i] = nullptr;
		m_pShaderResourceViews1[i] = nullptr;
	}
}

LiquidRenderer::~LiquidRenderer()
{
	for (auto i = 0; i < BUFFER_COUNT; i++)
	{
		SafeRelease(m_pBuffers1[i]);
		SafeRelease(m_pRenderTargetViews1[i]);
		SafeRelease(m_pShaderResourceViews1[i]);
	}

	SafeRelease(m_pDepthStencilBuffer);
	SafeRelease(m_pDepthStencilView);

	SafeDelete(m_pQuadDrawer);
	SafeDelete(m_pLiquidMat);
	SafeDelete(m_pDiffuseSeedMat);
	SafeDelete(m_pLiquidTexToRTMat);
	SafeDelete(m_pLiquidTexToRTScalarMat);

}

void LiquidRenderer::InitRenderer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, OverlordGame* pGame)
{
	if (IsInitialized)
		Logger::LogWarning(L"LiquidRenderer::InitRenderer>> Already Initialized!!! (multiple invocations)");

	const auto gameSettings = OverlordGame::GetGameSettings();
	IsEnabled = gameSettings.DirectX.EnableDeferredRendering;

	if (!IsEnabled)
		Logger::LogWarning(L"LiquidRenderer::InitRenderer>> DeferredRendering DISABLED but initialized...");

	m_pDevice = pDevice;
	m_pDeviceContext = pDeviceContext;
	m_pGame = pGame;

	const auto width = gameSettings.Window.Width;
	const auto height = gameSettings.Window.Height;


	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.WantCaptureMouse = true;
	io.DisplaySize = ImVec2(300, 100);

	ImGui_ImplWin32_Init(m_pGameSettings.Window.WindowHandle);
	ImGui_ImplDX11_Init(pDevice, pDeviceContext);
	ImGui::StyleColorsDark();


	for (int i = 0; i < BUFFER_COUNT; i++)
	{
		CreateBufferAndView(width, height, DXGI_FORMAT_R32G32B32A32_FLOAT, &m_pBuffers1[int(i)],
			&m_pRenderTargetViews1[int(i)],
			&m_pShaderResourceViews1[int(i)]);
	}
	for (int i = 0; i < BUFFER_COUNT; i++)
	{
		CreateBufferAndView(width, height, DXGI_FORMAT_R32G32B32A32_FLOAT, &m_pBuffers2[int(i)],
			&m_pRenderTargetViews2[int(i)],
			&m_pShaderResourceViews2[int(i)]);
	}

	//Create Depth-Stencil Buffer and View
	CreateDepthStencilBufferAndView(width, height);

	//Initialize QuadDrawer & Material
	m_pQuadDrawer = new QuadDrawer();
	m_pQuadDrawer->Initialize(pDevice);

	m_pLiquidMat = new LiquidMaterial();
	m_pLiquidSeedMat = new LiquidSeedMaterial();
	m_pLiquidScalarMat = new LiquidScalarMaterial();
	m_pDiffuseSeedMat = new DiffuseMaterial_Deferred();
	m_pLiquidMaterialSimulation = new LiquidMaterial_Simulation();
	m_pLiquidTexToRTMat = new LiquidMaterial_Simulation_TexToRT();
	m_pLiquidTexToRTScalarMat = new LiquidMaterial_Simulation_TexToRTScalar();
	m_pDiffuseSeedMat->SetDiffuseTexture(L"./Resources/Textures/Knight.jpg");
	m_pLiquidDrawMouseVel = new LiquidMaterial_Simulation_DrawMouseVel();
	m_pLiquidMatSim_Advect = new LiquidMaterial_Simulation_Advect();
	m_pLiquidJacobiIterMat = new LiquidMaterial_Simulation_Jacobi();
	m_pLiquidDivergenceMat = new LiquidMaterial_Simulation_Divergence();
	m_pLiquidProjectionMat = new LiquidMaterial_Simulation_Projection();
	m_pLiquidBoundaryMat = new LiquidMaterial_Simulation_Boundary();
	m_pLiquidDrawBoundaryMat = new LiquidMaterial_Simulation_DrawBoundary();
	m_pLiquidIsoContourMat = new LiquidMaterial_Simulation_IsoContour();
	m_pLiquidIsoContourVelMat = new LiquidMaterial_Simulation_IsoContourVelocity();
	m_pLiquidIsoLineVelMat = new LiquidMaterial_Simulation_IsoLineVelocity();
	m_pLiquidIsoLineScalarMat = new LiquidMaterial_Simulation_IsoLineScalar();
	m_pLiquidLICMat = new LiquidMaterial_Simulation_LineIntegralConvulution();
	m_pLiquidDrawInflowMat = new LiquidMaterial_Simulation_DrawMouseInflow();
	m_pLiquidInflowMat = new LiquidMaterial_Simulation_Inflow();
	m_pLiquidColorInflowMat = new LiquidMaterial_Simulation_DrawMouseColorInflow();
	m_pLiquidVelGradMat = new LiquidMaterial_Simulation_VelocityGradient(); 
	GameContext tempContext{};
	tempContext.pDevice = pDevice;
	tempContext.pDeviceContext = pDeviceContext;
	m_pLiquidMat->Initialize(tempContext);
	m_pLiquidSeedMat->Initialize(tempContext);
	m_pLiquidScalarMat->Initialize(tempContext);
	m_pDiffuseSeedMat->Initialize(tempContext);
	m_pLiquidMaterialSimulation->Initialize(tempContext);
	m_pLiquidTexToRTScalarMat->Initialize(tempContext);
	m_pLiquidDivergenceMat->Initialize(tempContext);
	m_pLiquidTexToRTMat->Initialize(tempContext);
	m_pLiquidMatSim_Advect->Initialize(tempContext);
	m_pLiquidDrawMouseVel->Initialize(tempContext);
	m_pLiquidJacobiIterMat->Initialize(tempContext);
	m_pLiquidProjectionMat->Initialize(tempContext);
	m_pLiquidBoundaryMat->Initialize(tempContext);
	m_pLiquidDrawBoundaryMat->Initialize(tempContext);
	m_pLiquidIsoContourMat->Initialize(tempContext);
	m_pLiquidIsoContourVelMat->Initialize(tempContext);
	m_pLiquidLICMat->Initialize(tempContext);
	m_pLiquidDrawInflowMat->Initialize(tempContext);
	m_pLiquidInflowMat->Initialize(tempContext);
	m_pLiquidColorInflowMat->Initialize(tempContext);
	m_pLiquidIsoLineVelMat->Initialize(tempContext);
	m_pLiquidIsoLineScalarMat->Initialize(tempContext);
	m_pLiquidVelGradMat->Initialize(tempContext);
}

void LiquidRenderer::SetRenderTargets() const
{
	m_pDeviceContext->OMSetRenderTargets(BUFFER_COUNT, m_pRenderTargetViews1, m_pDepthStencilView);
}

void LiquidRenderer::Begin()
{
	//Hijack Rendering Pipeline :)
	ClearRenderTargets(0, 0, 0, 0);
	float clearColor[4] = { 0, 0, 0, 0 };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetViews1[0], clearColor);
	SetRenderTargets();
}
void LiquidRenderer::RenderFrameToSeedRT()
{


	ID3D11RenderTargetView* rTargets2[3] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Color0)]], m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Pressure0)]], m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]] };
	m_pDeviceContext->OMSetRenderTargets(3, rTargets2, m_pDepthStencilView);
	m_pLiquidTexToRTMat->SetSourceDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::DiffuseInitial)]]);
	m_pLiquidTexToRTMat->UpdateVariables();
	m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidTexToRTMat);

	float clearColor[4] = { 0, 0, 0, 1 };
	float zeroColor[4] = { 0, 0, 0, 0 };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetViews2[m_pBufferIDs2[int(BufferIDs2::Boundary)]], clearColor);
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetViews2[m_pBufferIDs2[int(BufferIDs2::InflowVelocitySeed)]], zeroColor);
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::NormalInitial)]], clearColor);
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Pressure0)]], clearColor);

}

void LiquidRenderer::End()
{


	SimulationStep();
	//Draw Final Composition	//Reset Default Rendertarget (Forward Rendering)

	ID3D11RenderTargetView* rTargets[8] = { nullptr,nullptr,nullptr, nullptr, nullptr, nullptr, nullptr ,nullptr };
	m_pDeviceContext->OMSetRenderTargets(8, rTargets, nullptr);
	m_pGame->SetRenderTarget(nullptr);

	switch (m_pRenderState) //Render diffusecolor
	{
	case 0:
		//m_pLiquidMat->SetDiffuseSRV(m_pShaderResourceViews2[m_pBufferIDs2[int(BufferIDs2::InflowColorSeed)]]);
		m_pLiquidMat->SetDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Color0)]]);
		//m_pLiquidMat->SetNormalSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::NormalInitial)]]); //todo remove
		m_pLiquidMat->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidMat);
		break;
		//Render color + velocity 
	case 1:
		m_pLiquidLICMat->SetDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Color0)]]);
		m_pLiquidLICMat->SetAdvectionSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
		m_pLiquidLICMat->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidLICMat);
		break;
		//Render velocity iso grad
	case 2:
		m_pLiquidIsoContourVelMat->SetDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
		m_pLiquidIsoContourVelMat->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidIsoContourVelMat);
		break;
		//Render divergence pressure iso grad 
	case 3:
		m_pLiquidIsoContourMat->SetDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Pressure0)]]);
		m_pLiquidIsoContourMat->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidIsoContourMat);
		break;
		//Render Velocity iso line 
	case 4:
		m_pLiquidIsoLineVelMat->SetDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
		m_pLiquidIsoLineVelMat->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidIsoLineVelMat);
		break;
	case 5:
		m_pLiquidIsoLineScalarMat->SetDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Pressure0)]]);
		m_pLiquidIsoLineScalarMat->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidIsoLineScalarMat);
		break;
	case 6:

		m_pLiquidVelGradMat->SetDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Color0)]]);
		m_pLiquidVelGradMat->SetAdvectionSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
		m_pLiquidVelGradMat->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidVelGradMat);
		break;
	case 7:

		m_pLiquidVelGradMat->SetDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Color0)]]);
		m_pLiquidVelGradMat->SetAdvectionSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Pressure0)]]);
		m_pLiquidVelGradMat->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidVelGradMat);
		break;
	}


	ID3D11ShaderResourceView*const pSRV[2] = { nullptr, nullptr };
	m_pDeviceContext->PSSetShaderResources(0, 2, pSRV);



}
void LiquidRenderer::RenderMouseToRT(GameContext gameContext)
{
	if (gameContext.pInput->GetMousePosition().x > 700 && gameContext.pInput->GetMousePosition().y > 800)
		return;



	switch (m_pInputState) {
	case 0: //Draw Boundary
		if (gameContext.pInput->IsMouseButtonDown(VK_LBUTTON) && !m_pWasMouseDownPrevFrame)
		{
			m_pWasMouseDownPrevFrame = true;
			if (!m_pHasClicked)
			{
				m_pPoint1 = gameContext.pInput->GetMousePosition();
				m_pHasClicked = true;
			}
			else
			{
				/**/
				m_pPoint2 = gameContext.pInput->GetMousePosition();
				ID3D11RenderTargetView* rTargets10[1] = { m_pRenderTargetViews2[m_pBufferIDs2[int(BufferIDs2::Boundary)]] };
				m_pDeviceContext->OMSetRenderTargets(1, rTargets10, nullptr);
				m_pLiquidDrawBoundaryMat->UpdateVariables();

				int xmin, xmax, ymin, ymax;
				if (m_pPoint1.x < m_pPoint2.x)
				{
					xmin = m_pPoint1.x;
					xmax = m_pPoint2.x;
				}
				else {
					xmin = m_pPoint2.x;
					xmax = m_pPoint1.x;
				}
				if (m_pPoint1.y < m_pPoint2.y)
				{
					ymin = m_pPoint1.y;
					ymax = m_pPoint2.y;
				}
				else {
					ymin = m_pPoint2.y;
					ymax = m_pPoint1.y;
				}
				float red[4] = { 1,0,1,1 };
				m_pLiquidDrawBoundaryMat->SetBoundaryPositionVariables(xmin, ymin, xmax, ymax, red);
				m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidDrawBoundaryMat);
				//SwapVelocityRTBinding();
				m_pHasClicked = false;
			}

		}
		else
		{
			m_pWasMouseDownPrevFrame = false;
		}
		break;

		//Draw Velocity 
	case 1:
		if (m_pWasMouseDownPrevFrame)
		{
			if (gameContext.pInput->IsMouseButtonDown(VK_LBUTTON))
			{
				auto pos = gameContext.pInput->GetMousePosition();
				m_pVelX = pos.x - m_pPrevPos.x;
				m_pVelY = pos.y - m_pPrevPos.y;
				Logger::LogWarning(std::to_wstring(m_pVelX));
				Logger::LogWarning(std::to_wstring(m_pVelY));
				ID3D11RenderTargetView* rTargets3[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]] };
				m_pDeviceContext->OMSetRenderTargets(1, rTargets3, nullptr);
				m_pLiquidDrawMouseVel->SetSourceDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity1)]]);
				m_pLiquidDrawMouseVel->UpdateVariables();
				m_pLiquidDrawMouseVel->UpdateMousePosVariables(pos.x, pos.y, m_pVelX, m_pVelY, *m_pBrushSize);
				m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidDrawMouseVel);

			}

		}

		if (gameContext.pInput->IsMouseButtonDown(VK_LBUTTON))
		{
			auto pos = gameContext.pInput->GetMousePosition();
			m_pPrevPos = pos;
			m_pWasMouseDownPrevFrame = true;
		}
		else
		{
			m_pPrevX = 0; m_pPrevY = 0;
			m_pWasMouseDownPrevFrame = false;
		}
		break;
	case 2: //Draw Inflow
		if (gameContext.pInput->IsMouseButtonDown(VK_LBUTTON))
		{


			if (m_pSeedInflowWithVelocity)
			{
				auto pos = gameContext.pInput->GetMousePosition();
				ID3D11RenderTargetView* rTargets3[1] = { m_pRenderTargetViews2[m_pBufferIDs2[int(BufferIDs2::InflowVelocitySeed)]] };
				m_pDeviceContext->OMSetRenderTargets(1, rTargets3, nullptr);
				m_pLiquidDrawInflowMat->SetSourceDiffuseSRV(m_pShaderResourceViews2[m_pBufferIDs2[int(BufferIDs2::NotInUse1)]]); // todo remove
				m_pLiquidDrawInflowMat->UpdateVariables();
				m_pLiquidDrawInflowMat->UpdateMousePosVariables(pos.x, pos.y, m_pInflowVelocity[0], m_pInflowVelocity[1], m_pBrushColor, *m_pBrushSize);
				m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidDrawInflowMat);
			}
			if (m_pSeedInflowWithColor)
			{
				auto pos = gameContext.pInput->GetMousePosition();
				ID3D11RenderTargetView* rTargets3[1] = { m_pRenderTargetViews2[m_pBufferIDs2[int(BufferIDs2::InflowColorSeed)]] };
				m_pDeviceContext->OMSetRenderTargets(1, rTargets3, nullptr);
				m_pLiquidColorInflowMat->SetSourceDiffuseSRV(m_pShaderResourceViews2[m_pBufferIDs2[int(BufferIDs2::NotInUse1)]]); // todo remove
				m_pLiquidColorInflowMat->UpdateVariables();
				m_pLiquidColorInflowMat->UpdateMousePosVariables(pos.x, pos.y, m_pInflowVelocity[0], m_pInflowVelocity[1], m_pBrushColor, *m_pBrushSize);
				m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidColorInflowMat);
			}
			if (m_pSeedInflowWithTemperature)
			{
				auto pos = gameContext.pInput->GetMousePosition();
				ID3D11RenderTargetView* rTargets3[1] = { m_pRenderTargetViews2[m_pBufferIDs2[int(BufferIDs2::InflowTemperatureSeed)]] };
				m_pDeviceContext->OMSetRenderTargets(1, rTargets3, nullptr);
				m_pLiquidDrawInflowMat->SetSourceDiffuseSRV(m_pShaderResourceViews2[m_pBufferIDs2[int(BufferIDs2::NotInUse1)]]); // todo remove
				m_pLiquidDrawInflowMat->UpdateVariables();
				m_pLiquidDrawInflowMat->UpdateMousePosVariables(pos.x, pos.y, m_pInflowVelocity[0], m_pInflowVelocity[1], m_pBrushColor, *m_pBrushSize);
				m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidDrawInflowMat);
			}

		}
		break;
	}

}

void LiquidRenderer::SimulationStep()
{

	Diffusion();
	Inflow();
	PressureProjection();
	BoundaryProjection();

	Advection();

}

void LiquidRenderer::DrawGui()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Any application code here

	if (ImGui::Button("Change Rendermode"))
		++m_pRenderState %= m_pMaxRenderStates;
	ImGui::SameLine();
	switch (m_pRenderState)
	{
	case 0:	ImGui::Text("Color"); break;
	case 1: ImGui::Text("Velocity Color overlay"); break;
	case 2: ImGui::Text("Velocity "); break;
	case 3: ImGui::Text("Pressure Gradient "); break;
	case 4: ImGui::Text("Velocity IsoLine"); break;
	case 5: ImGui::Text("Pressure Gradient IsoLine"); break;
	}
	//ImGui::SameLine();

	if (ImGui::Button("Change Inputmode"))
		++m_pInputState %= m_pMaxInputStates;
	ImGui::SameLine();

	switch (m_pInputState)
	{
	case 0:

		ImGui::Text("Boundary: Click 2x to create");
		break;
	case 1:

		ImGui::Text("Velocity Paiting");
		ImGui::DragFloat("Vel", m_pBrushVelocity, 0.025f, -10, 10);
		ImGui::DragFloat("Size", m_pBrushSize, 0.0005f, 0, 0.3f);
		break;
	case 2:

		ImGui::Text("Persistent Inflow Painting");
		if (ImGui::Button("Draw Seed with Color"))
		{
			m_pSeedInflowWithColor = !m_pSeedInflowWithColor;
		}

		ImGui::SameLine();
		if (m_pSeedInflowWithColor)
			ImGui::Text("On");
		else ImGui::Text("Off");
		if (ImGui::Button("Draw Seed with Velocity")) {
			m_pSeedInflowWithVelocity = !m_pSeedInflowWithVelocity;
		}

		ImGui::SameLine();
		if (m_pSeedInflowWithVelocity)
			ImGui::Text("On");
		else ImGui::Text("Off");

		if (ImGui::Button("Draw Seed with Temperature"))
		{
			m_pSeedInflowWithTemperature = !m_pSeedInflowWithTemperature;
		}

		ImGui::SameLine();
		if (m_pSeedInflowWithTemperature)
			ImGui::Text("On");
		else ImGui::Text("Off");
		ImGui::DragFloat("Size", m_pBrushSize, 0.001f, -0.4f, 0.4f);

		if (m_pSeedInflowWithColor)
			ImGui::ColorPicker3("Inflow Color", m_pBrushColor);

		if (m_pSeedInflowWithVelocity)
			ImGui::DragFloat2("Vel", m_pInflowVelocity, 0.01f, -15, 15);
		if (m_pSeedInflowWithTemperature)
			ImGui::Text("Todo::Temp");

	}



	//ImGui::ColorPicker3("Pick Seed color", m_pBrushColor);

	ImGui::SetWindowSize(ImVec2(300, 200));
	ImGui::SetWindowPos(ImVec2(700, 800));
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void LiquidRenderer::Diffusion()
{
	float clearColor[4] = { 0, 0, 0, 1 };


	//Diffuse velocity Pass
	m_pLiquidJacobiIterMat->SetAlphaBetaConstants(1.0f, 0.2f);
	for (int i = 0; i < 8; i++)
	{
		ID3D11RenderTargetView* rTargets5[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Velocity1)]] };
		m_pDeviceContext->OMSetRenderTargets(1, rTargets5, nullptr);
		m_pLiquidJacobiIterMat->SetXVectorSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
		m_pLiquidJacobiIterMat->SetBVectorSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
		m_pLiquidJacobiIterMat->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidJacobiIterMat);
		SwapVelocityRTBinding();
	}
	//diffuse color
	m_pLiquidJacobiIterMat->SetAlphaBetaConstants(1.f, 0.2f);
	for (int i = 0; i < 1; i++)
	{
		ID3D11RenderTargetView* rTargets5[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Color1)]] };
		m_pDeviceContext->OMSetRenderTargets(1, rTargets5, nullptr);
		m_pLiquidJacobiIterMat->SetXVectorSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Color0)]]);
		m_pLiquidJacobiIterMat->SetBVectorSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Color0)]]);
		m_pLiquidJacobiIterMat->UpdateVariables();
		//m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidJacobiIterMat);
		//SwapColorRTBinding();
	}
	//diffuse pressure
	m_pLiquidJacobiIterMat->SetAlphaBetaConstants(1.f, 0.2f);
	for (int i = 0; i < 1; i++)
	{
		ID3D11RenderTargetView* rTargets5[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Pressure1)]] };
		m_pDeviceContext->OMSetRenderTargets(1, rTargets5, nullptr);
		m_pLiquidJacobiIterMat->SetXVectorSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Pressure0)]]);
		m_pLiquidJacobiIterMat->SetBVectorSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Pressure0)]]);
		m_pLiquidJacobiIterMat->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidJacobiIterMat);
		SwapPressureRTBinding();
	}

}
void LiquidRenderer::PressureProjection()
{


	//Advect Velocity Pass
	//This is done here because the advection causes the velocity to become divergent and thus needs to be corrected
	//	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Velocity1)]], clearColor);
	for (int i = 0; i <4; i++)
	{
		ID3D11RenderTargetView* rTargets4[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Velocity1)]] };
		m_pDeviceContext->OMSetRenderTargets(1, rTargets4, nullptr);
		m_pLiquidMatSim_Advect->SetSourceAdvectedQuantitySRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
		m_pLiquidMatSim_Advect->SetSourceAdvectionForceSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
		m_pLiquidMatSim_Advect->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidMatSim_Advect);
		SwapVelocityRTBinding();
	}
	//Compute Gradient 
	//m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Color1)]], clearColor);     
	ID3D11RenderTargetView* rTargets6[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Color1)]] };
	m_pDeviceContext->OMSetRenderTargets(1, rTargets6, nullptr);
	m_pLiquidDivergenceMat->SetSourceSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);

	m_pLiquidDivergenceMat->UpdateVariables();
	m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidDivergenceMat);
	//Compute Pressure
	m_pLiquidJacobiIterMat->SetAlphaBetaConstants(-1, 0.25);

	for (int i = 0; i < 44; i++)
	{
		ID3D11RenderTargetView* rTargets5[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Pressure1)]] };
		m_pDeviceContext->OMSetRenderTargets(1, rTargets5, nullptr);
		m_pLiquidJacobiIterMat->SetXVectorSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Pressure0)]]);
		m_pLiquidJacobiIterMat->SetBVectorSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Color1)]]);
		m_pLiquidJacobiIterMat->UpdateVariables();
		m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidJacobiIterMat);
		SwapPressureRTBinding();
	}


	//Project divergence

	ID3D11RenderTargetView* rTargets7[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Velocity1)]] };
	m_pDeviceContext->OMSetRenderTargets(1, rTargets7, nullptr);
	m_pLiquidProjectionMat->SetVelocitySRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
	m_pLiquidProjectionMat->SetPressureSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Pressure1)]]);
	m_pLiquidProjectionMat->UpdateVariables();
	m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidProjectionMat);

	SwapVelocityRTBinding();
}
void LiquidRenderer::BoundaryProjection()
{
	//Project divergence

	ID3D11RenderTargetView* rTargets7[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Velocity1)]] };
	m_pDeviceContext->OMSetRenderTargets(1, rTargets7, nullptr);
	m_pLiquidProjectionMat->SetVelocitySRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
	m_pLiquidProjectionMat->SetPressureSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Pressure1)]]);
	m_pLiquidProjectionMat->UpdateVariables();
	m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidProjectionMat);

	SwapVelocityRTBinding();
	//Velocity Boundary handling 
	ID3D11RenderTargetView* rTargets8[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Velocity1)]] };
	m_pDeviceContext->OMSetRenderTargets(1, rTargets8, nullptr);
	m_pLiquidBoundaryMat->SetSourceDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
	m_pLiquidBoundaryMat->SetSourceBoundarySRV(m_pShaderResourceViews2[m_pBufferIDs2[int(BufferIDs2::Boundary)]]);
	m_pLiquidBoundaryMat->SetIsPressure(-1);
	m_pLiquidBoundaryMat->UpdateVariables();
	m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidBoundaryMat);
	SwapVelocityRTBinding();

	ID3D11RenderTargetView* rTargets9[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Pressure1)]] };
	m_pDeviceContext->OMSetRenderTargets(1, rTargets9, nullptr);
	m_pLiquidBoundaryMat->SetSourceDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Pressure0)]]);
	m_pLiquidBoundaryMat->SetSourceBoundarySRV(m_pShaderResourceViews2[m_pBufferIDs2[int(BufferIDs2::Boundary)]]);
	m_pLiquidBoundaryMat->SetIsPressure(1);
	m_pLiquidBoundaryMat->UpdateVariables();
	m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidBoundaryMat);
	SwapPressureRTBinding();
}
void LiquidRenderer::Inflow()
{

	ID3D11RenderTargetView* rTargets[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]] };
	m_pDeviceContext->OMSetRenderTargets(1, rTargets, nullptr);
	m_pLiquidInflowMat->SetSourceInflowSRV(m_pShaderResourceViews2[m_pBufferIDs2[int(BufferIDs2::InflowVelocitySeed)]]);
	m_pLiquidInflowMat->UpdateVariables();
	m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidDrawInflowMat);


	rTargets[0] = m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Color0)]];
	m_pDeviceContext->OMSetRenderTargets(1, rTargets, nullptr);
	m_pLiquidInflowMat->SetSourceInflowSRV(m_pShaderResourceViews2[m_pBufferIDs2[int(BufferIDs2::InflowColorSeed)]]);
	m_pLiquidInflowMat->UpdateVariables();
	m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidInflowMat);

	rTargets[0] = m_pRenderTargetViews2[m_pBufferIDs2[int(BufferIDs2::Temperature)]];
	m_pDeviceContext->OMSetRenderTargets(1, rTargets, nullptr);
	m_pLiquidInflowMat->SetSourceInflowSRV(m_pShaderResourceViews2[m_pBufferIDs2[int(BufferIDs2::InflowTemperatureSeed)]]);
	m_pLiquidInflowMat->UpdateVariables();
	m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidInflowMat);

}
void LiquidRenderer::Advection()
{
	ID3D11RenderTargetView* rTargets3[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Color1)]] };
	m_pDeviceContext->OMSetRenderTargets(1, rTargets3, nullptr);
	m_pLiquidMatSim_Advect->SetSourceDiffuseSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::DiffuseInitial)]]);//todo remove
	m_pLiquidMatSim_Advect->SetSourceAdvectedQuantitySRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Color0)]]);
	m_pLiquidMatSim_Advect->SetSourceAdvectionForceSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
	m_pLiquidMatSim_Advect->UpdateVariables();
	m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidMatSim_Advect);
	SwapColorRTBinding();
	//m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Color0)]], clearColor);



	//Advect pressure Pass

	//	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Velocity1)]], clearColor);

	ID3D11RenderTargetView* rTargets4[1] = { m_pRenderTargetViews1[m_pBufferIDs1[int(BufferIDs::Pressure1)]] };
	m_pDeviceContext->OMSetRenderTargets(1, rTargets4, nullptr);
	m_pLiquidMatSim_Advect->SetSourceAdvectedQuantitySRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Pressure0)]]);
	m_pLiquidMatSim_Advect->SetSourceAdvectionForceSRV(m_pShaderResourceViews1[m_pBufferIDs1[int(BufferIDs::Velocity0)]]);
	m_pLiquidMatSim_Advect->UpdateVariables();
	m_pQuadDrawer->DrawImmediate(m_pDeviceContext, m_pLiquidMatSim_Advect);
	SwapPressureRTBinding();
}
void LiquidRenderer::CreateBufferAndView(int width, int height, DXGI_FORMAT format, ID3D11Texture2D** pBuffer,
	ID3D11RenderTargetView** outputRTV,
	ID3D11ShaderResourceView** outputSRV) const
{
	//TEXTURE BUFFER
	//**************
	D3D11_TEXTURE2D_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	//Create Descriptor
	bufferDesc.Width = width;
	bufferDesc.Height = height;
	bufferDesc.MipLevels = 1;
	bufferDesc.ArraySize = 1;
	bufferDesc.Format = format;
	bufferDesc.SampleDesc.Count = 1;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	//Create Resource
	auto hRes = m_pDevice->CreateTexture2D(&bufferDesc, nullptr, pBuffer);
	Logger::LogHResult(hRes, L"LiquidRenderer::CreateBuffer(...)"); //Blocking call on fail

																	//RENDER TARGET VIEW
																	//******************
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	ZeroMemory(&rtvDesc, sizeof(rtvDesc));

	//Create Descriptor
	rtvDesc.Format = format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	//Create Resource
	hRes = m_pDevice->CreateRenderTargetView(*pBuffer, &rtvDesc, outputRTV);
	Logger::LogHResult(hRes, L"LiquidRenderer::CreateBuffer(...)"); //Blocking call on fail

																	//SHADER RESOURCE VIEW
																	//********************
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));

	//Create Descriptor
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	hRes = m_pDevice->CreateShaderResourceView(*pBuffer, &srvDesc, outputSRV);
	Logger::LogHResult(hRes, L"LiquidRenderer::CreateBuffer(...)"); //Blocking call on fail
}

void LiquidRenderer::CreateDepthStencilBufferAndView(int width, int height)
{
	//Texture Buffer
	//**************
	D3D11_TEXTURE2D_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	//Create Descriptor
	bufferDesc.Width = width;
	bufferDesc.Height = height;
	bufferDesc.MipLevels = 1;
	bufferDesc.ArraySize = 1;
	bufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	bufferDesc.SampleDesc.Count = 1;
	bufferDesc.SampleDesc.Quality = 0;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	//Create Resource
	HRESULT hRes = m_pDevice->CreateTexture2D(&bufferDesc, nullptr, &m_pDepthStencilBuffer);
	Logger::LogHResult(hRes, L"LiquidRenderer::CreateDepthStencilBufferAndView(...)"); //Blocking call on fail


																					   //Depth Stencil View
																					   //******************
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	//Create Descriptor
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	//Create Resource
	hRes = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	Logger::LogHResult(hRes, L"LiquidRenderer::CreateDepthStencilBufferAndView(...)"); //Blocking call on fail
}

void LiquidRenderer::ClearRenderTargets(float r, float g, float b, float a)
{

	float clearColor[4] = { r, g, b, a };
	for (int i = 0; i < 1; i++)
	{
		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetViews1[i], clearColor);
	}
	/*
	for (auto & m_pRenderTargetView : m_pRenderTargetViews1)
	{
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	}
	*/
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void LiquidRenderer::SwapColorRTBinding()
{

	if (m_pIsColorSwitched)
	{
		m_pBufferIDs1[2] = 2;
		m_pBufferIDs1[5] = 5;
		m_pIsColorSwitched = false;
	}
	else
	{
		m_pBufferIDs1[2] = 5;
		m_pBufferIDs1[5] = 2;
		m_pIsColorSwitched = true;

	}


}
void LiquidRenderer::SwapPressureRTBinding()
{
	if (m_pIsPressureSwitched)
	{
		m_pBufferIDs1[3] = 3;
		m_pBufferIDs1[6] = 6;
		m_pIsPressureSwitched = false;
	}
	else
	{
		m_pBufferIDs1[3] = 6;
		m_pBufferIDs1[6] = 3;
		m_pIsPressureSwitched = true;
	}
	//m_pIsPressureSwitched = !m_pIsPressureSwitched;
}
void LiquidRenderer::SwapVelocityRTBinding()
{
	if (m_pIsVelocitySwitched)
	{
		m_pBufferIDs1[4] = 4;
		m_pBufferIDs1[7] = 7;
		m_pIsVelocitySwitched = false;
	}
	else
	{
		m_pBufferIDs1[4] = 7;
		m_pBufferIDs1[7] = 4;
		m_pIsVelocitySwitched = true;
	}
	//m_pIsVelocitySwitched = !m_pIsVelocitySwitched;
}
void LiquidRenderer::SwapRenderTargetBindings()
{

	if (m_pSwitchedRenderTargets)
	{
		m_pBufferIDs1[2] = 2;
		//m_pBufferIDs1[3] = 3;
		m_pBufferIDs1[4] = 4;
		m_pBufferIDs1[5] = 5;
		//m_pBufferIDs1[6] = 6;
		m_pBufferIDs1[7] = 7;
		m_pSwitchedRenderTargets = false;
	}
	else
	{
		m_pBufferIDs1[2] = 5;
		//m_pBufferIDs1[3] = 6;
		m_pBufferIDs1[4] = 7;
		m_pBufferIDs1[5] = 2;
		//m_pBufferIDs1[6] = 3;
		m_pBufferIDs1[7] = 4;
		m_pSwitchedRenderTargets = true;
	}

}