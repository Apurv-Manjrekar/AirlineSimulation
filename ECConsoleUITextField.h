//
//  ECConsoleUITextField.h
//  

#ifndef ECConsoleUITextField_h
#define ECConsoleUITextField_h

#include <string>
#include <vector>

#include "ECConsoleUIItem.h"
class ECTextViewImp;

//*****************************************************************************
// Console UI text field: 

class ECConsoleUITextField : public ECConsoleUIItem
{
public:
    // specifiy the starting point of the text field
    ECConsoleUITextField(ECTextViewImp *pTextView, int xpos, int ypos, int len);
    
    // Get displayed text at a specific row
    // Text is relative to the item portion (i.e., relative to (xLR, yLR))
    virtual std::string GetTextAtRow(int r) const;
    
    // Get highlighted part (if any); return the row with highlight
    // if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
    // Assume: at most a single row with highlighted part
    virtual int GetHighlightPosition(int &xLeft, int &xRight) const;

    // Are there any other function you might need to override?

    virtual bool IsHandlingKeys() const;
    virtual void HdlKeyEnter();
    virtual void HdlOtherKey();

    
    
private:
    ECTextViewImp* pTextView;
    bool editMode;
    std::string text;
};

#endif /* ECConsoleUITextField_h */
