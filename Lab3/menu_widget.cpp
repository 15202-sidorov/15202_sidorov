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
const QString Menu::HEIGHT_SIGN = "Height:";
const QString Menu::LENGTH_SIGN = "Length:";

Menu::Menu(QWidget *parent)
	:QWidget(parent)
{
	//setting text for buttons and so forth
	
	SET_GOOD_LABEL(STOP_SIGN);
	StartButton.setText("GO");
	StopButton.setText("STOP");
	StepButton.setText("STEP");
	ClearButton.setText("CLEAR");
	ResizeButton.setText("RESIZE");

	HeightEdit.setFixedSize(50,30);
	LengthEdit.setFixedSize(50,30);
	height.setText(HEIGHT_SIGN);
	length.setText(LENGTH_SIGN);

	//adding and setting widgets in menu
	button_layout.addWidget(&StartButton);
	button_layout.addWidget(&StopButton);
	button_layout.addWidget(&StepButton);
	button_layout.addWidget(&ClearButton);
	info_layout.addWidget(&state);
	info_layout.addWidget(&height);
	info_layout.addWidget(&HeightEdit);
	info_layout.addWidget(&length);
	info_layout.addWidget(&LengthEdit);
	info_layout.addWidget(&ResizeButton);

	main_layout.addLayout(&button_layout);
	main_layout.addLayout(&info_layout);

	button_layout.setAlignment(&StepButton,Qt::AlignHCenter);
	button_layout.setAlignment(&StopButton,Qt::AlignHCenter);
	button_layout.setAlignment(&StartButton,Qt::AlignHCenter);
	info_layout.setAlignment(&state,Qt::AlignHCenter);
	info_layout.setAlignment(&HeightEdit,Qt::AlignHCenter);
	info_layout.setAlignment(&LengthEdit,Qt::AlignHCenter);
	info_layout.setAlignment(&ResizeButton,Qt::AlignHCenter);

	setLayout(&main_layout);

	connect(&StartButton,SIGNAL(clicked()),this,SLOT(setLabelInProgress()));
	connect(&StartButton,SIGNAL(clicked()),this,SLOT(throwRun()));

	connect(&StopButton,SIGNAL(clicked()),this,SLOT(setLabelStop()));
	connect(&StopButton,SIGNAL(clicked()),this,SLOT(throwStop()));
	
	connect(&StepButton,SIGNAL(clicked()),this,SLOT(throwStep()));
	connect(&ClearButton,SIGNAL(clicked()),this,SLOT(throwClear()));

	connect(&ResizeButton,SIGNAL(clicked()),this,SLOT(throwResize()));
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

void Menu::throwResize()
{
	std::string height_value = HeightEdit.toPlainText().toLatin1().data();
	std::string length_value = LengthEdit.toPlainText().toLatin1().data();

	if (!height_value.size() || !length_value.size())
	{
		return;
	}

	//check whether the text is right
	for(int i = 0; i < height_value.size(); i++)
	{
		if ((height_value[i] > '9') || (height_value[i] < '0'))
		{
			return;
		}
	}

	for (int i = 0; i < length_value.size(); i++)
	{
		if ((length_value[i] > '9') || (length_value[i] < '0'))
		{
			return;
		}
	}


	int result_length = atoi(length_value.c_str());
	int result_height = atoi(height_value.c_str());

	emit Resize(result_length,result_height);
	return ;
}
