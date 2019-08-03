float3 gLightDirection = float3(-0.577f, -0.577f, 0.577f);

Texture2D gTextureDiffuse;
Texture2D gTextureNormal;

texture2D gTextureVelocity; 
texture2D gTexturePressure; 
texture2D gTextureColor; 

texture2D gTextureVelocity2;
texture2D gTexturePressure2;
texture2D gTextureColor2;
SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Wrap;// or Mirror or Clamp or Border
    AddressV = Wrap;// or Mirror or Clamp or Border
};

RasterizerState Solid
{
	FillMode = SOLID;
	CullMode = FRONT;
};
RasterizerState NoCulling
{
	CullMode = NONE;
};


struct VS_INPUT{
	float3 pos : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT{
	float4 pos : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

DepthStencilState DisableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
};
struct PS_OUTPUT
{
	float4 color : SV_TARGET0;
};
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input){

	VS_OUTPUT output;

	output.pos = float4(input.pos,1.0f);
	output.texCoord = input.texCoord;

	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_TARGET0{
	PS_OUTPUT output = (PS_OUTPUT)0;
	float4 normal = gTextureNormal.Sample(samPoint, input.texCoord);
	//clip(normal.w-0.1f);

	float3 diffuse = gTextureDiffuse.Sample(samPoint, input.texCoord).xyz;
	float diffuseStrength = dot(normal.xyz, -gLightDirection);
	diffuseStrength = diffuseStrength * 0.5 + 0.5;
	diffuseStrength = saturate(diffuseStrength);


	output.color = float4(0, 1, 0.5, 1); 
	//return float4(diffuse * diffuseStrength, 1.0f);
	return float4(0, 1, 0.5, 1);
	//return float4(0, 1, 0.5, 0.5);
}

//--------------------------------------------------------------------------------------
// Technique
//--------------------------------------------------------------------------------------
technique11 Default
{
    pass P0
    {
		SetRasterizerState(NoCulling);
		SetDepthStencilState(DisableDepth, 0);

		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}

