#pragma once


class RawBuffer
{
public:
	RawBuffer(void* inputData, uint32 inputByte, uint32 outputByte);
	~RawBuffer();

public:
	void CreateBuffer();
	//입력값 넣어주기
	void CopyToInput(void* data);
	//결과값 가져오기
	void CopyFromOutput(void* data);

public:
	ComPtr<ID3D11ShaderResourceView> GetSRV() { return _srv; }
	ComPtr<ID3D11UnorderedAccessView> GetUAV() { return _uav; }

private:
	//버퍼만들기
	void CreateInput();
	//입력 SRV만들기
	void CreateSRV();
	//결과가져올버퍼 만들기
	void CreateOutput();
	//결과 가져올 UAV
	void CreateUAV();
	//결과값 취합 및 복사
	void CreateResult();

private:
	ComPtr<ID3D11Buffer> _input;
	ComPtr<ID3D11ShaderResourceView> _srv;
	ComPtr<ID3D11Buffer> _output;
	ComPtr<ID3D11UnorderedAccessView> _uav;
	//결과값을 복사해올 버퍼
	ComPtr<ID3D11Buffer> _result;
private:
	void* _inputData;
	uint32 _inputByte = 0;
	uint32 _outputByte = 0;
};

