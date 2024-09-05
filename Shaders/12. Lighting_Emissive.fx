#include "00. Global.fx"


float4 MaterialEmissive;


MeshOutput  VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position,W);
    output.worldPosition = output.position;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    //회전고려
    output.normal = mul(input.normal, (float3x3) W);

	return output;
}



//Emissive - 림라이트
// 외곽선 구할 때 사용

float4 PS(MeshOutput input) : SV_TARGET
{
    float3 cameraPosition = -V._41_42_43;
    //카메라로 가는 방향
    float3 E = normalize(cameraPosition - input.worldPosition);
    
    float value = saturate(dot(E, input.normal));
    float emissive = 1.0f - value;
    
    //점차 증가
    emissive = smoothstep(0.0f, 1.0f, emissive);
    
    float4 color = MaterialEmissive * emissive;
    
    return color;
}

technique11 T0
{
	//하나의 통로
    PASS_VP(P0, VS, PS)
};
