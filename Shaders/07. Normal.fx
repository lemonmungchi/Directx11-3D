matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;
//기본 월드좌표
float3 LightDir;

struct VertexInput
{
	float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
    output.position = mul(input.position,World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
	

    output.uv = input.uv;
    //회전고려
    output.normal = mul(input.normal, (float3x3) World);

	return output;
}

SamplerState Sampler0;


float4 PS(VertexOutput input) : SV_TARGET
{
    float3 normal = normalize(input.normal);
    float3 light = -LightDir;
    
    //내적
    //return float4(1, 1, 1, 1) * dot(light, normal);
    
	//텍스처 -> 샘플링된 좌표 
    return Texture0.Sample(Sampler0, input.uv) * dot(light, normal);
}

//와이어프레임모드
RasterizerState FillModeWireFrame
{
    FillMode = Wireframe;
};


technique11 T0
{
	//하나의 통로
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}

    pass P1
    {
        SetRasterizerState(FillModeWireFrame);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};
