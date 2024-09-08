#ifndef _GLOBAL_FX_
#define _GLOBAL_FX_

/////////////////
// ConstBuffer //
/////////////////

cbuffer GlobalBuffer
{
    matrix V;
    matrix P;
    matrix VP;
    matrix VInv;
};

cbuffer TransformBuffer
{
    matrix W;
};

/////////////////
// VertexBuffer //
/////////////////

struct Vertex
{
    float4 position : POSITION;
};

struct VertexTexture
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexColor
{
    float4 Position : POSITION;
    float4 Color : COLOR;
};

struct VertexTextureNormal
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VertexTextureNormalTangent
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

/////////////////
// Vertexoutput //
/////////////////

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct MeshOutput
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

/////////////////
// SamplerState //
/////////////////

SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState PointSampler
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Wrap;
    AddressV = Wrap;
};

/////////////////////
// RasterizerState //
/////////////////////

//와이어프레임모드
RasterizerState FillModeWireFrame
{
    FillMode = Wireframe;
};

///////////
// Macro //
////////////

#define PASS_VP(name, vs, ps)                       \
pass name                                           \
{                                                   \
	SetVertexShader(CompileShader(vs_5_0, vs()));   \
	SetPixelShader(CompileShader(ps_5_0, ps()));    \
}                  


//////////////
// Function //
//////////////

float3 CameraPosition()
{
    return VInv._41_42_43;

}
#endif

