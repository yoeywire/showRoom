#include "showRoom.h"

wxIMPLEMENT_APP(showRoom);

bool showRoom::OnInit() {

	mainFrame = new mainWindow(rgbEngine);
	mainFrame->Show();

	effectFrame = new EffectWindow(rgbEngine);
	effectFrame->Show();

	return true;
}