#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "wx/wx.h"
#include "main.h"
#include "EffectWindow.h"
#include "../Engine/RgbEngine.h"


class showRoom : public wxApp
{
public:
	virtual bool OnInit();

private:
	RgbEngine* rgbEngine = new RgbEngine;

	main* mainFrame = nullptr;
	EffectWindow* effectFrame = nullptr;
};

