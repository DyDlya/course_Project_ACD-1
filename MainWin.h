#pragma once

#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/event.h>
#include <wx/msgdlg.h>
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/log.h> 
#include <wx/txtstrm.h>

class MainWin : public wxFrame {
	wxPanel* panel;
	wxBoxSizer* hSizer1;
	wxBoxSizer* hSizer2;
	wxBoxSizer* hSizer3;
	wxBoxSizer* hSizer4;
	wxBoxSizer* hSizer5;
	wxBoxSizer* vSizer;
	
	enum MENU_EVT {
		// Меню "Файл"
		EVT_OPEN,
		// Меню "Обучение"
		EVT_TEORY,
		EVT_TEST
	};

public:
	// StaticText - лэйбл
	// TextCtrl - текстовое поле

	wxMenuBar* menuBar;
	wxMenu* file;
	wxMenu* study;
	wxMenuItem* studyTeory;
	wxMenuItem* studyTest;

	wxStaticText* mainText;
	wxTextCtrl* mainCtrl;
	wxStaticText* findText;
	wxTextCtrl* findCtrl;
	wxStaticText* shiftCount;

	wxButton* clearBtn;
	wxButton* findBtn;
	
	void OnFind(wxCommandEvent &event);
	void OnClear(wxCommandEvent& event);

	void MenuFileOpen(wxCommandEvent& event);
	void MenuStudyTeory(wxCommandEvent& event);
	void MenuStudyTest(wxCommandEvent& event);

	MainWin();
};