//-------------------------------------------------------------------------
//
//  Created on:		October 9, 2014
//  Created by:		Rhalf Wendel Caacbay (Lucky)
//
//  Modified on:
//  Modified by:
//
//-------------------------------------------------------------------------
#ifndef ACSKEYPAD_H
#define ACSKEYPAD_H

#include "AcsIncludes.h"

class AcsKeypad : public QObject
{

    Q_OBJECT

public:
    uint64_t uTimeout;
    uint64_t keyType;
    uint64_t keyCode;

    enum Keypad
    {
        LEFT = 16777264,
        DOWN = 16777265,
        UP = 16777266,
        RIGHT = 16777267,

        POWER = 16777483,
        EXIT = 16777216,
        CLEAR = 16777219,
        ENTER = 16777220,
        FUNCTION = 16777249,
        DOT = 16777268,

        NUMBER0 = 48,
        NUMBER1 = 49,
        NUMBER2 = 50,
        NUMBER3 = 51,
        NUMBER4 = 52,
        NUMBER5 = 53,
        NUMBER6 = 54,
        NUMBER7 = 55,
        NUMBER8 = 56,
        NUMBER9 = 57

    };

    enum KeyMode
    {
        NUMBER,
        UPPERCASE,
        LOWERCASE,
        SPECIAL
    };

    AcsKeypad();
    ~AcsKeypad();

    bool processKey(QWidget *pParent, QObject *pObject, QEvent *pEvent);
    uint8_t mode(KeyMode eMode);

private:
    QLineEdit *_pLineEdit;
    QTextEdit *_pTextEdit;

    uint8_t uKeyCount;
    uint64_t uKeyStroke;
    KeyMode eKeyMode;
    uint64_t uKeyTimeout;

    QTimer timerTimeout;

public slots:
    void keyTimeout();
};

#endif // ACSKEYPAD_H
