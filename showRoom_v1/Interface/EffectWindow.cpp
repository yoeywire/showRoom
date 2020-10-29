#include "EffectWindow.h"

wxBEGIN_EVENT_TABLE(EffectWindow, wxFrame)
EVT_GRID_CELL_CHANGING(EffectWindow::TableValueChanged, 11001)
wxEND_EVENT_TABLE()



EffectWindow::EffectWindow(RgbEngine* engine) : wxFrame(nullptr, wxID_ANY, "Effect Window", wxPoint(550, 250), wxSize(880, 350))
{
	rgbEngine = engine;

	fxTable = new wxGrid(this, 11001, wxPoint(0, 0), wxSize(900, 350));
	align = new wxGridCellAttr();

	//fxTable->Bind(wxEVT_GRID_CELL_CHANGED, &EffectWindow::TableValueChanged, this, 11001);

	fxTable->SetDefaultRowSize(60, true);
	fxTable->SetDefaultColSize(150, true);
	fxTable->CreateGrid(1, 5);

	// We can set the sizes of individual rows and columns
	fxTable->SetRowSize(0, 60);
	fxTable->SetColSize(0, 150);

	align->SetAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
	fxTable->SetColAttr(0, align);
	fxTable->SetColAttr(1, align);
	fxTable->SetColAttr(2, align);
	fxTable->SetColAttr(3, align);
	fxTable->SetColAttr(4, align);

	// FxTable colum names
	fxTable->SetColLabelValue(0, "Attribute");
	fxTable->SetColLabelValue(1, "Waveform");
	fxTable->SetColLabelValue(2, "Speed [BPM]");
	fxTable->SetColLabelValue(3, "Rate");
	fxTable->SetColLabelValue(4, "Groups");

	// Initial effect values
	fxTable->SetCellValue(0, 0, "Dim");
	fxTable->SetCellValue(0, 2, "120");
	fxTable->SetCellValue(0, 3, "x1");
	fxTable->SetCellValue(0, 4, "16");

	wxString waveforms[3] = { wxT("Sin"), wxT("Ramp"), wxT("Step") };	// Make table strings
	fxTable->SetCellEditor(0, 1, new wxGridCellChoiceEditor(3, waveforms, false)); // Add this to Cell
	fxTable->SetCellValue(0, 1, wxT("Sin"));


	attributeSel = new wxComboBox(this, 10201, "Sin", wxPoint());

	wxLog* logger = new wxLogStream();
	wxLog::SetActiveTarget(logger);
}



void EffectWindow::OnButtonClicked(wxCommandEvent& evt)
{
	int buttonId = evt.GetId();
	wxLogDebug("<Effect Window> Button %d pressed", evt.GetId());

	switch (buttonId) {
	case 10001:
		break;
	}
	evt.Skip();
}



void EffectWindow::TableValueChanged(wxGridEvent& evt) {
	wxLogDebug("<Effect Window> Grid change: %d cell: %d, %d data: %d", evt.GetId(), evt.GetCol(), evt.GetRow(), evt.GetSelection());

	switch (evt.GetCol()) {
	case 0: 
		fxTable->SetCellValue(0, 0, "Dim");
		break;
	case 1:
		rgbEngine->fxParameterChange(WAVEFORM, 0);
		break;
	case 2:
		double paramBuf;
		evt.GetString().ToDouble(&paramBuf);
		rgbEngine->fxParameterChange(SPEED, static_cast<float>(paramBuf));
		break;
	case 3:
		//fxTable->SetCellValue(0, 0, "Dim");
		break;
	}

	evt.Skip();
}