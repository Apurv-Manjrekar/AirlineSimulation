#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ECAirlineSimulator.h"
#include "ECTextViewImp.h"
#include "ECConsoleUIView.h"
#include "ECConsoleUITextLabel.h"
#include "ECConsoleUITextField.h"
#include "ECConsoleUIListBox.h"
#include "ECConsoleUIButton.h"


using namespace std;

static void AddUIItems(ECConsoleUIView& viewUI, ECAirlineSimulator& airlineSimulator)
{
    // create several labels
    ECConsoleUITextLabel *pl1 = new ECConsoleUITextLabel(30, 1, "Manjrekar Airline Flight Reservation System");
    pl1->SetHighlight(true);
    viewUI.AddUIItem(pl1);
    
    // Create a border (well, not very pretty)
    string horizBar;
    for(int i=0; i<viewUI.GetColNumInView(); ++i)
    {
        horizBar += '-';
    }

    ECConsoleUITextLabel *pl2 = new ECConsoleUITextLabel(0, 0, horizBar);
    viewUI.AddUIItem(pl2);
    ECConsoleUITextLabel *pl3 = new ECConsoleUITextLabel(0, viewUI.GetRowNumInView()-1, horizBar);
    viewUI.AddUIItem(pl3);


    ECConsoleUITextLabel *srcLabel = new ECConsoleUITextLabel(15, 5, "Origination");
    viewUI.AddUIItem(srcLabel);
    ECConsoleUITextLabel *destLabel = new ECConsoleUITextLabel(40, 5, "Destination");
    viewUI.AddUIItem(destLabel);
    // Add a list box
    ECConsoleUIListBox *srcListBox = new ECConsoleUIListBox(15, 7, 30, 9);
    ECConsoleUIListBox *destListBox = new ECConsoleUIListBox(40, 7, 55, 9);
    set<string> airportCodes;
    airlineSimulator.GetAllAirportCode(airportCodes);
    for(auto code : airportCodes)
    {
        srcListBox->AddChoice(code);
        destListBox->AddChoice(code);
    }
    srcListBox->Choose(0);
    destListBox->Choose(0);
    viewUI.AddUIItem(srcListBox);
    viewUI.AddUIItem(destListBox);

    // Add a third list box
    ECConsoleUITextLabel *flightsLabel = new ECConsoleUITextLabel(25, 15, "Flights");
    viewUI.AddUIItem(flightsLabel);
    ECConsoleUIListBox *flightsListBox = new ECConsoleUIListBox(10, 17, 60, 19);
    viewUI.AddUIItem(flightsListBox);

    // Add Search for Flights button
    ECConsoleUITextLabel *flightsUpperHoriz = new ECConsoleUITextLabel(20, 12, "----------------------");
    viewUI.AddUIItem(flightsUpperHoriz); 
    ECConsoleUIButton *searchFlightsButton = new ECConsoleUISearchForFlightsButton(20, 13, 41, 13, "Search For Flights", srcListBox, destListBox, flightsListBox, airlineSimulator, viewUI.GetView());
    viewUI.AddUIItem(searchFlightsButton);
    ECConsoleUITextLabel *flightsLowerHoriz = new ECConsoleUITextLabel(20, 14, "----------------------");
    viewUI.AddUIItem(flightsLowerHoriz);
    
    // Add a text field to input name
    ECConsoleUITextLabel *passengerLabel = new ECConsoleUITextLabel(15, 22, "Enter Passenger Name:");
    viewUI.AddUIItem(passengerLabel);
    ECConsoleUITextField *passengerTextField = new ECConsoleUITextField(viewUI.GetView(), 15, 24, 20);
    viewUI.AddUIItem(passengerTextField);

    // // Add Register button
    // ECConsoleUITextLabel *registerUpperHoriz = new ECConsoleUITextLabel(70, 21, "-------------");
    // viewUI.AddUIItem(registerUpperHoriz);
    // ECConsoleUIButton *registerButton = new ECConsoleUIButton(70, 22, 82, 22, "Register!");
    // viewUI.AddUIItem(registerButton);
    // ECConsoleUITextLabel *registerLowerHoriz = new ECConsoleUITextLabel(70, 23, "-------------");
    // viewUI.AddUIItem(registerLowerHoriz);
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }

    ifstream inputDataFile(argv[1]);

    if(!inputDataFile.is_open())
    {
        cout << "Could not open file: " << argv[1] << endl;
        return 1;
    }

    ECAirlineSimulator airlineSimulator;

    string currLine;
    while(getline(inputDataFile, currLine))
    {
        if(currLine.empty() || currLine[0] == '#')
        {
            continue;
        }
        // ******* ADD AIRPORTS *******
        if(currLine[0] == '1')
        {
            auto firstSpace = currLine.find(' ');
            auto secondSpace = currLine.find(' ', firstSpace + 1);
            string airportCode = currLine.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string airportName = currLine.substr(secondSpace + 1);
            airlineSimulator.AddAirport(airportName, airportCode);
        }
        // ******* SET DISTANCES *******
        else if(currLine[0] == '2')
        {
            auto firstSpace = currLine.find(' ');
            auto secondSpace = currLine.find(' ', firstSpace + 1);
            auto thirdSpace = currLine.find(' ', secondSpace + 1);
            string airportSrc = currLine.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string airportDest = currLine.substr(secondSpace + 1, thirdSpace - secondSpace - 1);
            int distance = stoi(currLine.substr(thirdSpace + 1));
            airlineSimulator.SetDistBtwAirports(airportSrc, airportDest, distance);
        }
        // ******* ADD FLIGHTS *******
        else if(currLine[0] == '3')
        {
            auto firstSpace = currLine.find(' ');
            auto secondSpace = currLine.find(' ', firstSpace + 1);
            auto thirdSpace = currLine.find(' ', secondSpace + 1);
            auto fourthSpace = currLine.find(' ', thirdSpace + 1);
            auto fifthSpace = currLine.find(' ', fourthSpace + 1);
            string airportSrc = currLine.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string airportDest = currLine.substr(secondSpace + 1, thirdSpace - secondSpace - 1);
            double timeDepart = stod(currLine.substr(thirdSpace + 1, fourthSpace - thirdSpace - 1));
            int maxPassengers = stoi(currLine.substr(fourthSpace + 1, fifthSpace - fourthSpace - 1));
            double costOperate = stod(currLine.substr(fifthSpace + 1));
            airlineSimulator.AddFlight(airportSrc, airportDest, timeDepart, maxPassengers, costOperate);
        }
    }
    inputDataFile.close();

    // ******* INITIALIZE UI *******
    ECTextViewImp wndTest;
    wndTest.AddStatusRow("UI test", "For demo only", true);
    
    // Create a console UI view
    ECConsoleUIView viewUI(&wndTest);
    
    // Add a few UI items
    AddUIItems(viewUI, airlineSimulator);
    
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