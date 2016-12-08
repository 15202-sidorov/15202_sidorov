#include "menu_widget.h"

void Menu::SET_GOOD_LABEL(QString sign)
{
	QString labelText = "<P><b><i><FONT COLOR='#ff0000' FONT SIZE = 4>";
	labelText.append(sign);
	labelText.append("</i></b></P></br>"); 
	state.setText(labelText);
}

const QString Menu::STOP_SIGN = "Stop";
const QString Menu::GO_SIGN = "In progress";

Menu::Menu(QWidget *parent)
	:QWidget(parent)
{
	//setting text for buttons and so forth
	
	SET_GOOD_LABEL(STOP_SIGN);
	StartButton.setText("GO");
	StopButton.setText("STOP");
	StepButton.setText("STEP");
	ClearButton.setText("CLEAR");
	
	//adding and setting widgets in menu
	button_layout.addWidget(&StartButton);
	button_layout.addWidget(&StopButton);
	button_layout.addWidget(&StepButton);
	button_layout.addWidget(&ClearButton);
	info_layout.addWidget(&state);

	main_layout.addLayout(&button_layout);
	main_layout.addLayout(&info_layout);

	button_layout.setAlignment(&StepButton,Qt::AlignHCenter);
	button_layout.setAlignment(&StopButton,Qt::AlignHCenter);
	button_layout.setAlignment(&StartButton,Qt::AlignHCenter);
	info_layout.setAlignment(&state,Qt::AlignHCenter);

	setLayout(&main_layout);

	connect(&StartButton,SIGNAL(clicked()),this,SLOT(setLabelInProgress()));
	connect(&StartButton,SIGNAL(clicked()),this,SLOT(throwRun()));

	connect(&StopButton,SIGNAL(clicked()),this,SLOT(setLabelStop()));
	connect(&StopButton,SIGNAL(clicked()),this,SLOT(throwStop()));
	
	connect(&StepButton,SIGNAL(clicked()),this,SLOT(throwStep()));
	connect(&ClearButton,SIGNAL(clicked()),this,SLOT(throwClear()));
}

void Menu::setLabelInProgress()
{
	SET_GOOD_LABEL(GO_SIGN);
	this->update();
}

void Menu::setLabelStop()
{
	SET_GOOD_LABEL(STOP_SIGN);
	this->update();
} 
