float3 gLightDirection = float3(-0.577f, -0.577f, 0.577f);

Texture2D gDiffuseMap;
Texture2D gAdvectionMap; 

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
float cubicPulse(float center, float width, float x)
{
	x = abs(x - center);
	if (x>width) return 0.0;
	x /= width;
	return 1.0 - x * x*(3.0 - 2.0*x);
}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_TARGET{


	float2 Velocity = gAdvectionMap.Sample(samLinear, input.texCoord);
	float vel = sqrt(pow(Velocity.x,2) + pow(Velocity.y,2)) ;
	float4 color = gDiffuseMap.Sample(samLinear, input.texCoord);
	float t = 1;  //treshhold

	if (vel < 0.001) return color;
	t = 1; 
/*
	if (vel < t)
	{
		color.r *= 1;
		color.g *= 0.5 + sin(20 * vel);
		color.b *= 1;
		return float4(color.xyz, 1);
	}
	if (vel < 0.5)
	{

		color.r *= 0.5 + sin(6 * vel);
		color.g *= 1;
		color.b *= 0.5 + sin(6 * vel);
		return float4(color.xyz, 1);
	}
	if (vel < 1)
	{
		color.r *= 1;
		color.g *= 1;
		color.b *= 0.5 + sin(2 * vel);

		return float4(color.xyz, 1);
	}
	if (vel <  15)
	{
		color.r *= sin( vel);
		color.g *= 1;
		color.b *= 1;
		return float4(color.xyz, 1);
	}
	return float4(color.xyz,1);
	

	if (abs(vel - 0.1) < 0.5)
	{
		color.r *= 1;
		color.g *= 0.5 + sin(20 * vel);
		color.b *= 1;
		return float4(color.xyz, 1);
	}
*/	
	
		color.r = color.r  + (0.5*cubicPulse(t*2, t*2, vel));
		color.g = color.g  +(0.2*cubicPulse(t/2, t*0.5, vel));
		color.b = color.b  + (0.2*cubicPulse(t * 8, t*8, vel)); ;
		return float4(color.xyz, 1);
	/*}
	
	t = 2;
	if (vel < t)
	{
		color.r = color.r * (1 + (cubicPulse(t / 2, t/2, vel)));
		color.g = color.g * (1 + (cubicPulse(t / 2, t/2, vel)));
		color.b *= 1;
		return float4(color.xyz, 1);
	}return float4(color.xyz, 1);*/
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