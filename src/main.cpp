#ifdef _WIN32
#ifdef _WIN64
#include <Windows.h>
#else
#error windows x86 not support
#endif
#else
#error platform not support, or you may help me improve it
#endif
#include <print>
#include <thread>
#include <mutex>
#include <condition_variable>
std::mutex mtx;
std::condition_variable cv;
bool launched=false;
bool guisuccess=true;
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
    mtx.lock();
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
    launched=true;
    if(hwnd==NULL){
        guisuccess=false;
        return;
    }
    mtx.unlock();
    cv.notify_one();
    ShowWindow(hwnd,SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    MSG msg{};
    while(GetMessageA(&msg,NULL,0,0)>0){
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return;
}
#endif
int main() {
    std::unique_lock<std::mutex> lck(mtx);
    std::jthread gui(WinGUI);
    std::println("loading...");
    cv.wait(lck,[]{return launched;});
    if(guisuccess)
        std::println("Success!");
    else
        std::println("Error while trying to create the window!");
}