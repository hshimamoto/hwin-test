// MIT License
// Copyright (c) 2015 Hiroshi Shimamoto

#include "hwin/hwin.hxx"

using namespace hWin;

class mynotify : public notify {
public:
	mynotify(notify_wnd *w);
	virtual void proc(LPARAM m);
};

mynotify::mynotify(notify_wnd *w) : notify(w)
{
	NOTIFYICONDATA *ni = get();

	ni->uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	ni->hIcon = ::LoadIcon(getInst(), "ICON_TEST");
}

void mynotify::proc(LPARAM m)
{
}

class mywnd : public wnd {
	notify_wnd *nw;
	mynotify *n;
public:
	mywnd(cls *c) : wnd(c), nw(NULL), n(NULL) {}
	virtual LRESULT proc(HWND w, UINT m, WPARAM wp, LPARAM lp);
	virtual void on_create(void);
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

void mywnd::on_create(void)
{
	nw = new notify_wnd(get_class());
	nw->create();

	n = new mynotify(nw);

	n->add();
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
