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
	float4 color = float4(0, 0, 0, 1);
	float t = 1;  //treshhold

	if (vel < 0.00001) return float4(0,0,0,1);
	t = 1; 
	color.b += (0.20*cubicPulse(t / 16, t*0.065, vel));
	color.b += (0.15*cubicPulse(t / 8, t*0.125, vel));
	color.g += (0.10*cubicPulse(t / 8, t*0.125, vel));
	color.g +=(0.3*cubicPulse(t/4, t*0.25, vel));
	color.r += (0.7*cubicPulse(t * 2, t * 2, vel));
	color.g += (0.7*cubicPulse(t * 1, t*1, vel));
	color.r += (0.8*cubicPulse(t * 1, t * 1, vel));
	float res = 1024; 
	color.b += (0.35*cubicPulse(res * t / 16, res * t*0.065, vel));
	color.g += (0.3*cubicPulse(res * t / 4, res *  t*0.25, vel));
	color.r += (0.7*cubicPulse(res * t * 2, res * t * 2, vel));
	color.g += (0.7*cubicPulse(res * t * 1, res * t * 1, vel));
	color.r += (0.8*cubicPulse(res * t * 1, res * t * 1, vel));

	return float4(color.xyz, 1);

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