#pragma once


// �̱��� ����	(2)
class CCore
{
	SINGLE(CCore);
private:
	HWND	m_hWnd;				// ���� ������ �ڵ�
	POINT	m_ptResolution;		// ���� ������ �ػ�
	HDC		m_hDC;				// ���� �����쿡 Draw�� DC

public:
	int init(HWND _hWnd, POINT _ptResolution);	// �ʱ�ȭ �Լ�, ���ο��� ȣ��
	void progress();

private:
	void update();
	void render();

private:
	CCore();
	~CCore();
};