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
	float scale = 2; 
	float distance = scale * 1024;

	float distancemodulo = (distance*(abs(color.r) + abs(color.g)))% distance;
	
	float alpha = 1; 
	float s = 0.85; 
	float4 output = { .55,.17,.06,1 };
	if ((distance*(abs(color.r) + abs(color.g))) / distance > 1) 	return output;
	if (distancemodulo< scale * 10)
	{
	
		output = float4(0.05 * s * (distancemodulo /(scale * 10)), 0.2 * s * (distancemodulo / (scale * 10)), 0.05 * s * (distancemodulo / (scale * 10)), alpha);
		return output;
	}
	//s = s - 0.025; 
	if (distancemodulo < (scale * 20))
	{

		output = float4(0.08*s * (distancemodulo / (scale * 20)), 0.4*s * (distancemodulo / (scale * 20)), 0.1*s * (distancemodulo / (scale * 20)), alpha);
		return output;
	}
	//s = s - 0.025;
	if (distancemodulo <(scale * 40))
	{
		output = float4(0.2* s * (distancemodulo / (scale * 40)), 0.6 * s * (distancemodulo / (scale * 40)), 0.15 * s * (distancemodulo / (scale * 40)), alpha);
		return output;
	}
	//s = s - 0.05;
	if (distancemodulo < scale * 80)
	{
		
		output = float4(0.4* s * (distancemodulo / (scale * 80)), 0.7 * s * (distancemodulo / (scale * 80)), 0.25 * s * (distancemodulo / (scale * 80)), alpha);
		return output;
	}
	//s = s - 0.05;
	if (distancemodulo< scale * 150)
	{
		output = float4(0.55 *s * (distancemodulo / (scale * 150)), 0.7 * s * (distancemodulo / (scale * 150)), 0.08 *s * (distancemodulo / (scale * 150)), alpha);
		return output;
	
	}

	if (distancemodulo < scale * 240)
	{
		output = float4(0.8 * s * (distancemodulo / (scale * 240)), 0.8 * s * (distancemodulo / (scale * 240)), 0.08 * s * (distancemodulo / (scale * 240)), alpha);
		return output;
	}

	if (distancemodulo < scale * 330)
	{
		output = float4(0.85* s * (distancemodulo / (scale * 330)), 0.35* s * (distancemodulo / (scale * 330)), 0.05*s * (distancemodulo / (scale * 330)), alpha);
		return output;
	}

	if (distancemodulo < scale * 420)
	{
		output = float4(0.9* s * (distancemodulo / (scale * 420)), 0.2* s * (distancemodulo / (scale * 420)), 0.07*s * (distancemodulo / (scale * 420)), 1);
		return output;
	}
	scale *= 2; 
	if (distancemodulo < scale * 512)
	{
		output = float4(0.9* s * (distancemodulo / (scale * 512)), 0.2* s * (distancemodulo / (scale * 512)), 0.07*s * (distancemodulo / (scale * 512)), 1);
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