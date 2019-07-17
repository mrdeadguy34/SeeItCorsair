#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "include/CUESDK.h"
#include <Windows.h>
#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include <QtCore>



class ColorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ColorWindow(bool background);
    ~ColorWindow();

    void showWindow();
    //Set up for widgets in dialog
    QLabel* redLabel = new QLabel("Red:", this);
    QLabel* greenLabel = new QLabel("Green", this);
    QLabel* blueLabel = new QLabel("Blue:", this);
    QSpinBox* redBox = new QSpinBox(this);
    QSpinBox* greenBox = new QSpinBox(this);
    QSpinBox* blueBox = new QSpinBox(this);
    QPushButton* submitButton = new QPushButton("Submit", this);

private:
    bool forBackground; //Used to differentiate between changing background color and changing char light color
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int lightKeys(char keyChar); //Function to light the keys for new character and translate old lights over by 5
    std::vector<int> currentColors(); //Returns a vector of classes current r, g, b values
    std::vector<int> currentbgColors(); //Returns a vector of classes current bR, bG, bB values

    ~MainWindow();

public slots:
    int changeColor(); //Changes classes r, g, b values
    int changeBackgroundColor(); //Changes classes bR, bG, bB colors

private:
    QPushButton* changeColorButton;
    ColorWindow* changeColorWindow = new ColorWindow(false); //Window to change char light color
    ColorWindow* changeBackgroundWindow = new ColorWindow(true); //Window to change background light color


    HHOOK hhklowLevelKybd;
    //Colors for the keys which represent the character
    int r = 255;
    int g = 0;
    int b = 0;
    //Colors for the background keys unlit by characters
    int bR = 255;
    int bG = 255;
    int bB = 255;


};



#endif // MAINWINDOW_H
