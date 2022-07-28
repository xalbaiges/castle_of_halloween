/*
 * Compilation :
 *               gcc main.c -lm -lgdi32 -o main
*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define WINDOW_WIDTH 500
#define TILE_SIZE 50
#define MAP_SIZE 10


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



int map[10][10] = {
                 {1,1,1,1,1,1,1,1,1,1},
                 {1,0,0,0,0,0,0,0,0,1},
                 {1,0,0,0,0,0,0,0,0,1},
                 {1,0,0,0,0,0,0,0,0,1},
                 {1,0,0,0,0,1,0,0,0,1},
                 {1,0,0,0,0,1,0,0,0,1},
                 {1,0,0,1,1,1,0,0,0,1},
                 {1,0,0,0,0,0,0,0,0,1},
                 {1,0,0,0,0,0,0,0,0,1},
                 {1,1,1,1,1,1,1,1,1,1}
                };






int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    
    MSG  msg;
    WNDCLASSW wc = {0};

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Rectangle";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Rectangle",
          WS_OVERLAPPEDWINDOW | WS_VISIBLE,
          100, 100, 250, 200, NULL, NULL, hInstance, NULL);

    while (GetMessage(&msg, NULL, 0, 0)) {
        
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    printf("bye!\n");

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    
    HDC hdc;
    PAINTSTRUCT ps;

    switch(msg) {
        /* keyboard managment */
        /* https://docs.microsoft.com/es-es/windows/win32/inputdev/keyboard-input  */
        case WM_KEYDOWN:
             switch(wParam) {
               case VK_UP:
                    printf("DOWN VK_UP\n" );
                    break;
               case VK_DOWN:
                    printf("DOWN VK_DOWN\n" );
                    break;
               case VK_LEFT:
                    printf("DOWN VK_LEFT\n" );
                    break;
               case VK_RIGHT:
                    printf("DOWN VK_RIGHT\n" );
                    break;
             }/*eo_switch*/
             break;

        case WM_KEYUP:
             switch(wParam) {
               case VK_UP:
                    printf("UP VK_UP\n" );
                    break;
               case VK_DOWN:
                    printf("UP VK_DOWN\n" );
                    break;
               case VK_LEFT:
                    printf("UP VK_LEFT\n" );
                    break;
               case VK_RIGHT:
                    printf("UP VK_RIGHT\n" );
                    break;
             }/*eo_switch*/
             break;

        /* eo keyboard managment */
    
        case WM_PAINT:

            hdc = BeginPaint(hwnd, &ps);
            Rectangle(hdc, 50, 50, 200, 100);
            EndPaint(hwnd, &ps);
            break;

        case WM_DESTROY:
 
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}