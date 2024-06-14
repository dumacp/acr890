//-------------------------------------------------------------------------
//
//  Created on:		November 21, 2014
//  Created by:		Rhalf Wendel Caacbay (Lucky)
//
//  Modified on:
//  Modified by:
//
//-------------------------------------------------------------------------
#ifndef ACSEXCEPTION_H
#define ACSEXCEPTION_H

#include "AcsIncludes.h"

class AcsException
{

public:
    int8_t iNumber;
    uint8_t aStatusWord[2];
    QString sMessage;
    AcsException();
};

#endif // ACSEXCEPTION_H
