// Test code for console UI
#include "ECTextViewImp.h"
#include "ECConsoleUIView.h"
#include "ECConsoleUITextLabel.h"
#include "ECConsoleUITextField.h"
#include "ECConsoleUIListBox.h"
#include "ECConsoleUIButton.h"
#include <iostream>

using namespace  std;

// construct a simple UI
static void Test1(ECConsoleUIView &viewTest)
{
    // create several labels
    ECConsoleUITextLabel *pl1 = new ECConsoleUITextLabel(30, 1, "CSE 3150");
    pl1->SetHighlight(true);
    viewTest.AddUIItem(pl1);
    ECConsoleUITextLabel *pl2 = new ECConsoleUITextLabel(25, 5, "Insructors");
    viewTest.AddUIItem(pl2);
    // Create a border (well, not very pretty)
    string horizBar;
    for(int i=0; i<viewTest.GetColNumInView(); ++i)
    {
        horizBar += '-';
    }

    
    ECConsoleUITextLabel *pl4 = new ECConsoleUITextLabel(0, 0, horizBar);
    viewTest.AddUIItem(pl4);
    ECConsoleUITextLabel *pl5 = new ECConsoleUITextLabel(0, viewTest.GetRowNumInView()-1, horizBar);
    viewTest.AddUIItem(pl5);

    // YOU NEED TO IMPLEMENT THE FOLLOWING TO MAKE IT WORK
// #if 0       
    // Add a list box
    ECConsoleUIListBox *pl = new ECConsoleUIListBox(25, 7, 45, 9 );
    pl->AddChoice("Professor Astro");
    pl->AddChoice("Professor Bearass");
    pl->AddChoice("Professor Carmark");
    pl->AddChoice("Professor Darpaet");
    pl->AddChoice("Professor Ergodist");
    pl->AddChoice("Professor Fantom");
    pl->Choose(0);
    viewTest.AddUIItem(pl);
    
    // Add another list box
    ECConsoleUITextLabel *pl6 = new ECConsoleUITextLabel(15, 12, "Lectures");
    viewTest.AddUIItem(pl6);
    ECConsoleUIListBox *px2 = new ECConsoleUIListBox(15, 15, 30, 17 );
    px2->AddChoice("Monday 8 am");
    px2->AddChoice("Tuesday 6 pm");
    px2->AddChoice("Wednesday 9 am");
    px2->AddChoice("Thursday 2 pm");
    px2->AddChoice("Friday 8 am");
    px2->Choose(0);
    viewTest.AddUIItem(px2);
    
    // Add a third list box
    ECConsoleUITextLabel *pl7 = new ECConsoleUITextLabel(40, 12, "Labs");
    viewTest.AddUIItem(pl7);
    ECConsoleUIListBox *px3 = new ECConsoleUIListBox(40, 15, 55, 17 );
    px3->AddChoice("Tu/Th 2 pm");
    px3->AddChoice("Tu/Th 4 pm");
    px3->AddChoice("M/W 9 am");
    px3->AddChoice("M/W 11 am");
    px3->Choose(0);
    viewTest.AddUIItem(px3);
    
    // Add a text field to input name
    ECConsoleUITextLabel *pl8 = new ECConsoleUITextLabel(15, 20, "Enter your name to register:");
    viewTest.AddUIItem(pl8);
    ECConsoleUITextField *pt1 = new ECConsoleUITextField(viewTest.GetView(), 15, 22, 20);
    viewTest.AddUIItem(pt1);


    // Add Register button
    ECConsoleUITextLabel *pl9 = new ECConsoleUITextLabel(70, 19, "-------------");
    viewTest.AddUIItem(pl9);
    ECConsoleUIButton *pb1 = new ECConsoleUIButton(70, 20, 82, 20, "Register!");
    viewTest.AddUIItem(pb1);
    ECConsoleUITextLabel *pl10 = new ECConsoleUITextLabel(70, 21, "-------------");
    viewTest.AddUIItem(pl10);
// #endif
}


int main(int argc, char *argv[])
{
    //
    ECTextViewImp wndTest;

    // add a status bar
    wndTest.AddStatusRow("UI test", "For demo only", true);
    
    // Create a console UI view
    ECConsoleUIView viewUI(&wndTest);
    
    // Add a few UI items
    Test1(viewUI);
    
    // Display it
    viewUI.Refresh();
    
    // Show the window
    try {
        wndTest.Show();
    }
    catch(std::string ex)
    {
        cout << "Exception: " << ex << endl;
    }
    return 0;
}
