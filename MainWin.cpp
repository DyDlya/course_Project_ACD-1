#include "MainWin.h"
#include "Find.h"
#include "QuestionForm.h"
#include "TeoryForm.h"

MainWin::MainWin(): wxFrame(NULL, wxID_ANY, "����� �����",wxDefaultPosition, wxSize(450, 400), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	panel = new wxPanel(this, -1);
	
	menuBar = new wxMenuBar();
	file = new wxMenu();
	file->Append(EVT_OPEN, wxT("�������"));
	file->Bind(wxEVT_MENU, &MainWin::MenuFileOpen, this);
	menuBar->Append(file, wxT("����"));
	
	study = new wxMenu();
	studyTeory = new wxMenuItem(study,EVT_TEORY, wxT("������"));
	study->Append(studyTeory);
	studyTest = new wxMenuItem(study, EVT_TEST, wxT("������������"));
	study->Append(studyTest);
	study->Bind(wxEVT_COMMAND_MENU_SELECTED, &MainWin::MenuStudyTeory, this, studyTeory->GetId());
	study->Bind(wxEVT_COMMAND_MENU_SELECTED, &MainWin::MenuStudyTest, this, studyTest->GetId());

	menuBar->Append(study, wxT("��������"));


	hSizer1 = new wxBoxSizer(wxHORIZONTAL); // �������������� ������
	hSizer2 = new wxBoxSizer(wxHORIZONTAL); // �������������� ������

	hSizer3 = new wxBoxSizer(wxHORIZONTAL); // �������������� ������
	hSizer4 = new wxBoxSizer(wxHORIZONTAL); // �������������� ������
	hSizer5 = new wxBoxSizer(wxHORIZONTAL); // �������������� ������

	vSizer = new wxBoxSizer(wxVERTICAL); // ������������ ������, �� ������� �� ���������
	
	// ������ ���� ����� � ������� ��� ���
	mainText = new wxStaticText(panel, wxID_ANY, wxT("�������� �����"));
	mainCtrl = new wxTextCtrl(panel, wxID_ANY,wxT(""),wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	hSizer1->Add(mainText, 0, wxTOP, 8); 
	hSizer2->Add(mainCtrl, 1, wxEXPAND );

	// ���� ����� ��� ������� ���������
	findText = new wxStaticText(panel, wxID_ANY, wxT("������� ������� ������"));
	findCtrl = new wxTextCtrl(panel, wxID_ANY, wxT(""));
	hSizer3->Add(findText, 0);
	hSizer4->Add(findCtrl, 1, wxEXPAND);

	// ������ ����������
	shiftCount = new wxStaticText(panel, wxID_ANY, wxT("���������� ��������: 0"));
	findBtn = new wxButton(panel, wxID_ANY, wxT("�����"),wxDefaultPosition, wxSize(96,28));
	clearBtn = new wxButton(panel, wxID_ANY, wxT("��������"), wxDefaultPosition, wxSize(96, 28));
	// �������� ��������� � �������
	findBtn->Bind(wxEVT_BUTTON, &MainWin::OnFind, this);
	clearBtn->Bind(wxEVT_BUTTON, &MainWin::OnClear, this);

	hSizer5->Add(shiftCount, 0, wxRIGHT| wxALIGN_CENTRE_VERTICAL, 72);
	hSizer5->Add(clearBtn, 0);
	hSizer5->Add(findBtn, 0, wxLEFT | wxBOTTOM, 8);
	

	// ���������� �������� ���� ����� � ������
	vSizer->Add(hSizer1, 0, wxLEFT, 12);
	vSizer->Add(-1, 4);
	vSizer->Add(hSizer2, 1, wxEXPAND | wxLEFT | wxRIGHT|wxBOTTOM, 12);
	

	// ���������� ���� ����� ������� ������ � ������
	vSizer->Add(hSizer3, 0, wxLEFT, 12);
	vSizer->Add(-1, 4);
	vSizer->Add(hSizer4, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 12);

	// ���������� ������
	vSizer->Add(-1, 8);
	vSizer->Add(hSizer5, 0, wxALIGN_RIGHT | wxRIGHT, 12);

	panel->SetSizer(vSizer);
	SetMenuBar(menuBar);


}

void MainWin::OnFind(wxCommandEvent& event)
{
	
	

	std::string mainStr = MainWin::mainCtrl->GetValue().ToStdString();
	std::string findStr = MainWin::findCtrl->GetValue().ToStdString();

	int shift = 0;
	int findResult = FindStr(mainStr, findStr, shift);

	if (findResult != -1) {
		wxPuts(std::to_string(findResult));

		MainWin::mainCtrl->SetFocus();
		
		MainWin::mainCtrl->SetSelection((findResult - findStr.size()) + 1, findResult+1);

		MainWin::shiftCount->SetLabel(wxT("���������� ��������: " + std::to_string(shift)));
		
	}
	else {
		wxMessageBox("����� �� ��� �����������!");
		MainWin::shiftCount->SetLabel(wxT("���������� ��������: 0"));
	}

}

void MainWin::OnClear(wxCommandEvent& event)
{
	
	MainWin::mainCtrl->Clear();
	MainWin::findCtrl->Clear();
}

void MainWin::MenuFileOpen(wxCommandEvent& event)
{
	wxFileDialog
		openFileDialog(this, _("Open TXT file"), "", "",
			"TXT files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	
	wxFileInputStream input(openFileDialog.GetPath());
	wxTextInputStream text(input, wxT("\x09"), wxConvUTF8);
	wxString line;
	while (input.IsOk() && !input.Eof())
	{
		line += text.ReadLine();
		
	}
	MainWin::mainCtrl->SetValue(line);
}

void MainWin::MenuStudyTeory(wxCommandEvent& event) // ����� � �������������� ����������� �� ����. �������� �������
{
	TeoryForm* tForm = new TeoryForm(this);
	tForm->Show(true);
	tForm->LoadTeoryText();
}

void MainWin::MenuStudyTest(wxCommandEvent& event)
{
	this->Hide();

	Question* qForm = new Question(this);
	qForm->Show(true);
}
