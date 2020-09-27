#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "wx/wx.h"
#include "main.h"


class ledInterface : public wxApp
{
public:
	virtual bool OnInit();

private:
	main* m_frame1 = nullptr;
};

