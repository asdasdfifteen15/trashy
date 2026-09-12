#include <windows.h>
#include <stdio.h>

// 全局变量
int g_counter = 0;
HWND g_hwndCounter;

// 保存和加载计数器到文件
void SaveCounter() {
    FILE* file = fopen("误删.dat", "wb");
    if (file) {
        fwrite(&g_counter, sizeof(int), 1, file);
        fclose(file);
    }
}

void LoadCounter() {
    FILE* file = fopen("误删.dat", "rb");
    if (file) {
        fread(&g_counter, sizeof(int), 1, file);
        fclose(file);
    }
}

// 更新计数器显示
void UpdateCounterDisplay() {
    char buffer[32];
    sprintf(buffer, "计数器: %d", g_counter);
    SetWindowText(g_hwndCounter, buffer);
}

// 窗口过程
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        // 创建计数器显示文本
        g_hwndCounter = CreateWindow("STATIC", "计数器: 0", 
            WS_VISIBLE | WS_CHILD, 10, 10, 200, 30, 
            hwnd, NULL, NULL, NULL);
        
        // 创建增加按钮
        CreateWindow("BUTTON", "+1", 
            WS_VISIBLE | WS_CHILD, 10, 50, 100, 30, 
            hwnd, (HMENU)1, NULL, NULL);
        
        // 创建重置按钮
        CreateWindow("BUTTON", "重置", 
            WS_VISIBLE | WS_CHILD, 120, 50, 100, 30, 
            hwnd, (HMENU)2, NULL, NULL);
        
        LoadCounter();
        UpdateCounterDisplay();
        break;
        
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { // +1 按钮
            g_counter++;
            UpdateCounterDisplay();
            SaveCounter();
        }
        else if (LOWORD(wParam) == 2) { // 重置按钮
            g_counter = 0;
            UpdateCounterDisplay();
            SaveCounter();
        }
        break;
        
    case WM_DESTROY:
        SaveCounter();
        PostQuitMessage(0);
        return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// 主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	printf("请勿关闭此窗口");
    // 注册窗口类
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "CounterApp";
    RegisterClass(&wc);
    
    // 创建窗口（摒弃控制台）
    HWND hwnd = CreateWindow("CounterApp", "计数器应用", 
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 140, 
        NULL, NULL, hInstance, NULL);
    
    if (!hwnd) return -1;
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}
