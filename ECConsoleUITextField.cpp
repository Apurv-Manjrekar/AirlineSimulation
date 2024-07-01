//
//  ECConsoleUITextField.cpp
//  

#include "ECConsoleUITextField.h"
#include "ECTextViewImp.h"

using namespace std;

ECConsoleUITextField::ECConsoleUITextField(ECTextViewImp *pTextView, int xpos, int ypos, int len) : ECConsoleUIItem(xpos, ypos, xpos+len, ypos), pTextView(pTextView), editMode(false)
{}
    
// Get displayed text at a specific row
// Text is relative to the item portion (i.e., relative to (xLR, yLR))
std::string ECConsoleUITextField::GetTextAtRow(int r) const
{
    if(r == GetYUL())
    {
        return ": " + text;
    }
    else
    {
        return "";
    }
}

// Get highlighted part (if any); return the row with highlight
// if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
// Assume: at most a single row with highlighted part
int ECConsoleUITextField::GetHighlightPosition(int &xLeft, int &xRight) const
{
    return -1;
}

// Are there any other function you might need to override?

bool ECConsoleUITextField::IsHandlingKeys() const { return true; }

void ECConsoleUITextField::HdlKeyEnter()
{
    editMode = true;
    pTextView->Refresh();
}

void ECConsoleUITextField::HdlOtherKey()
{
    if(editMode)
    {
        int key = pTextView->GetPressedKey();
        if(key == BACKSPACE)
        {
            if(!text.empty())
            {
                text.pop_back();
                pTextView->Refresh();
            }
        }
        else if(key == CTRL_C)
        {
            editMode = false;
            pTextView->Refresh();
        }
        else if(text.length() < GetWidth()-2)
        {
            text += key;
            pTextView->Refresh();
        }
    }
}

