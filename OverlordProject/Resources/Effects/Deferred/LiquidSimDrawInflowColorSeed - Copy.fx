float4x4 gWorld : WORLD;
float4x4 gWorldViewProj : WORLDVIEWPROJECTION;
float3 gLightDirection = float3(-0.577f, -0.577f, 0.577f);
int gScreenRes = 1024;
Texture2D gDiffuseMap;
float gTimeStep;
float3 gColor; 

float gXpos;
float gYpos;
float gXvel;
float gYvel;
float gStrength = 0.33;
float gSize;
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

struct VS_INPUT {
	float3 pos : POSITION;
	//float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT {
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
VS_OUTPUT VS(VS_INPUT input) {

	/*
	VS_OUTPUT output;
	// Step 1:	convert position into float4 and multiply with matWorldViewProj
	output.pos = mul ( float4(input.pos,1.0f), gWorldViewProj );
	// Step 2:	rotate the normal: NO TRANSLATION
	//			this is achieved by clipping the 4x4 to a 3x3 matrix,
	//			thus removing the postion row of the matrix
	output.normal = normalize(mul(input.normal, (float3x3)gWorld));
	output.texCoord = input.texCoord;
	return output;
	*/
	VS_OUTPUT output;

	output.pos = float4(input.pos, 1.0f);
	output.texCoord = input.texCoord;
	//output.normal = input.normal; 
	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
PS_OUTPUT PS(VS_OUTPUT input) : SV_TARGET{

	PS_OUTPUT output = (PS_OUTPUT)0;


	//output.color = float4(vel.x, vel.y, 0, 1);
	float distx = (gXpos / 1024) - input.texCoord.x;
	float disty = (gYpos / 1024) - input.texCoord.y;
	float distance = sqrt((distx * distx) + (disty * disty));
	//if (abs(gXvel + gYvel) < 1) discard;
	if (distance < gSize)
	{
		output.color = float4(gColor.x , gColor.y, gColor.z, 1);
		//output.color = float4(0.77, 0.33, 0, 1);
	}
	else
	{
		discard;
	}


//output.color = float4(distance  , 0, 0, 1);
//output.normal = float4(avg, avg, avg, output.color.a);
//output.normal = float4(1.0f, 0.4f, 0.0f, 1.0f);
//output.specular = float4(1.0f, 0.4f, 0.0f, 1.0f);
//output.light_accumulation = float4(0.0f, 1.0f, 0.0f, 1.0f);
//output.color = float4(0, 1, 0, 1);
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

		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS()));
	}
}

