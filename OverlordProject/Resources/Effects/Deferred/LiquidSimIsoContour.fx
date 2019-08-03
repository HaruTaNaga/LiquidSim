float3 gLightDirection = float3(-0.577f, -0.577f, 0.577f);

Texture2D gDiffuseMap;

SamplerState samPoint
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = Wrap;// or Mirror or Clamp or Border
	AddressV = Wrap;// or Mirror or Clamp or Border
};
SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;// or Mirror or Clamp or Border
	AddressV = Wrap;// or Mirror or Clamp or Border
};

RasterizerState Solid
{
	FillMode = SOLID;
	CullMode = BACK;
};

struct VS_INPUT {
	float3 pos : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT {
	float4 pos : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

DepthStencilState DisableDepth
{
	DepthEnable = FALSE;
	DepthWriteMask = ZERO;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input) {

	VS_OUTPUT output;

	output.pos = float4(input.pos, 1.0f);
	output.texCoord = input.texCoord;

	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_TARGET{

	float4 color = gDiffuseMap.Sample(samLinear, input.texCoord);
	float distance = 512.0f; 
	float distancemodulo = abs(color.r)% distance; 
	float alpha = 1; 
	float s = 0.7; 

	if ((fmod((color.r), distance)) < 0) {
		//s =  ( 0.6 *(distancemodulo / 512));
		s = 0.5; 
	}

	float4 output = { 0.8* s * (distancemodulo / 240), 0.3* s * (distancemodulo / 240), 0.05*s * (distancemodulo / 240),1 };


	if (distancemodulo< 10)
	{

		output = float4(0.05 * s * (distancemodulo / 10), 0.2 * s * (distancemodulo / 10), 0.05 * s * (distancemodulo / 10), alpha);
		return output;
	}
	s = s - 0.025;
	if (distancemodulo < 20)
	{

		output = float4(0.08*s * (distancemodulo / 20), 0.4*s * (distancemodulo / 20), 0.1*s * (distancemodulo / 20), alpha);
		return output;
	}
	s = s - 0.025;
	if (distancemodulo < 40)
	{
		output = float4(0.2* s * (distancemodulo / 40), 0.6 * s * (distancemodulo / 40), 0.15 * s * (distancemodulo / 40), alpha);
		return output;
	}
	s = s - 0.05;
	if (distancemodulo < 80)
	{

		output = float4(0.4* s * (distancemodulo / 80), 0.7 * s * (distancemodulo / 80), 0.25 * s * (distancemodulo / 80), alpha);
		return output;
	}
	s = s - 0.05;
	if (distancemodulo< 150)
	{
		output = float4(0.55 *s * (distancemodulo / 150), 0.7 * s * (distancemodulo / 150), 0.08 *s * (distancemodulo / 150), alpha);
		return output;

	}
	s = s - 0.05;
	if (distancemodulo < 240)
	{
		output = float4(0.8 * s * (distancemodulo / 240), 0.8 * s * (distancemodulo / 240), 0.08 * s * (distancemodulo / 240), alpha);
		return output;
	}
	s = s - 0.05;
	if (distancemodulo < 330)
	{
		output = float4(0.85* s * (distancemodulo / 330), 0.35* s * (distancemodulo / 200), 0.05*s * (distancemodulo / 330), alpha);
		return output;
	}
	s = s - 0.05;
	if (distancemodulo < 420)
	{
		output = float4(0.9* s * (distancemodulo / 420), 0.2* s * (distancemodulo / 420), 0.07*s * (distancemodulo / 420), 1);
		return output;
	}
	output = float4(0.7* s * (distancemodulo / 512), 0.3* s * (distancemodulo / 512), 0.03*s * (distancemodulo / 512), alpha);

	
	if ((fmod((color.r), distance)) < 0) {
		//output.rg *=  pow((24 - (distancemodulo)/24),15);
	}
		//output.b = 0.4 * (1 - (distancemodulo / 16));
	return output;
}

//--------------------------------------------------------------------------------------
// Technique
//--------------------------------------------------------------------------------------
technique11 Default
{
	pass P0
	{
		SetRasterizerState(Solid);
		SetDepthStencilState(DisableDepth, 0);

		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS()));
	}
}



/*
float4 color = gDiffuseMap.Sample(samLinear, input.texCoord);
if ((abs(color.r) % 2) < 0.0005)
color = float4(0.9, 0.4, 0.0, 0.7);
if (abs(color.r) < 0.0001)
color = float4(1, 1, 1, 1);


return color;*/