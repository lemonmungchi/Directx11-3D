#include "00. Global.fx"


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

float4 PS(VertexOutput input) : SV_TARGET
{
    //내적
    //return float4(1, 1, 1, 1) * dot(light, normal);
	//텍스처 -> 샘플링된 좌표 
    return Texture0.Sample(LinearSampler, input.uv);
}

technique11 T0
{
	//하나의 통로
    PASS_VP(P0, VS, PS)
};
