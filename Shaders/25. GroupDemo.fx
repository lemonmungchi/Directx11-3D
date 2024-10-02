
ByteAddressBuffer Input;    // SRV
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
    //2차원 배열에서 유니크한 인덱스 계산 몇번째인지 2차원 -> 1차원
    uint index = input.groupID.x * (10 * 8 * 3) + input.groupIndex;
    //10(3+3+3+1+1) : 구조체 크기, 4: 바이트
    uint outAddress = index * 11 * 4;
    
    //데이터 : 4바이트 * 몇번째인지
    uint inAddress = index * 4;
    float value = (float)Input.Load(inAddress);
    
    //구조체에서 각 변수가 떨어진 정도
    Output.Store3(outAddress + 0, input.groupID);
    Output.Store3(outAddress + 12, input.groupThreadID);
    Output.Store3(outAddress + 24, input.dispatchThreadID);
    Output.Store(outAddress + 36, input.groupIndex);
    Output.Store(outAddress + 40, (uint)value);
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
