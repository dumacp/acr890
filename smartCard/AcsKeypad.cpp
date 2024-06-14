//-------------------------------------------------------------------------
//
//  Created on:		November 21, 2014
//  Created by:		Rhalf Wendel Caacbay (Lucky)
//
//  Modified on:
//  Modified by:
//
//-------------------------------------------------------------------------
#include "AcsKeypad.h"

AcsKeypad::AcsKeypad()
{
    timerTimeout.setSingleShot(1);
    connect(&timerTimeout, SIGNAL(timeout()), this, SLOT(keyTimeout()));
}

AcsKeypad::~AcsKeypad()
{
}

bool AcsKeypad::processKey(QWidget *pParent, QObject *pObject, QEvent *pEvent)
{
    uint8_t uDebugger = 0;
    uKeyTimeout = 500;

    if (pEvent->type() != QEvent::KeyPress)
        return false;

    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(pEvent);

    QLineEdit *pLineEdit = qobject_cast<QLineEdit *>((pObject));
    bool bLineEdit = false;

    QTextEdit *pTextEdit = qobject_cast<QTextEdit *>((pObject));
    bool bTextEdit = false;

    _pLineEdit = pLineEdit;

    _pTextEdit = pTextEdit;

    if (pLineEdit)
        bLineEdit = true;
    else if (pTextEdit)
        bTextEdit = true;
    else
        return false;

    switch (keyEvent->key())
    {
    case AcsKeypad::EXIT:
    {
        break;
    }
    case AcsKeypad::CLEAR:
    {
        if (bLineEdit)
            _pLineEdit->backspace();
        else
        {
            _pTextEdit->textCursor().deletePreviousChar();
        }
        break;
    }
    case AcsKeypad::FUNCTION:
    {
        if (eKeyMode == LOWERCASE)
        {
            eKeyMode = UPPERCASE;
        }
        else if (eKeyMode == UPPERCASE)
        {
            eKeyMode = NUMBER;
        }
        else if (eKeyMode == NUMBER)
        {
            eKeyMode = LOWERCASE;
        }
        break;
    }
    case AcsKeypad::NUMBER0:
    {
        if (bLineEdit)
        {
            if (eKeyMode == LOWERCASE || eKeyMode == UPPERCASE)
                _pLineEdit->insert(" ");
            if (eKeyMode == NUMBER)
                _pLineEdit->insert("0");
        }
        else
        {
            if (eKeyMode == LOWERCASE || eKeyMode == UPPERCASE)
                _pTextEdit->insertPlainText(" ");
            if (eKeyMode == NUMBER)
                _pTextEdit->insertPlainText("0");
        }
        break;
    }
    case AcsKeypad::NUMBER1:
    {
        if (uKeyStroke != (uint64_t)keyEvent->key())
        {
            uKeyStroke = (uint64_t)keyEvent->key();
            uKeyCount = 0;
        }
        if (eKeyMode == LOWERCASE || eKeyMode == UPPERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("#");
                else
                    _pTextEdit->insertPlainText("#");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("#");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("#");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("@");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("@");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("-");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("-");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 4:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("*");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("*");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
                break;
            }
        }
        if (eKeyMode == NUMBER)
        {
            if (bLineEdit)
                _pLineEdit->insert("1");
            else
                _pTextEdit->insertPlainText("1");
        }
        break;
    }
    case AcsKeypad::NUMBER2:
    {
        if (uKeyStroke != (uint64_t)keyEvent->key())
        {
            uKeyStroke = (uint64_t)keyEvent->key();
            uKeyCount = 0;
        }
        if (eKeyMode == LOWERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("a");
                else
                    _pTextEdit->insertPlainText("a");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("a");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("a");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("b");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("b");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("c");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("c");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == UPPERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("A");
                else
                    _pTextEdit->insertPlainText("A");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("A");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("A");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("B");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("B");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("C");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("C");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == NUMBER)
        {
            if (bLineEdit)
                _pLineEdit->insert("2");
            else
                _pTextEdit->insertPlainText("2");
        }

        break;
    }
    case AcsKeypad::NUMBER3:
    {
        if (uKeyStroke != (uint64_t)keyEvent->key())
        {
            uKeyStroke = (uint64_t)keyEvent->key();
            uKeyCount = 0;
        }
        if (eKeyMode == LOWERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("d");
                else
                    _pTextEdit->insertPlainText("d");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("d");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("d");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("e");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("e");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("f");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("f");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == UPPERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("D");
                else
                    _pTextEdit->insertPlainText("D");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("D");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("D");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("E");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("E");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("F");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("F");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == NUMBER)
        {
            if (bLineEdit)
                _pLineEdit->insert("3");
            else
                _pTextEdit->insertPlainText("3");
        }
        break;
    }
    case AcsKeypad::NUMBER4:
    {
        if (uKeyStroke != (uint64_t)keyEvent->key())
        {
            uKeyStroke = (uint64_t)keyEvent->key();
            uKeyCount = 0;
        }
        if (eKeyMode == LOWERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("g");
                else
                    _pTextEdit->insertPlainText("g");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("g");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("g");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("h");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("h");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("i");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("i");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == UPPERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("G");
                else
                    _pTextEdit->insertPlainText("G");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("G");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("G");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("H");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("H");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("I");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("I");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == NUMBER)
        {
            if (bLineEdit)
                _pLineEdit->insert("4");
            else
                _pTextEdit->insertPlainText("4");
        }
        break;
    }
    case AcsKeypad::NUMBER5:
    {
        if (uKeyStroke != (uint64_t)keyEvent->key())
        {
            uKeyStroke = (uint64_t)keyEvent->key();
            uKeyCount = 0;
        }
        if (eKeyMode == LOWERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("j");
                else
                    _pTextEdit->insertPlainText("j");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("j");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("j");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("k");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("k");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("l");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("l");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == UPPERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("J");
                else
                    _pTextEdit->insertPlainText("J");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("J");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("J");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("K");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("K");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("L");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("L");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == NUMBER)
        {
            if (bLineEdit)
                _pLineEdit->insert("5");
            else
                _pTextEdit->insertPlainText("5");
        }
        break;
    }
    case AcsKeypad::NUMBER6:
    {
        if (uKeyStroke != (uint64_t)keyEvent->key())
        {
            uKeyStroke = (uint64_t)keyEvent->key();
            uKeyCount = 0;
        }
        if (eKeyMode == LOWERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("m");
                else
                    _pTextEdit->insertPlainText("m");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("m");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("m");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("n");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("n");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("o");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("o");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == UPPERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("M");
                else
                    _pTextEdit->insertPlainText("M");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("M");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("M");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("N");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("N");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("O");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("O");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == NUMBER)
        {
            if (bLineEdit)
                _pLineEdit->insert("6");
            else
                _pTextEdit->insertPlainText("6");
        }
        break;
    }
    case AcsKeypad::NUMBER7:
    {
        if (uKeyStroke != (uint64_t)keyEvent->key())
        {
            uKeyStroke = (uint64_t)keyEvent->key();
            uKeyCount = 0;
        }
        if (eKeyMode == LOWERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("p");
                else
                    _pTextEdit->insertPlainText("p");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("p");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("p");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("q");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("q");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("r");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("r");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 4:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("s");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("s");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == UPPERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("P");
                else
                    _pTextEdit->insertPlainText("P");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("P");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("P");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("Q");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("Q");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("R");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("R");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 4:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("S");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("S");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == NUMBER)
        {
            if (bLineEdit)
                _pLineEdit->insert("7");
            else
                _pTextEdit->insertPlainText("7");
        }
        break;
    }
    case AcsKeypad::NUMBER8:
    {
        if (uKeyStroke != (uint64_t)keyEvent->key())
        {
            uKeyStroke = (uint64_t)keyEvent->key();
            uKeyCount = 0;
        }
        if (eKeyMode == LOWERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("t");
                else
                    _pTextEdit->insertPlainText("t");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("t");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("t");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("u");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("u");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("v");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("v");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == UPPERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("T");
                else
                    _pTextEdit->insertPlainText("T");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("T");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("T");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("U");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("U");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("V");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("V");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == NUMBER)
        {
            if (bLineEdit)
                _pLineEdit->insert("8");
            else
                _pTextEdit->insertPlainText("8");
        }
        break;
    }
    case AcsKeypad::NUMBER9:
    {
        if (uKeyStroke != (uint64_t)keyEvent->key())
        {
            uKeyStroke = (uint64_t)keyEvent->key();
            uKeyCount = 0;
        }
        if (eKeyMode == LOWERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("w");
                else
                    _pTextEdit->insertPlainText("w");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("w");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("w");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("x");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("x");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("y");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("y");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 4:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("z");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("z");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == UPPERCASE)
        {
            switch (uKeyCount)
            {
            case 0:
                if (bLineEdit)
                    _pLineEdit->insert("W");
                else
                    _pTextEdit->insertPlainText("W");
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 1:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("W");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("W");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 2:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("X");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("X");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 3:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("Y");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("Y");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount++;
                break;
            case 4:
                if (bLineEdit)
                {
                    _pLineEdit->backspace();
                    _pLineEdit->insert("Z");
                }
                else
                {
                    _pTextEdit->textCursor().deletePreviousChar();
                    _pTextEdit->insertPlainText("Z");
                }
                timerTimeout.start(uKeyTimeout);
                uKeyCount = 1;
            }
        }
        if (eKeyMode == NUMBER)
        {
            if (bLineEdit)
                _pLineEdit->insert("9");
            else
                _pTextEdit->insertPlainText("9");
        }

        break;
    }
    case AcsKeypad::DOT:
    {
        if (uKeyStroke != (uint64_t)keyEvent->key())
        {
            uKeyStroke = (uint64_t)keyEvent->key();
            uKeyCount = 0;
        }

        switch (uKeyCount)
        {
        case 0:
            if (bLineEdit)
                _pLineEdit->insert(".");
            else
                _pTextEdit->insertPlainText(".");
            timerTimeout.start(uKeyTimeout);
            uKeyCount++;
            break;
        case 1:
            if (bLineEdit)
            {
                _pLineEdit->backspace();
                _pLineEdit->insert(".");
            }
            else
            {
                _pTextEdit->textCursor().deletePreviousChar();
                _pTextEdit->insertPlainText(".");
            }
            timerTimeout.start(uKeyTimeout);
            uKeyCount++;
            break;
        case 2:
            if (bLineEdit)
            {
                _pLineEdit->backspace();
                _pLineEdit->insert(",");
            }
            else
            {
                _pTextEdit->textCursor().deletePreviousChar();
                _pTextEdit->insertPlainText(",");
            }
            timerTimeout.start(uKeyTimeout);
            uKeyCount++;
            break;
        case 3:
            if (bLineEdit)
            {
                _pLineEdit->backspace();
                _pLineEdit->insert("?");
            }
            else
            {
                _pTextEdit->textCursor().deletePreviousChar();
                _pTextEdit->insertPlainText("?");
            }
            timerTimeout.start(uKeyTimeout);
            uKeyCount++;
            break;
        case 4:
            if (bLineEdit)
            {
                _pLineEdit->backspace();
                _pLineEdit->insert("!");
            }
            else
            {
                _pTextEdit->textCursor().deletePreviousChar();
                _pTextEdit->insertPlainText("!");
            }
            timerTimeout.start(uKeyTimeout);
            uKeyCount = 1;
        }

        break;
    }

    case AcsKeypad::LEFT:
        if (bLineEdit)
            _pLineEdit->cursorBackward(false, 1);
        else
            _pTextEdit->moveCursor(QTextCursor::Left);

        break;

    case AcsKeypad::RIGHT:
        if (bLineEdit)
            _pLineEdit->cursorForward(false, 1);
        else
            _pTextEdit->moveCursor(QTextCursor::Right);

        break;

    case AcsKeypad::ENTER:
        if (bLineEdit)
            _pLineEdit->nextInFocusChain()->setFocus();
        else
            _pTextEdit->nextInFocusChain()->setFocus();
        break;
    }

    if (uDebugger)
        AcsHelper::printDebug(QString::number(keyEvent->key()));

    return true;
}

void AcsKeypad::keyTimeout()
{
    uKeyCount = 0;
}

uint8_t AcsKeypad::mode(KeyMode eMode)
{
    eKeyMode = eMode;
    return 0;
}
