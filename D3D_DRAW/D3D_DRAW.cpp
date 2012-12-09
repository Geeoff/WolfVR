//
// Wolfenstein VR
//
// D3D_DRAW.CPP created by Geoff Cagle.
// This is our D3D Renderer.
//
extern "C"
{
	#include "D3D_DRAW.h"
}

#include "ComPtr.h"
#include <cassert>
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")

namespace
{
	// device and context
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceCtx;
	D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL) 0;

	// render target
	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<ID3D11Texture2D> depthStencilTex;
	ComPtr<ID3D11RenderTargetView> renderTargView;
	ComPtr<ID3D11DepthStencilView> depthStencilView;

	// viewport
	D3D11_VIEWPORT viewPort = {0};

	// helper methods
	inline ComPtr<IDXGIFactory> GetFactory( )
	{
		ComPtr<IDXGIDevice> giDevice;
		HRESULT hr = device.QueryInterface( giDevice );
		assert( SUCCEEDED(hr) );

		ComPtr<IDXGIAdapter> giAdapter;
		hr = giDevice->GetParent( __uuidof(IDXGIAdapter), reinterpret_cast<void**>(giAdapter.InitAsParam()) );
		assert( SUCCEEDED(hr) );

		ComPtr<IDXGIFactory> giFactory;
		hr = giAdapter->GetParent( __uuidof(IDXGIFactory), reinterpret_cast<void**>(giFactory.InitAsParam()) );
		assert( SUCCEEDED(hr) );

		return giFactory;
	}
}

extern HWND hWnd;

void D3D_Init( )
{
	// Create device and context. /////////////////////////////////////////////

	HRESULT hr = D3D11CreateDevice
	(
		NULL, // adapter
		D3D_DRIVER_TYPE_HARDWARE, // driver type
		0, // software driver
		D3D11_CREATE_DEVICE_SINGLETHREADED, // flags
		NULL, // feature level array
		0, // feature level array length
		D3D11_SDK_VERSION, // sdk version
		device.InitAsParam(), // device pointer
		&featureLevel, // returned feature level
		deviceCtx.InitAsParam() // return context
	);

	assert( SUCCEEDED(hr) );

	// Query MSAA. ////////////////////////////////////////////////////////////

	UINT msaaQuality;
	hr = device->CheckMultisampleQualityLevels( DXGI_FORMAT_R8G8B8A8_UNORM, 4, &msaaQuality );
	assert( SUCCEEDED(hr) );

	// Create swap chain. /////////////////////////////////////////////////////

	DXGI_SWAP_CHAIN_DESC swapDesc = {0};
	swapDesc.BufferDesc.Width = 640;
	swapDesc.BufferDesc.Height = 480;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if( msaaQuality > 0 )
	{
		swapDesc.SampleDesc.Count = 4;
		swapDesc.SampleDesc.Quality = msaaQuality-1;
	}
	else
	{
		swapDesc.SampleDesc.Count = 1;
		swapDesc.SampleDesc.Quality = 0;
	}

	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;
	swapDesc.OutputWindow = hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = 0;

	ComPtr<IDXGIFactory> factory = GetFactory( );
	assert( factory );

	hr = factory->CreateSwapChain( device.Get(), &swapDesc, swapChain.InitAsParam() );
	assert( SUCCEEDED(hr) );

	factory.Clear( );

	// Create Render Target view //////////////////////////////////////////////////

	ComPtr<ID3D11Texture2D> backBuf;
	hr = swapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuf.InitAsParam()) );
	assert( SUCCEEDED(hr) );

	hr = device->CreateRenderTargetView( backBuf.Get(), 0, renderTargView.InitAsParam() );
	backBuf.Clear( );

	// Create Depth Stencil View //////////////////////////////////////////////////

	D3D11_TEXTURE2D_DESC depthStencilDesc = {0};
	depthStencilDesc.Width = 640;
	depthStencilDesc.Height = 480;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if( msaaQuality > 0 )
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = msaaQuality-1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 1;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = device->CreateTexture2D( &depthStencilDesc, NULL, depthStencilTex.InitAsParam() );
	assert( SUCCEEDED(hr) );

	hr = device->CreateDepthStencilView( depthStencilTex.Get(), NULL, depthStencilView.InitAsParam() );
	assert( SUCCEEDED(hr) );

	// Bind Views to Output Merger Stage ///////////////////////////////////////////

	deviceCtx->OMSetRenderTargets( 1, renderTargView.GetAsParam(), depthStencilView.Get() );

	// Set viewport ////////////////////////////////////////////////////////////////
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = 640.0f;
	viewPort.Height = 640.0f;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 0.0f;

	deviceCtx->RSSetViewports( 1, &viewPort );
}

void D3D_Shutdown( )
{
	depthStencilView.Clear( );
	renderTargView.Clear( );
	depthStencilTex.Clear( );
	swapChain.Clear( );
	deviceCtx.Clear( );
	device.Clear( );
}

void D3D_Test( )
{
	const FLOAT clearColor[] = {0,0,0,1};

	deviceCtx->ClearRenderTargetView( renderTargView, clearColor );
	deviceCtx->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );

	HRESULT hr = swapChain->Present( 0, 0 );
	assert( SUCCEEDED(hr) );
}
