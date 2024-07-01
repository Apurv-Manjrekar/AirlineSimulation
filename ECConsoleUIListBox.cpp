//
//  ECConsoleUIListBox.cpp
//  

#include "ECConsoleUIListBox.h"
using namespace std;

// specifiy the portion of the view for this list box
ECConsoleUIListBox::ECConsoleUIListBox(int xUL, int yUL, int xLR, int yLR ) : ECConsoleUIItem(xUL, yUL, xLR, yLR), indexStart(0), indexChoice(0)
{}

// Add a choice item
void ECConsoleUIListBox::AddChoice(const std::string &text)
{
    this->listChoices.push_back(text);
}

// Choose an item
void ECConsoleUIListBox::Choose(int rIndex)
{
    if(rIndex >= 0 && rIndex < this->listChoices.size())
    {
        this->indexChoice = rIndex;
    }
}

// Get the chosen one
int ECConsoleUIListBox::GetChoice() const { return indexChoice; }

void ECConsoleUIListBox::ClearChoices()
{
    this->listChoices.clear();
    this->indexStart = 0;
    this->indexChoice = 0;
}

// Get displayed text at a specific row
// Text is relative to the item portion (i.e., relative to (xLR, yLR))
std::string ECConsoleUIListBox::GetTextAtRow(int r) const
{
    int row = r - GetYUL();
    if(row >= 0 && row < 3 && indexStart + row < this->listChoices.size())
    {
        if(this->listChoices[indexStart + row].size() < this->GetWidth())
        {
            return this->listChoices[indexStart + row];
        }
        else
        {
            return this->listChoices[indexStart + row].substr(0, this->GetWidth());
        }
    }
    return "";
}

// Get highlighted part (if any); return the row with highlight
// if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
// Assume: at most a single row with highlighted part
int ECConsoleUIListBox::GetHighlightPosition(int &xLeft, int &xRight) const
{
    if(this->indexChoice >= 0 && this->indexChoice < this->listChoices.size())
    {
        xLeft = 0;
        xRight = GetWidth()-1;
        return this->indexChoice;
    }
    return -1;
}

bool ECConsoleUIListBox::IsHandlingKeys() const { return true; }

void ECConsoleUIListBox::HdlKeyUp()
{
    if(this->indexChoice > 0)
    {
        this->indexChoice--;
    }
    else if(this->indexChoice == 0 && (indexStart-3) >= 0)
    {
        indexStart-=3;
        this->indexChoice = 2;
    }
    else if(indexStart + this->indexChoice == 0)
    {
        if(this->listChoices.size() > 3)
        {
            indexStart = this->listChoices.size()-3;
            this->indexChoice = 2;
        }
        else
        {
            indexStart = 0;
            this->indexChoice = this->listChoices.size()-1;
        }
    }
    else
    {
        indexStart -= 1;
        this->indexChoice = 0;
    }

}

void ECConsoleUIListBox::HdlKeyDown()
{
    if(this->indexChoice < 2 && this->indexChoice + indexStart < this->listChoices.size()-1)
    {
        this->indexChoice++;
    }
    else if(this->indexChoice == 2 && this->listChoices.size() > (indexStart + 3))
    {
        indexStart+=3;
        this->indexChoice = 0;
    }
    else if(indexStart + this->indexChoice == this->listChoices.size()-1)
    {
        indexStart = 0;
        this->indexChoice = 0;
    }
    else
    {
        indexStart += this->indexChoice + 1;
        this->indexChoice = 0;
    }
}

void ECConsoleUIListBox::HdlKeyEnter()
{
    this->Choose(this->indexChoice);
}
// Are there any other function you might need to override?