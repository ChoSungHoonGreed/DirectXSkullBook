// DirectX3Skull.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "DirectX3Skull.h"
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LPDIRECT3D9			g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;
HRESULT InitD3D(HWND hWnd)
{
	//디바이스를 생성하기 위한 D3D 객체 생성
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));	//반드시 제로메모리로 미리 구조체를 깨끗이 지워야 한다.
	d3dpp.Windowed = TRUE;	//창모드로 생성
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //가장 효율적인 swap효과
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;// 현재 바탕화면 모드에 맞춰서 후면 버퍼 생성
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}
	return S_OK;
}
void Cleanup()
{
	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}
void Render()
{
	if (NULL == g_pd3dDevice)
		return;

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		//랜더창
		g_pd3dDevice->EndScene();
	}
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		Render();
		ValidateRect(hWnd, NULL);
		return 0;
	}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandle(NULL) , NULL, NULL, NULL, NULL, "D3D Tutorial", NULL };
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow("D3D Tutorial", "D3D Tutorial 01 : CreateDevice", WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, GetDesktopWindow(), NULL, wc.hInstance, NULL);

	if (SUCCEEDED(InitD3D(hWnd)))
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	UnregisterClass("D3D Tutorial", wc.hInstance);
	return 0;


}

