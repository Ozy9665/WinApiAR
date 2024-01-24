#pragma once


// 싱글톤 패턴	(2)
class CCore
{
	SINGLE(CCore);
private:
	HWND	m_hWnd;				// 메인 윈도우 핸들
	POINT	m_ptResolution;		// 메인 윈도우 해상도
	HDC		m_hDC;				// 메인 윈도우에 Draw할 DC

	HBITMAP	 m_hBit;
	HDC		 m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);	// 초기화 함수, 메인에서 호출
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() {return m_ptResolution;}
};