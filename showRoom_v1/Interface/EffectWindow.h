#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "wx/wx.h"
#include <wx/grid.h>
#include "../Engine/RgbEngine.h"

class EffectWindow : public wxFrame
{
public:
	EffectWindow(RgbEngine* engine);

	wxGrid* fxTable = nullptr;
	wxGridCellAttr* align = nullptr;
	wxComboBox* attributeSel = nullptr;

	void OnButtonClicked(wxCommandEvent& evt);
	void TableValueChanged(wxGridEvent& evt);

	wxDECLARE_EVENT_TABLE();
	

private:
	RgbEngine* rgbEngine = nullptr;
};

