#ifndef _MENU_WIDGET_H_
#define _MENU_WIDGET_H_

#include <QtGui>

class Menu: public QWidget
{
	Q_OBJECT
public:
	explicit Menu(QWidget *parent);

signals:
	void RunGame();
	void StopGame();
	void MakeStep();
	void ClearFeild();

private slots:
	void setLabelStop();
	void setLabelInProgress();
	void throwStep() {emit MakeStep();};
	void throwClear() {emit ClearFeild();};
	void throwStop() {emit StopGame();};
	void throwRun() {emit RunGame();};

private:
	QLabel state;
	QTextEdit WidthEdit;
	QTextEdit HeightEdit;
	QHBoxLayout button_layout;
	QHBoxLayout info_layout; 
	QVBoxLayout main_layout;
	
	QPushButton StopButton;
	QPushButton StartButton;
	QPushButton StepButton;
	QPushButton ClearButton;
	static const QString STOP_SIGN;
	static const QString GO_SIGN;

	inline void SET_GOOD_LABEL(QString sign);
	bool checkCorrectSize();
};

#endif