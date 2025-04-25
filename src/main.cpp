#ifdef _WIN64
#include <Windows.h>
#endif
#include <print>
#include <thread>
#include <mutex>
#include <condition_variable>
std::mutex mtx;
std::condition_variable cv;
bool guisu=false;
#ifdef _WIN64
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam){
    switch(msg){
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd,msg,wParam,lParam);
}
void WinGUI(){
    const char* CLASS_NAME="Main Window Class";
    HINSTANCE hInstance=GetModuleHandleA(NULL);
    WNDCLASSA wc{};
    wc.lpfnWndProc=WndProc;
    wc.hInstance=hInstance;
    wc.lpszClassName=CLASS_NAME;
    RegisterClassA(&wc);
    HWND hwnd=CreateWindowExA(
        0,
        CLASS_NAME,
        "Hello World GUI",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if(hwnd==NULL){
        return;
    }
    ShowWindow(hwnd,SW_SHOWNORMAL);
    MSG msg{};
    while(GetMessageA(&msg,NULL,0,0)>0){
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return;
}
#endif
int main() {
    std::println("loading...");
    std::jthread gui(WinGUI);
}