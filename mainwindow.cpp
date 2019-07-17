#include "mainwindow.h"
#include "include/CUESDK.h"
#include <QCoreApplication>
#include <QtGui>
#include <QtWidgets>
#include <QtCore>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <thread>

MainWindow * mwReference;

const std::vector<CorsairLedId> AREA_ONE {
                CLK_Z, CLK_X, CLK_C, CLK_V, CLK_A, CLK_S, CLK_D,
                CLK_F, CLK_R, CLK_E, CLK_W, CLK_Q, CLK_1, CLK_2, CLK_3, CLK_4, CLK_T, CLK_G, CLK_B, CLK_5};

const std::vector<CorsairLedId> AREA_TWO {
                CLK_B, CLK_N, CLK_M, CLK_CommaAndLessThan, CLK_PeriodAndBiggerThan,
                CLK_SlashAndQuestionMark, CLK_H, CLK_J, CLK_K, CLK_L, CLK_SemicolonAndColon,
                CLK_Y, CLK_U, CLK_I, CLK_O, CLK_P, CLK_6, CLK_7, CLK_8, CLK_9, CLK_0 };



LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    //Key hook callback function
    if (nCode == HC_ACTION)
    {
        switch (wParam)
        {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
            PKBDLLHOOKSTRUCT hookData = (PKBDLLHOOKSTRUCT)lParam;

            if ((wParam == WM_KEYUP) || (wParam == WM_SYSKEYUP)) { //Only on key up
                //mwReference->lightKeys((char)hookData->vkCode);
                char keyChar = (char)hookData->vkCode;
                std::thread lightingThread([&keyChar] {
                    mwReference->lightKeys(keyChar);
                });
                lightingThread.join();
            }
            else {
                break;
            }

            break;

        }

    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}



void setSize(int x, int y, QWidget* Window)
{
    //Function forces window size not allowing rescale
    Window->resize(x,y);
    Window->setMinimumSize(x,y);
    Window->setMaximumSize(x,y);
}

const char* toString(CorsairError error) //Corsair generic error conversion
{
    switch (error) {
    case CE_Success :
        return "CE_Success";
    case CE_ServerNotFound:
        return "CE_ServerNotFound";
    case CE_NoControl:
        return "CE_NoControl";
    case CE_ProtocolHandshakeMissing:
        return "CE_ProtocolHandshakeMissing";
    case CE_IncompatibleProtocol:
        return "CE_IncompatibleProtocol";
    case CE_InvalidArguments:
        return "CE_InvalidArguments";
    default:
        return "unknown error";
    }
}

