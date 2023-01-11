#pragma once
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/log.h> 
#include <wx/txtstrm.h>

class TeoryForm : public wxFrame
{


public:

	wxPanel* panel;

	wxTextCtrl* TeoryText;

	TeoryForm(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = "Теоретические сведения");

	~TeoryForm();

	void LoadTeoryText();

};