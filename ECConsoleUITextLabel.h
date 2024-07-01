//
//  ECConsoleUITextLabel.h
//  

#ifndef ECConsoleUITextLabel_h
#define ECConsoleUITextLabel_h

#include "ECConsoleUIItem.h"
#include <string>

//*****************************************************************************
// Simple UI item: a text label
// Text displays at a specific location (a single row)

class ECConsoleUITextLabel : public ECConsoleUIItem
{
public:
    // (xpos, ypos): starting position of this label, text: text to be displayed
    ECConsoleUITextLabel(int xpos, int ypos, const std::string &strText);
    
    // Get displayed text at a specific row
    // Text is relative to the item portion (i.e., relative to (xLR, yLR))
    virtual std::string GetTextAtRow(int r) const;
    
    // Get highlighted part (if any); return the row with highlight
    // if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
    // Assume: at most a single row with highlighted part
    virtual int GetHighlightPosition(int &xLeft, int &xRight) const;
    
    // Set highlight to T/F
    void SetHighlight(bool f) { fHighlight = f; }
    
    // Handle enter key
    virtual void HdlKeyEnter();
    
private:
    std::string strText;
    bool fHighlight;
};

#endif /* ECConsoleUITextLabel_h */
