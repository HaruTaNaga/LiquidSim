float4x4 gWorld : WORLD;
float4x4 gWorldViewProj : WORLDVIEWPROJECTION; 
float3 gLightDirection = float3(-0.577f, -0.577f, 0.577f);

Texture2D gDiffuseMap;
float gTimeStep;
Texture2D gAdvectionForceMap;
Texture2D gAdvectedQuantityMap;
SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
    //Filter = MIN_MAG_MIP_POINT;
	//Filter = ANISOTROPIC; 
    AddressU = Clamp;// or Mirror or Clamp or Border
    AddressV = Clamp;// or Mirror or Clamp or Border
};

RasterizerState Solid
{
	FillMode = SOLID;
	CullMode = FRONT;
};

struct VS_INPUT{
	float3 pos : POSITION;
	//float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT{
	float4 pos : SV_POSITION;
	//float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct PS_OUTPUT
{
	float4 color : SV_TARGET0;
//	float4 normal : SV_TARGET1;
//	float4 specular : SV_TARGET2;
//	float4 light_accumulation : SV_TARGET3;
	
};


DepthStencilState EnableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
};

RasterizerState NoCulling
{
	CullMode = NONE;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input){


	VS_OUTPUT output;

	output.pos = float4(input.pos, 1.0f);
	output.texCoord = input.texCoord;
 
	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
PS_OUTPUT PS(VS_OUTPUT input) : SV_TARGET{

	PS_OUTPUT output = (PS_OUTPUT)0;
    float2 vel = gAdvectionForceMap.Sample(samLinear, input.texCoord).xy;
	float2 coords = input.texCoord - (vel.xy / 1024 * gTimeStep);
	output.color = gAdvectedQuantityMap.Sample(samLinear, coords);
	return output;
}

//--------------------------------------------------------------------------------------
// Technique
//--------------------------------------------------------------------------------------
technique11 Default
{
    pass P0
    {
		SetRasterizerState(NoCulling);
		SetDepthStencilState(EnableDepth, 0);

		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}

