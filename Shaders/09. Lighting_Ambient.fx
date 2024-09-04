#include "00. Global.fx"

//광원자체의 색상
float4 LightAmbient;
//물체 재질 색상- 빛을 얼마나 받아들이는지   
float4 MaterialAmbient;

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

Texture2D Texture0;

// Ambient (주변광 / 환경광)
// 일정한 밝기와 색
// 수많은 반사 - 불분명한 광원

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = LightAmbient * MaterialAmbient;
	//텍스처 -> 샘플링된 좌표 
    //return color;
    return Texture0.Sample(LinearSampler, input.uv) * color;
}

technique11 T0
{
	//하나의 통로
    PASS_VP(P0, VS, PS)
};
