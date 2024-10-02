
struct InputDesc
{
    matrix input;
};

struct OutputDesc
{
    matrix result;
};

//하나의 배열로 보면된다
StructuredBuffer<InputDesc> Input;
RWStructuredBuffer<OutputDesc> Output;

//thread 개수 x*y*z 총합 
[numthreads(500,1,1)]       //x만 500개 행렬값
void CS(uint id : SV_GroupIndex)
{
    matrix result = Input[id].input * 2;
    
    Output[id].result = result;
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
