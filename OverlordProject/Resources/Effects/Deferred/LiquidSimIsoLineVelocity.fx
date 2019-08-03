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
	

	float distance = 512.0f * (abs(color.r) + abs(color.g));

	float alpha = 1; 
	float s = 0.7; 

	if ((fmod((color.r), distance)) < 0) {
		//s =  ( 0.6 *(distance / 512));
		//s = 0.5; 
	}
	float4 output = { 0,0,0,1 }; 
	//float4 output = { 0.8* s * (distance / 240), 0.3* s * (distance / 240), 0.05*s * (distance / 240),1 };

	float thickness = 2; 
	if (abs(distance - 10)< 0.1*thickness)
	{
	
		output = float4(0.025 * s * (distance /10), 0.1 * s * (distance / 10), 0.025 * s * (distance / 10), alpha);
		return output;
	}
	s = s - 0.025; 
	if (abs(distance - 20)< .15*thickness)
	{

		output = float4(0.08*s * (distance / 20), 0.3*s * (distance / 20), 0.1*s * (distance / 20), alpha);
		return output;
	}
	s = s - 0.025;
	if (abs(distance - 40)< .2*thickness)
	{
		output = float4(0.2* s * (distance / 40), 0.7 * s * (distance / 40), 0.15 * s * (distance / 40), alpha);
		return output;
	}

	if (abs(distance - 60)< .4*thickness)
	{
		output = float4(0.2* s * (distance / 60), 0.9 * s * (distance / 60), 0.15 * s * (distance / 60), alpha);
		return output;
	}
	s = s - 0.05;
	if (abs(distance - 80)< .8*thickness)
	{
		
		output = float4(0.4* s * (distance / 80), 0.7 * s * (distance / 80), 0.25 * s * (distance / 80), alpha);
		return output;
	}
	s = s - 0.05;
	if (abs(distance - 150)< 1.5*thickness)
	{
		output = float4(0.55 *s * (distance / 150), 0.7 * s * (distance / 150), 0.08 *s * (distance / 150), alpha);
		return output;
	
	}
	s = s - 0.05;
	if (abs(distance - 240)< 2.4* thickness)
	{
		output = float4(0.8 * s * (distance / 240), 0.8 * s * (distance / 240), 0.08 * s * (distance / 240), alpha);
		return output;
	}
	s = s - 0.05;
	if (abs(distance - 330)< 3.3*thickness)
	{
		output = float4(0.85* s * (distance / 330), 0.35* s * (distance / 200), 0.05*s * (distance / 330), alpha);
		return output;
	}
	s = s - 0.05;
	if (abs(distance - 420)< 4.2*thickness)
	{
		output = float4(0.9* s * (distance / 420), 0.2* s * (distance / 420), 0.07*s * (distance / 420), 1);
		return output;
	}
	if (abs(distance - 840)< 8.4*thickness)
	{
		output = float4(0.9* s * (distance / 840), 0.2* s * (distance / 840), 0.07*s * (distance / 840), 1);
		return output;
	}
	//output = float4(0.7* s * (distance / 512), 0.3* s * (distance / 512), 0.03*s * (distance / 512), alpha);

	
	if ((fmod((color.r), distance)) < 0) {
		//output.rg *=  pow((24 - (distance)/24),15);
	}
		//output.b = 0.4 * (1 - (distance / 16));
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