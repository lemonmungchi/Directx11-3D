
//RGBA
Texture2DArray<float4> Input;
RWTexture2DArray<float4> Output;

//thread 개수 a*b*c 총합 
[numthreads(32,32,1)]       //2차원
void CS(uint3 id : SV_DispatchThreadID)
{
    float4 color = Input.Load(int4(id, 0));     //쓰레드 넘버링값에 해당하는 정보 추출
    
    //Output[id] = color;
    Output[id] = 1.0f - color;      //반전 
    //Output[id] = (color.r + color.g + color.b) / 3.0f;        //회색풍
}


technique11 T0
{
    Pass P0
    {
        SetVertexShader(NULL);
        SetPixelShader(NULL);
        //컴퓨트 쉐이더 세팅
        SetComputeShader(CompileShader(cs_5_0, CS()));
    }
};
