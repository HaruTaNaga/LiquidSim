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
	float distance = 4096.0f; 

	float distancemodulo =(abs(color.r))% distance;

	float alpha = 1; 
	float s = 0.7; 

	if ((fmod((color.r), distance)) < 0) {
		//s =  ( 0.6 *(distancemodulo / 512));
		//s = 0.5; 
	}
	float4 output = { 0,0,0,1 }; 
	//float4 output = { 0.8* s * (distancemodulo / 240), 0.3* s * (distancemodulo / 240), 0.05*s * (distancemodulo / 240),1 };

	float thickness = 2; 
	if (abs(distancemodulo - 10)< 0.1*thickness)
	{
	
		output = float4(0.025 * s * (distancemodulo /10), 0.1 * s * (distancemodulo / 10), 0.025 * s * (distancemodulo / 10), alpha);
		return output;
	}
	s = s - 0.025; 
	if (abs(distancemodulo - 20)< .15*thickness)
	{

		output = float4(0.08*s * (distancemodulo / 20), 0.3*s * (distancemodulo / 20), 0.1*s * (distancemodulo / 20), alpha);
		return output;
	}
	s = s - 0.025;
	if (abs(distancemodulo - 40)< .2*thickness)
	{
		output = float4(0.2* s * (distancemodulo / 40), 0.7 * s * (distancemodulo / 40), 0.15 * s * (distancemodulo / 40), alpha);
		return output;
	}

	if (abs(distancemodulo - 60)< .4*thickness)
	{
		output = float4(0.2* s * (distancemodulo / 60), 0.9 * s * (distancemodulo / 60), 0.15 * s * (distancemodulo / 60), alpha);
		return output;
	}
	s = s - 0.05;
	if (abs(distancemodulo - 80)< .8*thickness)
	{
		
		output = float4(0.4* s * (distancemodulo / 80), 0.7 * s * (distancemodulo / 80), 0.25 * s * (distancemodulo / 80), alpha);
		return output;
	}
	s = s - 0.05;
	if (abs(distancemodulo - 150)< 1.5*thickness)
	{
		output = float4(0.55 *s * (distancemodulo / 150), 0.7 * s * (distancemodulo / 150), 0.08 *s * (distancemodulo / 150), alpha);
		return output;
	
	}
	s = s - 0.05;
	if (abs(distancemodulo - 240)< 2.4* thickness)
	{
		output = float4(0.8 * s * (distancemodulo / 240), 0.8 * s * (distancemodulo / 240), 0.08 * s * (distancemodulo / 240), alpha);
		return output;
	}
	s = s - 0.05;
	if (abs(distancemodulo - 330)< 3.3*thickness)
	{
		output = float4(0.85* s * (distancemodulo / 330), 0.35* s * (distancemodulo / 200), 0.05*s * (distancemodulo / 330), alpha);
		return output;
	}
	s = s - 0.05;
	if (abs(distancemodulo - 420)< 4.2*thickness)
	{
		output = float4(0.9* s * (distancemodulo / 420), 0.2* s * (distancemodulo / 420), 0.07*s * (distancemodulo / 420), 1);
		return output;
	}
	if (abs(distancemodulo - 840)< 8.4*thickness)
	{
		output = float4(0.9* s * (distancemodulo / 840), 0.2* s * (distancemodulo / 840), 0.07*s * (distancemodulo / 840), 1);
		return output;
	}
	//output = float4(0.7* s * (distancemodulo / 512), 0.3* s * (distancemodulo / 512), 0.03*s * (distancemodulo / 512), alpha);

	
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