#include "00. Global.fx"

float3 LightDir;
//광원색
float4 LightDiffuse;
//물체 재질 색상- 빛을 얼마나 받아들이는지 
float4 MaterialDiffuse;
Texture2D DiffuseMap;

VertexOutput VS(VertexTextureNormal input)
{
	VertexOutput output;
    output.position = mul(input.position,W);
    output.position = mul(output.position, VP);
	
    output.uv = input.uv;
    //회전고려
    output.normal = mul(input.normal, (float3x3) W);

	return output;
}



//Diffuse - 분산광

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    
    //람베르트
    float value = dot(-LightDir, normalize(input.normal));
    color = color * value * LightDiffuse * MaterialDiffuse;
    
    return color;
}

technique11 T0
{
	//하나의 통로
    PASS_VP(P0, VS, PS)
};
