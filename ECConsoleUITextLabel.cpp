//
//  ECConsoleUITextLabel.cpp
//  

#include "ECConsoleUITextLabel.h"

using namespace std;

//*****************************************************************************
// Simple UI item: a text label
// Text displays at a specific location (a single row)

// (xpos, ypos): starting position of this label, text: text to be displayed
ECConsoleUITextLabel :: ECConsoleUITextLabel(int xpos, int ypos, const std::string &strTextIn) : ECConsoleUIItem(xpos, ypos, xpos+(int)strTextIn.size()-1, ypos), strText(strTextIn), fHighlight(false)
{
    if( strText.size() == 0)
    {
        throw string("ECConsoleUITextLabel: text cannot be empty");
    }
}

// Get displayed text at a specific row
// Text is relative to the item portion (i.e., relative to (xLR, yLR))
std::string ECConsoleUITextLabel :: GetTextAtRow(int r) const
{
    string strOut;
    if( r == GetYUL() )
    {
        strOut = this->strText;
    }
    return strOut;
}

// Get highlighted part (if any); return the row with highlight
// if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
// Assume: at most a single row with highlighted part
int ECConsoleUITextLabel :: GetHighlightPosition(int &xLeft, int &xRight) const
{
    if( fHighlight == false )
    {
        return -1;
    }
    else
    {
        xLeft = 0;
        xRight = GetWidth()-1;
        return 0;
    }
}

// Handle enter key
void ECConsoleUITextLabel :: HdlKeyEnter()
{
    // do nothing
    //SetHighlight( !fHighlight );
}
