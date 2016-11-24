#include "menu_widget.h"

#define SET_GOOD_LABEL(SIGN) \
	QString labelText = "<P><b><i><FONT COLOR='#ff0000' FONT SIZE = 4>"; \
	labelText.append(SIGN); \
	labelText.append("</i></b></P></br>"); \
	state.setText(labelText);

const QString Menu::STOP_SIGN = "Stop";
const QString Menu::GO_SIGN = "In progress";

Menu::Menu(QWidget *parent)
	:QWidget(parent)
{
	//setting text for buttons and so forth
	
	SET_GOOD_LABEL(STOP_SIGN)
	StartButton.setText("GO");
	StopButton.setText("STOP");
	
	//adding and setting widgets in menu
	layout.addWidget(&StartButton);
	layout.addWidget(&StopButton);
	layout.addWidget(&state);

	layout.setAlignment(&StopButton,Qt::AlignHCenter);
	layout.setAlignment(&StartButton,Qt::AlignHCenter);
	layout.setAlignment(&state,Qt::AlignHCenter);

	setLayout(&layout);

	connect(&StartButton,SIGNAL(clicked()),this,SLOT(setLabelInProgress()));
	connect(&StopButton,SIGNAL(clicked()),this,SLOT(setLabelStop()));
}

void Menu::setLabelInProgress()
{
	SET_GOOD_LABEL(GO_SIGN)
	this->update();
}

void Menu::setLabelStop()
{
	SET_GOOD_LABEL(STOP_SIGN)
	this->update();
} 