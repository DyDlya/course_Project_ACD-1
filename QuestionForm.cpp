#include "QuestionForm.h"

int randomer(int a, int b) { // Функция для получения случайных чисел в интервале от 1 до 100
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(a, b);
	int var;
	var = dist(gen);
	return var;
}


Question::Question(wxWindow* parent, wxWindowID id, const wxString& title) : wxFrame(parent, id, title, wxDefaultPosition, wxSize(500,350), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{

	Panel* panel = new Panel(this, wxID_ANY);
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	ParentWin = parent;

	this->Centre(wxBOTH);

	
	
	panel->curQuestion = 1;
	panel->randomQuestionNum = randomer(1, 20);
	panel->GetQuestion();
}

Question::~Question()
{
	ParentWin->Show(true);
}



Panel::Panel(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{
	ParentWin = parent;
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* hSizer1;
	hSizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* vSizer1;
	vSizer1 = new wxBoxSizer(wxVERTICAL);

	stText1 = new wxStaticText(this, wxID_ANY, wxT("Вопрос:"), wxDefaultPosition, wxDefaultSize, 0);
	stText1->Wrap(-1);
	stText1->SetFont(wxFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial Narrow")));
	stText1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));

	vSizer1->Add(stText1, 0, wxTOP, 12);

	QText = new wxStaticText(this, wxID_ANY, wxT("Бла бла "), wxDefaultPosition, wxSize(-1, 72), 0);
	QText->Wrap(450);
	QText->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));
	QText->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));

	vSizer1->Add(QText, 1, wxTOP, 8);


	hSizer1->Add(vSizer1, 1, wxEXPAND | wxLEFT, 20);


	mainSizer->Add(hSizer1, 1, wxEXPAND, 5);

	m_staticline2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	mainSizer->Add(m_staticline2, 0, wxEXPAND | wxALL, 12);

	wxBoxSizer* hSizer2;
	hSizer2 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* vSizer2;
	vSizer2 = new wxBoxSizer(wxVERTICAL);

	rBtn1 = new wxRadioButton(this, 1, wxT("RadioBtn"), wxDefaultPosition, wxSize(450,-1), 0);
	rBtn1->Bind(wxEVT_RADIOBUTTON, &Panel::GetAnswer, this);
	vSizer2->Add(rBtn1, 0, wxALL, 5);

	rBtn2 = new wxRadioButton(this, 2, wxT("RadioBtn"), wxDefaultPosition, wxSize(450, -1), 0);
	rBtn2->Bind(wxEVT_RADIOBUTTON, &Panel::GetAnswer, this);
	vSizer2->Add(rBtn2, 0, wxALL, 5);

	rBtn3 = new wxRadioButton(this, 3, wxT("RadioBtn"), wxDefaultPosition, wxSize(450, -1), 0);
	rBtn3->Bind(wxEVT_RADIOBUTTON, &Panel::GetAnswer, this);
	vSizer2->Add(rBtn3, 0, wxALL, 5);

	rBtn4 = new wxRadioButton(this, 4, wxT("RadioBtn"), wxDefaultPosition, wxSize(450, -1), 0);
	rBtn4->Bind(wxEVT_RADIOBUTTON, &Panel::GetAnswer, this);
	vSizer2->Add(rBtn4, 0, wxALL, 5);


	hSizer2->Add(vSizer2, 1, wxEXPAND | wxLEFT, 20);


	mainSizer->Add(hSizer2, 1, wxEXPAND, 5);

	wxBoxSizer* hSizer3;
	hSizer3 = new wxBoxSizer(wxHORIZONTAL);

	nextQBtn = new wxButton(this, wxID_ANY, wxT("Следующий вопрос"), wxDefaultPosition, wxDefaultSize, 0);
	nextQBtn->Bind(wxEVT_BUTTON, &Panel::NextQuestion, this);
	hSizer3->Add(nextQBtn, 0, wxALIGN_BOTTOM | wxTOP | wxRIGHT | wxLEFT, 5);


	mainSizer->Add(hSizer3, 1, wxALIGN_RIGHT | wxBOTTOM | wxRIGHT, 16);


	this->SetSizer(mainSizer);
	this->Layout();
}

Panel::~Panel()
{
}

void Panel::NextQuestion(wxCommandEvent& event)
{
	userAnswer[randomQuestionNum] = curAnswer;
		
	randomQuestionNum = randomer(1, 20);
	
	this->GetQuestion();
}

void Panel::GetQuestion()
{

	if (curQuestion <= 5) {
		if (curQuestion == 5) {
			Panel::nextQBtn->SetLabel("Завершить");
		}

		wxFileInputStream input_a("Answers.txt");
		wxFileInputStream input_q("Questions.txt");
		wxTextInputStream AnsText(input_a, wxT("\x09"), wxConvUTF8);


		wxTextInputStream Qtext(input_q, wxT("\x09"), wxConvUTF8);

		for (int i = 0; i != randomQuestionNum; i++) {
			Qtext.ReadLine();
		}
		for (int i = 0; i != (randomQuestionNum) * 4; i++) {
			AnsText.ReadLine();
			
		}
		
		Panel::QText->SetLabel(Qtext.ReadLine());
		Panel::QText->Wrap(450);
		Panel::rBtn1->SetLabel(AnsText.ReadLine());
		Panel::rBtn2->SetLabel(AnsText.ReadLine());
		Panel::rBtn3->SetLabel(AnsText.ReadLine());
		Panel::rBtn4->SetLabel(AnsText.ReadLine());
		
		curQuestion++;
	}
	else {
		
		int score = 0;
		for (int i = 0; i <= 20; i++) {
			if (userAnswer[i] == trueAnswer[i]) {
				score++;
			}
		}

		wxMessageBox("Ваша оценка: "+ std::to_string(score)+"\nПравильных ответов: " + std::to_string(score) + " из пяти.");

		this->Close();
		ParentWin->Close();
	}
		
}

void Panel::GetAnswer(wxCommandEvent& event)
{
	curAnswer = event.GetId();
}
