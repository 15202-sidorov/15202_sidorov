#ifndef _MENU_WIDGET_H_
#define _MENU_WIDGET_H_

#include <QtGui>

class Menu: public QWidget
{
	Q_OBJECT
public:
	Menu(QWidget *parent);

signals:
	void RunGame();
	void StopGame();

private slots:
	void setLabelStop();
	void setLabelInProgress();	
private:
	QLabel state;
	QVBoxLayout layout;
	QPushButton StopButton;
	QPushButton StartButton;
	static const QString STOP_SIGN;
	static const QString GO_SIGN;
};


#endif