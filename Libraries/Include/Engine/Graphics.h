#pragma once


//그려지는 것에 필요한 것들
class Graphics
{
	DECLARE_SINGLE(Graphics);

public:
	void Init(HWND hwnd);

	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void CreateDepthStencilView();
	void SetViewport();

private:
	HWND _hwnd = {};

	// Device & SwapChain
	//물체를 생성 및 바인딩
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	ComPtr<IDXGISwapChain> _swapChain = nullptr;

	// RTV - 쉐이더에서 계산한거 그려주기
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	// DSC- 깊이 
	ComPtr<ID3D11Texture2D> _depthStencilTexture;
	ComPtr<ID3D11DepthStencilView> _depthStencilView;


	// Misc
	D3D11_VIEWPORT _viewport = { 0 };
};

