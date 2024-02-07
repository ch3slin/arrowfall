
// ----- Platform Globals -----

static bool running = true;

// ----- Platform Functions -----
bool platform_create_window(int width, int height, char* title);
void Platform_update_window();

// ----- Windows Platform -----
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>


// ----- Windows Globals -----
static HWND window;

// ----- Platform Implementation -----
LRESULT CALLBACK windows_window_callback(
    HWND window,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
){
    LRESULT result = 0;

    switch(msg){
        case WM_CLOSE:{
            running = false;
            break;
        }

        default:{
            result = DefWindowProcA(window, msg, wParam, lParam);
        }
    }
    return result;
}

char* uuid(char* title){
    return title;
}


bool platform_create_window(int width, int height, char* title){
    HINSTANCE instance = GetModuleHandleA(0);
    WNDCLASSA wc = {};
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = uuid(title);                         //need to impliment uuid()
    wc.lpfnWndProc = windows_window_callback;

    if(!RegisterClassA(&wc)){
        return false;
    }

    // WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMISEBOX
    int dwStyle = WS_OVERLAPPEDWINDOW;
    window = CreateWindowExA(
        0,
        uuid(title),    // reference lpszClassName from wc
        title,
        0,
        100,
        100,
        width,
        height,
        NULL,           // parent
        NULL,           // menu
        instance,
        NULL          // lpParent
    );

    if(window == NULL){
        return false;
    }
    
    ShowWindow(window, SW_SHOW);
    
    return true;
}

void Platform_update_window(){
    MSG msg;
    while(PeekMessageA(&msg, window, 0, 0, PM_REMOVE)){
        TranslateMessage(&msg);
        DispatchMessageA(&msg);              // calls callback in creating window
    }
}

#endif

int main(){
    platform_create_window(1200, 720, "Arrowfall");
    while(running){
        // Update

        Platform_update_window();
    }
    return 0;
}