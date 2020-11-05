#include "mainWindow.h"

wxBEGIN_EVENT_TABLE(mainWindow, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
EVT_BUTTON(10002, OnButtonClicked)
EVT_BUTTON(10003, OnButtonClicked)
EVT_SLIDER(10101, sliderChange)
EVT_SLIDER(10102, sliderChange)
EVT_SLIDER(10103, sliderChange)
EVT_SLIDER(10104, sliderChange)
wxEND_EVENT_TABLE()



mainWindow::mainWindow(MainEngine* engine) : wxFrame(nullptr, wxID_ANY, "ShowRoom Main Window", wxPoint(20, 150), wxSize(510, 400))
{
	rgbEngine = engine;

	m_btn1 = new wxButton(this, 10001, "Static Color", wxPoint(10, 10), wxSize(150, 90));
	m_btn2 = new wxButton(this, 10002, "Rainbow", wxPoint(170, 10), wxSize(150, 90));
	m_btn3 = new wxButton(this, 10003, "Effect", wxPoint(330, 10), wxSize(150, 90));

	sld1 = new wxSlider(this, 10101, 255, 0, 255, wxPoint(10, 120), wxSize(475, 15), wxSL_VALUE_LABEL);
	sld2 = new wxSlider(this, 10102, 255, 0, 255, wxPoint(10, 180), wxSize(475, 15), wxSL_VALUE_LABEL);
	sld3 = new wxSlider(this, 10103, 255, 0, 255, wxPoint(10, 240), wxSize(475, 15), wxSL_VALUE_LABEL);
	sld4 = new wxSlider(this, 10104, 255, 0, 255, wxPoint(10, 300), wxSize(475, 15), wxSL_VALUE_LABEL);

	menubar = new wxMenuBar;
	fileMenu = new wxMenu;
	fileMenu->Append(wxID_EXIT, wxT("&Quit"));
	menubar->Append(fileMenu, wxT("&File"));
	SetMenuBar(menubar);

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(mainWindow::OnQuit));

	wxLog* logger = new wxLogStream();
	wxLog::SetActiveTarget(logger);
}



void mainWindow::OnButtonClicked(wxCommandEvent& evt)
{
	int buttonId = evt.GetId();
	//wxLogDebug("<main frame> Button %d pressed", buttonId);

	rgbEngine->inputBtnChange(buttonId);
	evt.Skip();
}



void mainWindow::sliderChange(wxCommandEvent& evt) {
	//wxLogDebug("<main frame> Slider changed, value: %d", evt.GetInt());
	rgbEngine->inputSldChange(evt.GetId(), evt.GetInt());
}


void mainWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}