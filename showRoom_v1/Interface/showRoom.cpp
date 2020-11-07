#include "ShowRoom.h"

wxIMPLEMENT_APP(ShowRoom);

bool ShowRoom::OnInit() {

	mainFrame = new mainWindow(mainEngine);
	mainFrame->Show();

	effectFrame = new EffectWindow(mainEngine);
	effectFrame->Show();

	return true;
}

ShowRoom::~ShowRoom() {
	delete mainEngine;
}