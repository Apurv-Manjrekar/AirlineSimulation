//
//  ECConsoleUIView.h
//  

#ifndef ECConsoleUIView_h
#define ECConsoleUIView_h

#include <vector>
#include <string>
#include "ECObserver.h"

class ECTextViewImp;
class ECConsoleUIItem;


//*****************************************************************************
// Generic console UI view
// Displays some info on the screen, and then respond to user actions

class ECConsoleUIView : public ECObserver
{
public:
    ECConsoleUIView(ECTextViewImp *pTextView);
    virtual ~ECConsoleUIView();
    
    // Add UI item
    void AddUIItem(ECConsoleUIItem *pUIItem);
    
    // Display this view
    virtual void Refresh();
    
    // Get the number of rows in view
    int GetRowNumInView() const;
    
    // Get the number of rows in view
    int GetColNumInView() const;
    
    // Respond to key events
    virtual void Update();
    
    // Get textview
    ECTextViewImp *GetView() { return pTextView; }
    
private:
    // Compose a row in the view
    std::string ComposeRow(int r) const;
    
    // Is there a UI item in this row? if so, return the index of this UI item with the rightmost position; otehrwise, return -1
    int GetRightmostUIItemAtRow(int r) const;
    
    ECTextViewImp *pTextView;
    std::vector<ECConsoleUIItem *> listUIItems;
    int indexActiveUI;
};

#endif /* ECConsoleUIView_h */
