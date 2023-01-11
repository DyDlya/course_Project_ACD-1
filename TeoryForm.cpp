#include "TeoryForm.h"

TeoryForm::TeoryForm(wxWindow* parent, wxWindowID id, const wxString& title): wxFrame(parent, id, title,wxDefaultPosition, wxSize(600,400), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	panel = new wxPanel(this, -1);
	
	TeoryText = new wxTextCtrl(panel,wxID_ANY,wxT(""),wxDefaultPosition, this->GetClientSize(), wxTE_MULTILINE| wxTE_READONLY);
}

TeoryForm::~TeoryForm()
{
}

void TeoryForm::LoadTeoryText()
{
	
	wxFileInputStream input("Teory.txt");
	wxTextInputStream text(input, wxT("\x09"), wxConvUTF8);
	wxString line;
	while (input.IsOk() && !input.Eof())
	{
		line += text.ReadLine() + "\n";

	}
	TeoryForm::TeoryText->SetValue(line);
}
