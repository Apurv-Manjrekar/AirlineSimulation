//
//  ECConsoleUIItem.h
//  

#ifndef ECConsoleUIItem_h
#define ECConsoleUIItem_h

#include <vector>
#include <string>

//*****************************************************************************
// Generic console UI item
// A part of UI that interacts with the user

class ECConsoleUIItem
{
public:
    // Each UI item occupies a portion of the view
    // Upper left corner (xUL, yUL), lower right corner (xLR, yLR)
    ECConsoleUIItem(int xULIn, int yULIn, int xLRIn, int yLRIn) : xUL(xULIn), yUL(yULIn), xLR(xLRIn), yLR(yLRIn) {}
    
    virtual ~ECConsoleUIItem() {}
    
    // Get position info
    int GetXUL() const { return xUL; }
    int GetYUL() const { return yUL; }
    int GetXLR() const { return xLR; }
    int GetYLR() const { return yLR; }
    // Get size
    int GetWidth() const { return GetXLR()-GetXUL()+1; }
    int GetHeight() const { return GetYLR()-GetYUL()+1; }
    
    // Get displayed text at a specific row (absolute row in the screen/view sense; not specific to the item)
    // Text is relative to the item portion (i.e., relative to (xLR, yLR))
    virtual std::string GetTextAtRow(int r) const = 0;
    
    // Get highlighted part (if any); return the row with highlight
    // if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
    // Assume: at most a single row with highlighted part
    virtual int GetHighlightPosition(int &xLeft, int &xRight) const = 0;
    
    // key handling tasks; default: do noting
    // Is responding to keys? if no, won't bother to cycle through it
    virtual bool IsHandlingKeys() const { return false; }
    // Handle up key
    virtual void HdlKeyUp() {}
    // Handle down key
    virtual void HdlKeyDown() {}
    // Handle enter key
    virtual void HdlKeyEnter() {}
    // Handle other keys
    virtual void HdlOtherKey() {}
    
    // Utilities
    bool IsIntersectingRow(int r) const { return r >= yUL && r <= yLR; }
    
private:
    int xUL;
    int yUL;
    int xLR;
    int yLR;
};


#endif /* ECConsoleUIItem_h */
