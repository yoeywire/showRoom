#include "EffectWindow.h"

wxBEGIN_EVENT_TABLE(EffectWindow, wxFrame)
EVT_CHOICE(20001, ChoiceValueChanged)
EVT_CHOICE(20002, ChoiceValueChanged)
EVT_CHOICE(20009, ChoiceValueChanged)
EVT_TEXT(20003, TextValueChanged)
EVT_TEXT(20004, TextValueChanged)
EVT_TEXT(20005, TextValueChanged)
EVT_TEXT(20006, TextValueChanged)
EVT_TEXT(20007, TextValueChanged)
EVT_TEXT(20008, TextValueChanged)
wxEND_EVENT_TABLE()



EffectWindow::EffectWindow(MainEngine* mainEngine) : wxFrame(nullptr, wxID_ANY, "Effect Window", wxPoint(550, 250), wxSize(400, 350))
{
	engine = mainEngine;

	wxString attributes[2] = { wxT("Dim"), wxT("Color") };
	wxString waveforms[4] = { wxT("Sin"), wxT("Ramp"), wxT("Inv ramp"), wxT("Step") };
	wxString directions[2] = { wxT(">"), wxT("<") };

	// Attribute and waveform choice boxes:
	attrTxt = new wxStaticText(this, 22001, wxT("Attribute:"), wxPoint(10, 13), wxDefaultSize);
	formTxt = new wxStaticText(this, 22002, wxT("Waveform:"), wxPoint(190, 13), wxDefaultSize);
	attrBox = new wxChoice(this, 20001, wxPoint(70, 10), wxSize(80, 25), 2, attributes);
	attrBox->SetSelection(0);
	formBox = new wxChoice(this, 20002, wxPoint(260, 10), wxSize(80, 25), 4, waveforms);
	formBox->SetSelection(0);

	// Speed, rate and groups:
	speedTxt = new wxStaticText(this, 22003, wxT("Speed:"), wxPoint(10, 53), wxDefaultSize);
	rateTxt = new wxStaticText(this, 22004, wxT("Rate:"), wxPoint(180, 53), wxDefaultSize);
	speedTxt = new wxStaticText(this, 22009, wxT("Direction:"), wxPoint(10, 93), wxDefaultSize);
	groupsTxt = new wxStaticText(this, 22005, wxT("Groups:"), wxPoint(10, 133), wxDefaultSize);
	speedVal = new wxTextCtrl(this, 20003, wxT("120"), wxPoint(70, 50), wxSize(80, 22));
	rateVal = new wxTextCtrl(this, 20004, wxT("1"), wxPoint(220, 50), wxSize(80, 22));
	attrBox = new wxChoice(this, 20009, wxPoint(70, 90), wxSize(80, 25), 2, directions);
	attrBox->SetSelection(0);
	groupsVal = new wxTextCtrl(this, 20005, wxT("1"), wxPoint(70, 130), wxSize(80, 22));

	highTxt = new wxStaticText(this, 22006, wxT("High:"), wxPoint(10, 173), wxDefaultSize);
	lowTxt = new wxStaticText(this, 22007, wxT("Low:"), wxPoint(180, 173), wxDefaultSize);
	dutyTxt = new wxStaticText(this, 22008, wxT("Dutycycle:"), wxPoint(10, 213), wxDefaultSize);
	speedVal = new wxTextCtrl(this, 20006, wxT("100"), wxPoint(70, 170), wxSize(80, 22));
	rateVal = new wxTextCtrl(this, 20007, wxT("-100"), wxPoint(220, 170), wxSize(80, 22));
	dutyVal = new wxTextCtrl(this, 20008, wxT("50"), wxPoint(70, 210), wxSize(80, 22));

	wxLog* logger = new wxLogStream();
	wxLog::SetActiveTarget(logger);
}



void EffectWindow::TextValueChanged(wxCommandEvent& evt) 
{
	double entVal = 0;
	if (!evt.GetString().ToDouble(&entVal)) {
		//TODO: set value back to last value
	}


	switch (evt.GetId()) {
	case 20003:
		engine->fxParameterChange(SPEED, entVal);
		break;	
	case 20004:
		engine->fxParameterChange(RATE, entVal);
		break;	
	case 20005:
		engine->fxParameterChange(GROUPS, entVal);
		break;
	case 20006:
		engine->fxParameterChange(HIGH, entVal);
		break;
	case 20007:
		engine->fxParameterChange(LOW, entVal);
		break;
	case 20008:
		engine->fxParameterChange(DUTYCYCLE, entVal);
		break;
	}

	evt.Skip();
}



void EffectWindow::ChoiceValueChanged(wxCommandEvent& evt) 
{
	wxLogDebug("<EffectWindow> Value changed");

	switch (evt.GetId()) {
	case 20001:
		break;
	case 20002:
		engine->fxParameterChange(WAVEFORM, evt.GetInt());
		break;
	case 20009:
		engine->fxParameterChange(DIRECTION, evt.GetInt());
		break;
	}

	evt.Skip();
}