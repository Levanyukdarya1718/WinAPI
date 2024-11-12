//MainWindow
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "My Window"; //Имя Класса окна

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1)Регистрация класса окна:
	WNDCLASSEX wc; //windows class
	ZeroMemory(&wc, sizeof(wc));//обнуляыем экземпляр

	//связаны с размером и стилем
	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0; //cb... - Count Bytes

	//связаны с внешним видом
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm=LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_MY_WINDOW_CLASS;
	wc.lpfnWndProc = (WNDPROC)WndProc;

	//регистрация функции
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	// 2) Создание окна:
	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);
	INT window_width = screen_width * 3 / 4;
	INT window_height = screen_height * .75;
	INT window_start_x = screen_width / 8;
	INT window_start_y = screen_height / 8;


	HWND hwnd = CreateWindowEx
	(
		NULL, //ExStyles
		g_sz_MY_WINDOW_CLASS, //Class name
		g_sz_MY_WINDOW_CLASS, //Window title
		WS_OVERLAPPEDWINDOW, //Window style
		//CW_USEDEFAULT, CW_USEDEFAULT, //Window position
		//CW_USEDEFAULT, CW_USEDEFAULT, //Window Size
		window_start_x, window_start_y,
		window_width, window_height,
		NULL, //Parent Window
		NULL, //Main menu Resourceid for MainWindow or ResourceID for ChildWondow
		hInstance,
		NULL

	);
	ShowWindow(hwnd, nCmdShow);//Задает режим отображения окна
								//(Развернуто на весь экран, свернутто в окно, свернуто на панель задач)
	UpdateWindow(hwnd); //Прорисовывает окно

	//3) Запуск цикла сообщений:
	MSG msg; //Создаем сообщение
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return msg.message;
}
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_MOVE:
	case WM_SIZE:
	{
		RECT rect;
		GetWindowRect(hwnd, &rect); //записание координат
		INT window_width = rect.right - rect.left;
		INT window_height = rect.bottom - rect.top;
		CONST INT SIZE= 256;
		CHAR sz_title[SIZE]{};
		sprintf
			//s... - string;
			//...f-format;
			//printf(); //print formatted string (вывести на экран отформатированнуюстроку)
			// функция spritf(...) форматирует src- строку, и результат форматирования сохраняет в другую dst-строку
			//src - Source(строка источник). Как правило является форматированной строкой
			// Форматированная строка как правило смодержит спецификаторы, 
			// которые подменяются соответствующими параметрами.
			// %i -на место этого спецификатора вставляется значение типа int
			// %s -на место этого спецификатора вставляется значение типа char*(указатель на строку) 
			//dst- Distination(строгка получавтель)
		(
			sz_title, 
			"%s-Position:%ix%i;\tSize: %ix%i",
			g_sz_MY_WINDOW_CLASS, 
			rect.left, rect.top,
			window_width, window_height
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
		}
			break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);

	}
	return FALSE;
}