// MIT License
// Copyright (c) 2015 Hiroshi Shimamoto

#include "hwin/hwin.hxx"

using namespace hWin;

class mywnd : public wnd {
public:
	mywnd(cls *c) : wnd(c) {}
	virtual LRESULT proc(HWND w, UINT m, WPARAM wp, LPARAM lp);
};

LRESULT mywnd::proc(HWND w, UINT m, WPARAM wp, LPARAM lp)
{
	switch (m) {
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(w, m, wp, lp);
}

class myapp : public app {
public:
	myapp();
	void main(void);
};

myapp::myapp()
{
}

void myapp::main(void)
{
	cls *c = new cls();
	mywnd *w = new mywnd(c);

	c->regClass();

	HWND wnd = w->create();

	::UpdateWindow(wnd);
	::ShowWindow(wnd, SW_SHOW);

	msgloop();
}

int hWinMain(HINST inst, LPTSTR line, int show)
{
	myapp a;

	a.main();

	return 0;
}
