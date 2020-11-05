#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "wx/wx.h"
#include <wx/grid.h>
#include "../Engine/RgbEngine.h"

class EffectWindow : public wxFrame
{
public:
	EffectWindow(RgbEngine* engine);

	wxChoice* attrBox = nullptr;
	wxChoice* formBox = nullptr;
	wxStaticText* attrTxt = nullptr;
	wxStaticText* formTxt = nullptr;

	wxTextCtrl* speedVal = nullptr;
	wxTextCtrl* rateVal = nullptr;
	wxTextCtrl* groupsVal = nullptr;
	wxStaticText* speedTxt = nullptr;
	wxStaticText* rateTxt = nullptr;
	wxStaticText* groupsTxt = nullptr;

	void TextValueChanged(wxCommandEvent& evt);
	void ChoiceValueChanged(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
	

private:
	RgbEngine* rgbEngine = nullptr;
};