std::vector<CorsairLedColor> getCharLights(char key, CorsairLedColor charColor) {
    std::vector<CorsairLedColor> litKeys;
    switch (key) {
        //Definitions for characters
        case 'A':
            litKeys.assign(8, charColor);

            litKeys[0].ledId = CLK_Z;
            litKeys[1].ledId = CLK_S;
            litKeys[2].ledId = CLK_E;
            litKeys[3].ledId = CLK_4;
            litKeys[4].ledId = CLK_R;
            litKeys[5].ledId = CLK_F;
            litKeys[6].ledId = CLK_V;
            litKeys[7].ledId = CLK_D;
        break;
        case 'Z':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_Z;
            litKeys[1].ledId = CLK_X;
            litKeys[2].ledId = CLK_C;
            litKeys[3].ledId = CLK_V;
            litKeys[4].ledId = CLK_S;
            litKeys[5].ledId = CLK_E;
            litKeys[6].ledId = CLK_1;
            litKeys[7].ledId = CLK_2;
            litKeys[8].ledId = CLK_3;
            litKeys[9].ledId = CLK_4;
        break;
        case 'Q':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_2;
            litKeys[2].ledId = CLK_3;
            litKeys[3].ledId = CLK_E;
            litKeys[4].ledId = CLK_D;
            litKeys[5].ledId = CLK_S;
            litKeys[6].ledId = CLK_A;
            litKeys[7].ledId = CLK_Q;
            litKeys[8].ledId = CLK_C;
            litKeys[9].ledId = CLK_V;
       break;
       case 'W':
           litKeys.assign(10, charColor);
           litKeys[0].ledId = CLK_1;
           litKeys[1].ledId = CLK_Q;
           litKeys[2].ledId = CLK_A;
           litKeys[3].ledId = CLK_Z;
           litKeys[4].ledId = CLK_S;
           litKeys[5].ledId = CLK_C;
           litKeys[6].ledId = CLK_F;
           litKeys[7].ledId = CLK_R;
           litKeys[8].ledId = CLK_5;
           litKeys[9].ledId = CLK_D;
        break;
        case 'S':
            litKeys.assign(6, charColor);
            litKeys[0].ledId = CLK_4;
            litKeys[1].ledId = CLK_3;
            litKeys[2].ledId = CLK_W;
            litKeys[3].ledId = CLK_D;
            litKeys[4].ledId = CLK_X;
            litKeys[5].ledId = CLK_Z;
        break;
        case 'X':
            litKeys.assign(8, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_W;
            litKeys[2].ledId = CLK_D;
            litKeys[3].ledId = CLK_V;
            litKeys[4].ledId = CLK_Z;
            litKeys[5].ledId = CLK_S;
            litKeys[6].ledId = CLK_E;
            litKeys[7].ledId = CLK_4;
        break;
        case 'E':
            litKeys.assign(12, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_2;
            litKeys[2].ledId = CLK_3;
            litKeys[3].ledId = CLK_4;
            litKeys[4].ledId = CLK_Q;
            litKeys[5].ledId = CLK_W;
            litKeys[6].ledId = CLK_E;
            litKeys[7].ledId = CLK_A;
            litKeys[8].ledId = CLK_Z;
            litKeys[9].ledId = CLK_X;
            litKeys[10].ledId = CLK_C;
            litKeys[11].ledId = CLK_V;
        break;
        case 'D':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_2;
            litKeys[2].ledId = CLK_R;
            litKeys[3].ledId = CLK_F;
            litKeys[4].ledId = CLK_X;
            litKeys[5].ledId = CLK_Z;
            litKeys[6].ledId = CLK_A;
            litKeys[7].ledId = CLK_Q;
            litKeys[8].ledId = CLK_3;
            litKeys[9].ledId = CLK_C;
        break;
        case 'C':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_4;
            litKeys[1].ledId = CLK_3;
            litKeys[2].ledId = CLK_2;
            litKeys[3].ledId = CLK_1;
            litKeys[4].ledId = CLK_Q;
            litKeys[5].ledId = CLK_A;
            litKeys[6].ledId = CLK_Z;
            litKeys[7].ledId = CLK_X;
            litKeys[8].ledId = CLK_C;
            litKeys[9].ledId = CLK_V;
        break;
        case 'R':
            litKeys.assign(6, charColor);
            litKeys[0].ledId = CLK_2;
            litKeys[1].ledId = CLK_3;
            litKeys[2].ledId = CLK_4;
            litKeys[3].ledId = CLK_Q;
            litKeys[4].ledId = CLK_A;
            litKeys[5].ledId = CLK_Z;
        break;
        case 'F':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_2;
            litKeys[2].ledId = CLK_3;
            litKeys[3].ledId = CLK_4;
            litKeys[4].ledId = CLK_Q;
            litKeys[5].ledId = CLK_A;
            litKeys[6].ledId = CLK_S;
            litKeys[7].ledId = CLK_D;
            litKeys[8].ledId = CLK_F;
            litKeys[9].ledId = CLK_Z;
        break;
        case 'V':
            litKeys.assign(7, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_Q;
            litKeys[2].ledId = CLK_S;
            litKeys[3].ledId = CLK_X;
            litKeys[4].ledId = CLK_D;
            litKeys[5].ledId = CLK_R;
            litKeys[6].ledId = CLK_5;
         break;
         case 'T':
            litKeys.assign(7, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_2;
            litKeys[2].ledId = CLK_3;
            litKeys[3].ledId = CLK_4;
            litKeys[4].ledId = CLK_W;
            litKeys[5].ledId = CLK_S;
            litKeys[6].ledId = CLK_X;
         break;
         case 'G':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_4;
            litKeys[1].ledId = CLK_3;
            litKeys[2].ledId = CLK_2;
            litKeys[3].ledId = CLK_1;
            litKeys[4].ledId = CLK_Q;
            litKeys[5].ledId = CLK_A;
            litKeys[6].ledId = CLK_Z;
            litKeys[7].ledId = CLK_X;
            litKeys[8].ledId = CLK_C;
            litKeys[9].ledId = CLK_D;
        break;
        case 'B':
            litKeys.assign(8, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_Q;
            litKeys[2].ledId = CLK_A;
            litKeys[3].ledId = CLK_S;
            litKeys[4].ledId = CLK_D;
            litKeys[5].ledId = CLK_C;
            litKeys[6].ledId = CLK_X;
            litKeys[7].ledId = CLK_Z;
        break;
        case 'Y':
            litKeys.assign(6, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_Q;
            litKeys[2].ledId = CLK_S;
            litKeys[3].ledId = CLK_X;
            litKeys[4].ledId = CLK_E;
            litKeys[5].ledId = CLK_4;
        break;
        case 'H':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_Q;
            litKeys[2].ledId = CLK_A;
            litKeys[3].ledId = CLK_Z;
            litKeys[4].ledId = CLK_S;
            litKeys[5].ledId = CLK_D;
            litKeys[6].ledId = CLK_F;
            litKeys[7].ledId = CLK_V;
            litKeys[8].ledId = CLK_R;
            litKeys[9].ledId = CLK_4;
        break;
        case 'N':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_Q;
            litKeys[2].ledId = CLK_A;
            litKeys[3].ledId = CLK_Z;
            litKeys[4].ledId = CLK_W;
            litKeys[5].ledId = CLK_D;
            litKeys[6].ledId = CLK_V;
            litKeys[7].ledId = CLK_F;
            litKeys[8].ledId = CLK_R;
            litKeys[9].ledId = CLK_4;
        break;
        case 'U':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_Q;
            litKeys[2].ledId = CLK_A;
            litKeys[3].ledId = CLK_Z;
            litKeys[4].ledId = CLK_X;
            litKeys[5].ledId = CLK_C;
            litKeys[6].ledId = CLK_V;
            litKeys[7].ledId = CLK_F;
            litKeys[8].ledId = CLK_R;
            litKeys[9].ledId = CLK_4;
        break;
        case 'J':
            litKeys.assign(8, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_2;
            litKeys[2].ledId = CLK_3;
            litKeys[3].ledId = CLK_4;
            litKeys[4].ledId = CLK_E;
            litKeys[5].ledId = CLK_D;
            litKeys[6].ledId = CLK_C;
            litKeys[7].ledId = CLK_X;
        break;
        case 'M':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_Z;
            litKeys[1].ledId = CLK_A;
            litKeys[2].ledId = CLK_Q;
            litKeys[3].ledId = CLK_1;
            litKeys[4].ledId = CLK_W;
            litKeys[5].ledId = CLK_E;
            litKeys[6].ledId = CLK_4;
            litKeys[7].ledId = CLK_R;
            litKeys[8].ledId = CLK_F;
            litKeys[9].ledId = CLK_V;
        break;
        case 'I':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_2;
            litKeys[2].ledId = CLK_3;
            litKeys[3].ledId = CLK_4;
            litKeys[4].ledId = CLK_W;
            litKeys[5].ledId = CLK_S;
            litKeys[6].ledId = CLK_Z;
            litKeys[7].ledId = CLK_X;
            litKeys[8].ledId = CLK_C;
            litKeys[9].ledId = CLK_V;
        break;
        case 'O':
            litKeys.assign(12, charColor);
            litKeys[0].ledId = CLK_4;
            litKeys[1].ledId = CLK_3;
            litKeys[2].ledId = CLK_2;
            litKeys[3].ledId = CLK_1;
            litKeys[4].ledId = CLK_Q;
            litKeys[5].ledId = CLK_A;
            litKeys[6].ledId = CLK_Z;
            litKeys[7].ledId = CLK_X;
            litKeys[8].ledId = CLK_C;
            litKeys[9].ledId = CLK_V;
            litKeys[10].ledId = CLK_F;
            litKeys[11].ledId = CLK_R;
        break;
        case 'L':
            litKeys.assign(7, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_Q;
            litKeys[2].ledId = CLK_A;
            litKeys[3].ledId = CLK_Z;
            litKeys[4].ledId = CLK_X;
            litKeys[5].ledId = CLK_C;
            litKeys[6].ledId = CLK_V;
        break;
        case 'P':
            litKeys.assign(9, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_Q;
            litKeys[2].ledId = CLK_A;
            litKeys[3].ledId = CLK_Z;
            litKeys[4].ledId = CLK_2;
            litKeys[5].ledId = CLK_S;
            litKeys[6].ledId = CLK_3;
            litKeys[7].ledId = CLK_E;
            litKeys[8].ledId = CLK_D;
        break;
        case '1':
            litKeys.assign(8, charColor);
            litKeys[0].ledId = CLK_Q;
            litKeys[1].ledId = CLK_2;
            litKeys[2].ledId = CLK_W;
            litKeys[3].ledId = CLK_S;
            litKeys[4].ledId = CLK_Z;
            litKeys[5].ledId = CLK_X;
            litKeys[6].ledId = CLK_C;
            litKeys[7].ledId = CLK_V;
        break;
        case '2':
            litKeys.assign(9, charColor);
            litKeys[0].ledId = CLK_Q;
            litKeys[1].ledId = CLK_2;
            litKeys[2].ledId = CLK_3;
            litKeys[3].ledId = CLK_E;
            litKeys[4].ledId = CLK_D;
            litKeys[5].ledId = CLK_X;
            litKeys[6].ledId = CLK_C;
            litKeys[7].ledId = CLK_Z;
            litKeys[8].ledId = CLK_V;
        break;
        case '3':
            litKeys.assign(11, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_2;
            litKeys[2].ledId = CLK_3;
            litKeys[3].ledId = CLK_4;
            litKeys[4].ledId = CLK_R;
            litKeys[5].ledId = CLK_E;
            litKeys[6].ledId = CLK_F;
            litKeys[7].ledId = CLK_V;
            litKeys[8].ledId = CLK_C;
            litKeys[9].ledId = CLK_X;
            litKeys[10].ledId = CLK_Z;
        break;
        case '4':
            litKeys.assign(9, charColor);
            litKeys[0].ledId = CLK_1;
            litKeys[1].ledId = CLK_Q;
            litKeys[2].ledId = CLK_A;
            litKeys[3].ledId = CLK_S;
            litKeys[4].ledId = CLK_D;
            litKeys[5].ledId = CLK_F;
            litKeys[6].ledId = CLK_C;
            litKeys[7].ledId = CLK_E;
            litKeys[8].ledId = CLK_3;
        break;
        case '5':
            litKeys.assign(9, charColor);
            litKeys[0].ledId = CLK_2;
            litKeys[1].ledId = CLK_3;
            litKeys[2].ledId = CLK_4;
            litKeys[3].ledId = CLK_Q;
            litKeys[4].ledId = CLK_S;
            litKeys[5].ledId = CLK_D;
            litKeys[6].ledId = CLK_C;
            litKeys[7].ledId = CLK_X;
            litKeys[8].ledId = CLK_Z;
        break;
        case '6':
            litKeys.assign(11, charColor);
            litKeys[0].ledId = CLK_4;
            litKeys[1].ledId = CLK_3;
            litKeys[2].ledId = CLK_2;
            litKeys[3].ledId = CLK_1;
            litKeys[4].ledId = CLK_Q;
            litKeys[5].ledId = CLK_A;
            litKeys[6].ledId = CLK_S;
            litKeys[7].ledId = CLK_D;
            litKeys[8].ledId = CLK_C;
            litKeys[9].ledId = CLK_X;
            litKeys[10].ledId = CLK_Z;
        break;
        case '7':
            litKeys.assign(6, charColor);
            litKeys[0].ledId = CLK_X;
            litKeys[1].ledId = CLK_S;
            litKeys[2].ledId = CLK_W;
            litKeys[3].ledId = CLK_2;
            litKeys[4].ledId = CLK_3;
            litKeys[5].ledId = CLK_4;
        break;
        case '8':
            litKeys.assign(9, charColor);
            litKeys[0].ledId = CLK_2;
            litKeys[1].ledId = CLK_3;
            litKeys[2].ledId = CLK_W;
            litKeys[3].ledId = CLK_E;
            litKeys[4].ledId = CLK_A;
            litKeys[5].ledId = CLK_D;
            litKeys[6].ledId = CLK_Q;
            litKeys[7].ledId = CLK_Z;
            litKeys[8].ledId = CLK_X;
        break;
        case '9':
            litKeys.assign(10, charColor);
            litKeys[0].ledId = CLK_2;
            litKeys[1].ledId = CLK_W;
            litKeys[2].ledId = CLK_3;
            litKeys[3].ledId = CLK_E;
            litKeys[4].ledId = CLK_4;
            litKeys[5].ledId = CLK_R;
            litKeys[6].ledId = CLK_F;
            litKeys[7].ledId = CLK_V;
            litKeys[8].ledId = CLK_C;
            litKeys[9].ledId = CLK_X;
        break;
        case '0':
            litKeys.assign(12, charColor);
            litKeys[0].ledId = CLK_4;
            litKeys[1].ledId = CLK_3;
            litKeys[2].ledId = CLK_2;
            litKeys[3].ledId = CLK_1;
            litKeys[4].ledId = CLK_Q;
            litKeys[5].ledId = CLK_A;
            litKeys[6].ledId = CLK_Z;
            litKeys[7].ledId = CLK_X;
            litKeys[8].ledId = CLK_C;
            litKeys[9].ledId = CLK_V;
            litKeys[10].ledId = CLK_F;
            litKeys[11].ledId = CLK_R;
        break;
    }
    return litKeys;
}


std::vector<CorsairLedColor> getAvailableKeys(bool checkColor, int r, int g, int b)
{
    //get all keys on board
    //if checkColor is true will return only keys with matching colors to input
    auto colorsVector = std::vector<CorsairLedColor>();
    auto colors = mwReference->currentbgColors();
    auto ledPositions = CorsairGetLedPositions();
    if (ledPositions) {
        for (auto i = 0; i < ledPositions->numberOfLed; i++) {
            auto ledId = ledPositions->pLedPosition[i].ledId;
            if (checkColor) {
                CorsairLedColor testColor{ ledId };
                CorsairGetLedsColors(1, &testColor);
                if (testColor.r == r && testColor.g == g && testColor.b == b) {
                    colorsVector.push_back(testColor);

                }
            }
            else {
                colorsVector.push_back(CorsairLedColor{ ledId, colors[0], colors[1], colors[2] });
            }
        }
    }

    return colorsVector;
}

std::vector<CorsairLedColor> getBoardColors(int area) { // 0 - Whole board 1 - First character 2 - second character 3 - All non active keys
    auto bgColors = mwReference->currentbgColors();
    switch (area) {
        case 0:
        {
            return getAvailableKeys(false, NULL, NULL, NULL); //Return all board keys

        }
        case 1:
        {
        //return all keys in area one as defined at top of file
            std::vector<CorsairLedColor> areaKeys;
            for (auto &ledId : AREA_ONE) {
                areaKeys.push_back(CorsairLedColor{ ledId, bgColors[0], bgColors[1], bgColors[2] });
            }
            return areaKeys;
        }
        case 2:
        {
            //return all keys in area two as defined at top of file
            std::vector<CorsairLedColor> areaKeys;
            for (auto &ledId : AREA_TWO) {
                areaKeys.push_back(CorsairLedColor{ ledId, bgColors[0], bgColors[1], bgColors[2] });
            }
            return areaKeys;
        }
        case 3:
        {
            //Find all unlit up keys
            std::vector<int> rgbValues = mwReference->currentColors();
            std::vector<int> rgbBValues = mwReference->currentbgColors();
            std::vector<CorsairLedColor> areaKeys;
            auto litKeys = getAvailableKeys(true, rgbValues[0], rgbValues[1], rgbValues[2]);
            auto allKeys = getBoardColors(0);
            if (litKeys.empty()) {
                return allKeys;
            } else {
                std::vector<CorsairLedId> litIds;
                std::transform(litKeys.begin(), litKeys.end(), std::back_inserter(litIds), [](CorsairLedColor c) { return c.ledId; }); //Create vector of led ids from lit keys
                for (auto& led : allKeys) { //Remove all keys in vector that are in the second sector as to prevent over translation
                    if (std::find(litIds.begin(), litIds.end(), led.ledId) != litIds.end()) { //Check if led ID is in lit up keys

                    }
                    else {
                        areaKeys.push_back(CorsairLedColor{led.ledId, rgbBValues[0], rgbBValues[1], rgbBValues[2]});
                    }

                }


            }
            return areaKeys;

        }
        default:
            throw std::runtime_error("Failed to find any keys to clear");

    }


}

void ColorWindow::showWindow() {
    // Show color changing window and set modality
    setModal(true);
    setSize(200, 200, this);
    std::vector<int> colors;
    if (forBackground) {
        colors = mwReference->currentbgColors();
    } else {
        colors = mwReference->currentColors();
    }
    redLabel->setGeometry(55, 7, 40, 40);
    redBox->setGeometry(95, 10, 50, 30);
    redBox->setRange(0, 255);
    redBox->setValue(colors[0]);
    greenLabel->setGeometry(55, 50, 40, 30);
    greenBox->setGeometry(95, 50, 50, 30);
    greenBox->setRange(0, 255);
    greenBox->setValue(colors[1]);
    blueLabel->setGeometry(55, 90, 40, 30);
    blueBox->setGeometry(95, 90, 50, 30);
    blueBox->setRange(0, 255);
    blueBox->setValue(colors[2]);
    submitButton->setGeometry(0, 150, 200, 50);
    if (forBackground) {
        connect(submitButton, &QPushButton::pressed, mwReference, &MainWindow::changeBackgroundColor);
    } else {
        connect(submitButton, &QPushButton::pressed, mwReference, &MainWindow::changeColor);
    }

    show();
}

ColorWindow::ColorWindow(bool background)
    : QDialog()

{
    setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    forBackground = background;
}

ColorWindow::~ColorWindow() {

}

std::vector<int> MainWindow::currentColors() {
    return std::vector<int>{r, g, b};
}

std::vector<int> MainWindow::currentbgColors() {
    //Return current background colors
    return std::vector<int>{bR, bG, bB};
}


int MainWindow::changeColor() {
    //Changed classes color characters
    r = changeColorWindow->redBox->value();
    g = changeColorWindow->greenBox->value();
    b = changeColorWindow->blueBox->value();
    auto keys = getBoardColors(0);
    CorsairSetLedsColors(static_cast<int>(keys.size()), keys.data());
    changeColorWindow->hide();
    return 1;
}

int MainWindow::changeBackgroundColor() {
    //Change the classes background color properties
    bR = changeBackgroundWindow->redBox->value();
    bG = changeBackgroundWindow->greenBox->value();
    bB = changeBackgroundWindow->blueBox->value();
    auto keys = getBoardColors(0);
    CorsairSetLedsColors(static_cast<int>(keys.size()), keys.data());
    changeBackgroundWindow->hide();
    return 1;
}

int MainWindow::lightKeys(char keyChar) {
    //Set color for character light up
    CorsairLedColor charColor;
    charColor.r = r;
    charColor.g = g;
    charColor.b = b;
    //Set background color
    CorsairLedColor backColor;
    backColor.r = bR;
    backColor.g = bG;
    backColor.b = bB;
    auto keys = getBoardColors(2);
    CorsairSetLedsColors(static_cast<int>(keys.size()), keys.data()); //Clear the second character from board
    auto currentKeys = getAvailableKeys(true, r, g, b); //Get all lit up keys (should only be the first character)
    if (currentKeys.empty()) {

    }
    else {
        std::vector<CorsairLedColor> newKeys;
        for (auto &led : currentKeys) { //Remove all keys in vector that are in the second sector as to prevent over translation
            if (std::find(AREA_TWO.begin(), AREA_TWO.end(), led.ledId) != AREA_TWO.end()) {

            }
            else {
                newKeys.push_back(led);
            }

        }


        std::vector<CorsairLedColor> translatedKeys;
        for (auto &ledColor : newKeys) { //Translate keys by a vector of 5
            CorsairLedId newID = (CorsairLedId)((int)ledColor.ledId + 5);

            translatedKeys.push_back(CorsairLedColor{ newID, r, g, b });
        }

        auto keys = getBoardColors(0);
        CorsairSetLedsColors(static_cast<int>(keys.size()), keys.data());	//Clear board

        CorsairSetLedsColors(static_cast<int>(translatedKeys.size()), translatedKeys.data()); //Light translated keys
        std::this_thread::sleep_for(std::chrono::milliseconds(35)); //Necessary to allow program to cacth up with new lit up keys
    }
    auto keysOne = getBoardColors(1);
    CorsairSetLedsColors(static_cast<int>(keysOne.size()), keysOne.data()); //Remove old char
    std::vector<CorsairLedColor> litKeys;
    auto newKeys = getCharLights(keyChar, charColor);
    CorsairSetLedsColors(static_cast<int>(newKeys.size()), newKeys.data()); //Light new character key
    std::this_thread::sleep_for(std::chrono::milliseconds(35)); //Neccessary to allow the getBoardColors function to catch up with lit up keys
    auto unusedKeys = getBoardColors(3);
    CorsairSetLedsColors(static_cast<int>(unusedKeys.size()), unusedKeys.data()); //Set lights for all unlit keys
    return 1;
}





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("See It Corsair");
    mwReference = this;
    CorsairPerformProtocolHandshake(); //Corsair iCue initialisation
    if (const auto error = CorsairGetLastError()) { //Check for corsair initialisation error
        std::cout << "Handshake failed: " << toString(error) << "\nPress any key to quit." << std::endl;
        getchar();
        QCoreApplication::quit();
    }
    auto colorsVector = getBoardColors(0); // Clear board on start up
    if (colorsVector.empty()) { //Check keys are available
        std::runtime_error("No keys available on keyboard"); //Quit if no keys can be found
        QCoreApplication::quit();
    }

    CorsairSetLedsColors(static_cast<int>(colorsVector.size()), colorsVector.data()); //Clear board
    setSize(300, 100, this); //Scale window
    QPushButton* changeColorButton = new QPushButton("Change Light Color", this);
    QPushButton* changeBackgroundButton = new QPushButton("Change Background Light Color", this);
    changeColorButton->setGeometry(0, 0, 300, 50);
    changeBackgroundButton->setGeometry(0, 50, 300, 50);
    //Link buttons to change color functions
    connect(changeColorButton, &QPushButton::pressed, changeColorWindow, &ColorWindow::showWindow);
    connect(changeBackgroundButton, &QPushButton::pressed, changeBackgroundWindow, &ColorWindow::showWindow);


    HHOOK hhklowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0); //Initialise the hook
}

MainWindow::~MainWindow()
{
    UnhookWindowsHookEx(hhklowLevelKybd); //Unhook key hook
}
