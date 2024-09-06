#ifndef _LIGHT_FX_
#define _LIGHT_FX_

#include "00. Global.fx"

////////////
// struct //
///////////

struct LightDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
    float3 direction;
    float padding;      //16바이트 정렬
};

struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
};

/////////////////
// ConstBuffer //
////////////////

cbuffer LightBuffer
{
    LightDesc GlobalLight;
};

cbuffer MaterialBuffer
{
    MaterialDesc Material;
};

//////////
// SRV //
/////////

Texture2D DiffuseMap;
Texture2D SpecularMap;
Texture2D NormalMap;

///////////////
// Function //
//////////////

float4 ComputeLight(float3 normal,float2 uv,float3 worldPosition)
{
    float4 ambientColor = 0;
    float4 diffuseColor = 0;
    float4 specularColor = 0;
    float4 emissiveColor = 0;
    
    //Ambient - 주변광
    {
        float4 color = GlobalLight.ambient * Material.ambient;
        ambientColor = DiffuseMap.Sample(LinearSampler, uv) * color;
    }
    //Diffuse - 반사광
    {
        float4 color = DiffuseMap.Sample(LinearSampler, uv);
        //람베르트
        float value = dot(-GlobalLight.direction, normalize(normal));
        diffuseColor = color * value * GlobalLight.diffuse * Material.diffuse;
    }
    //Specular  - 광원효과
    {
        //float3 R = reflect(LightDir, normal);
        float3 R = GlobalLight.direction - (2 * normal * dot(GlobalLight.direction, normal));
        R = normalize(R);
    
        float3 cameraPosition = CameraPosition(); //마지막행
        float3 E = normalize(cameraPosition - worldPosition);       //물체-카메라
    
        float value = saturate(dot(R, E)); //clmap 0~1
        float specular = pow(value, 10);
    
        specularColor = GlobalLight.specular * Material.specular * specular;
    }
    //Emissive  - 외곽선
    {
        float3 cameraPosition = CameraPosition();
        //카메라로 가는 방향
        float3 E = normalize(cameraPosition - worldPosition);
    
        float value = saturate(dot(E, normal)); //0~1
        float emissive = 1.0f - value;          //1~0
    
        //점차 증가
        emissive = smoothstep(0.0f, 1.0f, emissive);
        emissive = pow(emissive, 2);
    
        emissiveColor = GlobalLight.emissive * Material.emissive * emissive;
    }
    
    return ambientColor + diffuseColor + specularColor + emissiveColor;
}

#endif

