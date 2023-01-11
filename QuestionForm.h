#pragma once

#include <wx/artprov.h>
#include <random>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/radiobut.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/panel.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/log.h> 
#include <wx/txtstrm.h>

class Question : public wxFrame
{


public:
	wxWindow* ParentWin;

	

	Question(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = "Тестирование");

	~Question();

};

class Panel : public wxPanel
{
private:
	
protected:
	wxStaticText* stText1;
	wxStaticText* QText;
	wxStaticLine* m_staticline2;
	wxRadioButton* rBtn1;
	wxRadioButton* rBtn2;
	wxRadioButton* rBtn3;
	wxRadioButton* rBtn4;
	wxButton* nextQBtn;
	
	

public:
	wxWindow* ParentWin;
	int curAnswer;
	int trueAnswer[20] = { 2,4,3,1,2,2,3,1,2,1,4,1,1,1,2,1,3,2,3,1 }; // Правильные ответы
	int userAnswer[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	int curQuestion;
	int randomQuestionNum;

	void NextQuestion(wxCommandEvent& event);

	void GetQuestion();

	void GetAnswer(wxCommandEvent& event);

	Panel(wxWindow* parent, wxWindowID id = wxID_ANY);

	~Panel();

};

