// WinApiAR.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "WinApiAR.h"
#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND      g_hWnd;   // 메인 윈도우 핸들
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 지역
// 전역
// 정적 (데이터 영역)
// 1. 함수 안에 선언될 때 - 함수 호출, 종료와 삭제 별개 
// 2. 파일안에 선언될 때 - 파일안에서만 접근가능 - 이름중복규칙 적용x
// 3. 클래스 안에 : 클래스객체의 생성, 해제와 상관없이 정적멤버는 데이터 영역에 하나 있음, 클래스 내에서만 접근가능
// 외부

class CClass
{
private:
    int m_i;
public:
    static int m_iStatic; // 정적 멤버 ( 데이터 ) 
public:
    void func()
    {
        this->m_i; 
        m_iStatic = 0;
    }

    // 정적 멤버함수. 객체없이 호출 가능. this가 없다(멤버 접근 불가), static키워드가 붙은 정적 멤버는 접근 가능
    static void FUNC()
    {
        m_iStatic = 0;
    }
};

int CClass::m_iStatic = 0;


// SAL
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.





    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIAR, szWindowClass, MAX_LOADSTRING);
    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core 초기화
    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{1280, 768})))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);

        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIAR));

    MSG msg;

    // GetMessage
    // 메세지큐에서 메세지 확인할 때 까지 대기
    // msg.message == WM_QUIT 일 때 false 반환 -> while문 종료 -> 프로그램 종료
    // 
    // GetMessage는 메세지가 발생할 떄 까지 대기 -> 메세지 반응형태
    // ∴ PeekMessage()로 메세지를 슬쩍보겠다. 
    // PeekMessage
    // 메세지 유무와 관계없이 항상 반환   
    // 메세지큐에서 메세지를 확인한 경우 true, 메세지큐에 메세지가 없는 경우 false를 반환
    // 
    // 기본 메시지 루프입니다:
    while (true)    
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))    // 메세지가 발생했다면
        {
            if (WM_QUIT == msg.message)
                break;
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        // 메세지가 발생하지 않는 대부분의 시간
        else
        {
            //  메세지가 없는동안 호출
            // Game 코드 수행
            // 디자인 패턴(설계 유형)
            // 싱글톤 패턴
            CCore::GetInst()->progress();
        }
    }
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIAR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIAR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 무효화 영역(Invalidate Rect)이 발생한 경우 WM_PAINT 발생
        {
            PAINTSTRUCT ps;

            // Device Context 만들어서 ID를 반환
            HDC hdc = BeginPaint(hWnd, &ps);    // Device  Context (그리기) : 그리기 작업을 하는데 필요한 데이터 들의 집합체
              

            //Rectangle(hdc, 1180, 668, 1280, 768);


            // 그리기 종료
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:
    {
 
    }
        break;
    case WM_LBUTTONDOWN:
        break;
    case WM_MOUSEMOVE:
        break;
    case WM_LBUTTONUP:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
