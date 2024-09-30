
//Read + Write
RWByteAddressBuffer Output; // -> UAV

struct ComputeInput
{
    //SV: system Value 지정되어 있는 시스템 벨류
    uint3 groupID : SV_GroupID;
    uint3 groupThreadID : SV_GroupThreadID;
    uint3 dispatchThreadID : SV_DispatchThreadID;
    uint groupIndex : SV_GroupIndex;
};

//thread 개수 a*b*c 총합
[numthreads(10,8,3)]
void CS(ComputeInput input)
{
    uint index = input.groupIndex;
    //10(3+3+3+1) : 구조체 크기, 4: 바이트
    uint outAddress = index * 10 * 4;
    
    
    //구조체에서 각 변수가 떨어진 정도
    Output.Store3(outAddress + 0, input.groupID);
    Output.Store3(outAddress + 12, input.groupThreadID);
    Output.Store3(outAddress + 24, input.dispatchThreadID);
    Output.Store3(outAddress + 36, input.groupIndex);
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
