#include "Client.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd = nullptr;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPWSTR    lpCmdLine,
					  _In_ int       nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	InitInstance(hInstance, nCmdShow);
	MSG msg{};

	Graphic_Device device(GRAPHIC_DESC(g_hWnd, true, WINCX, WINCY));
	TimeManager Time(50, 65);

	GameInstance instance(device.GetDevice());
	auto& Level = instance.Level;


	Level.OpenLevel(new Main_Level, nullptr);

	while(!GetAsyncKeyState(VK_ESCAPE))
	{
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Time.Update();
		Level.SyncLevel();

		while(Time.FixedLimit())
		{
			Level.FixedUpdate(Time.GetFDT());
		}

		while(Time.UpdateLimit())
		{
			float dt = Time.GetDT();
			Level.Update(dt);
			Level.LateUpdate(dt);
			Level.Render();
		}

		Level.EndFrame();

		Time.FPS_INFO(g_hWnd);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	return (int)msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex{};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
	RECT rc{ 0,0, WINCX ,WINCY };

	g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
						   CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top,
						   nullptr, nullptr, hInstance, nullptr);

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch(wmId)
			{
				case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
				default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_DESTROY:
		PostQuitMessage(0);
		break;
		default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}