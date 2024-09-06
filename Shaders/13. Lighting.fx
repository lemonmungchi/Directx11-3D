#include "00. Global.fx"
#include "00. Light.fx"


MeshOutput  VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position,W);
    output.worldPosition = output.position.xyz;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    //회전고려
    output.normal = mul(input.normal, (float3x3) W);

	return output;
}




float4 PS(MeshOutput input) : SV_TARGET
{
    float color = ComputeLight(input.normal, input.uv, input.worldPosition);
    
    return color;
}

technique11 T0
{
	//하나의 통로
    PASS_VP(P0, VS, PS)
};
