#include "00. Global.fx"

float3 LightDir;
float4 LightSpecular;
float4 MaterialSpecular;

Texture2D DiffuseMap;

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



//Specular 반사광
// 한방향으로 완전히 반사되는 빛- 퐁

float4 PS(MeshOutput input) : SV_TARGET
{
    //내장함수 방식
    //float3 R = reflect(LightDir, input.normal);
    //수학식 방식
    float3 R = LightDir - (2 * input.normal * dot(LightDir, input.normal));
    R = normalize(R);
    
    float3 cameraPosition = -V._41_42_43;       //마지막행
    float3 E = normalize(cameraPosition - input.worldPosition);
    
    float value = saturate(dot(R, E));      //clmap 0~1
    float specular = pow(value, 10);
    
  
    float4 color = LightSpecular * MaterialSpecular * specular;
    
    return color;
}

technique11 T0
{
	//하나의 통로
    PASS_VP(P0, VS, PS)
};
