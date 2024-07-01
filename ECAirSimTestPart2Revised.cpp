// Test code for airline simulation

#include "ECAirport.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECFlightItinerary.h"
#include "ECPassenger.h"
#include "ECAirlineSimulator.h"

#include <string>
#include <iostream>
#include <cmath>
using namespace std;

// Test utility
template<class T>
void ASSERT_EQ(T x, T y)
{
  if( x == y )
  {
    cout << "Test passed: equal: " << x << "  " << y << endl;
  }
  else
  {
    cout << "Test FAILED: equal: " << x << "  " << y << endl;
  }
}


// list of airports to use
static string ORD = "ORD";
static string BDL = "BDL";
static string SFO = "SFO";
static string EWR = "EWR";
static string IAD = "IAD";
static string BOS = "BOS";
static string IAH = "IAH";

// list of airplanes for capacity
static int CRJ_CAP = 3;
static int B737_CAP = 5;
static int B757_CAP = 8;
static int B777_CAP = 10;


static void Test1()
{
    ECAirlineSimulator sim;
    
    // Adding four airport
    sim.AddAirport("Chicago", ORD);
    sim.AddAirport("Houston", IAH);
    sim.AddAirport("San Francisco", SFO);
    sim.AddAirport("New York (Newwark, NJ)", EWR);
    
    // Set distances
    sim.SetDistBtwAirports(ORD, SFO, 2000);
    sim.SetDistBtwAirports(ORD, EWR, 1200);
    sim.SetDistBtwAirports(IAH, SFO, 1800);
    sim.SetDistBtwAirports(IAH, EWR, 1500);
    
    // Add flights
    sim.AddFlight(EWR, ORD, 7.0, 5, 2000);
    sim.AddFlight(EWR, ORD, 14.0, 5, 2000);
    sim.AddFlight(ORD, SFO, 11.0, 10, 3000);
    sim.AddFlight(ORD, SFO, 16.0, 10, 3000);
    sim.AddFlight(EWR, IAH, 8.5, 5, 2200);
    sim.AddFlight(EWR, IAH, 13.0, 5, 2200);
    sim.AddFlight(IAH, SFO, 12.0, 10, 2800);
    sim.AddFlight(IAH, SFO, 18.0, 10, 2800);
    sim.DoneFlightAdding();
    
    // Add passengers
    sim.AddPassengerBudget( IAH, SFO, 700);
    sim.AddPassengerBudget( IAH, ORD, 900);
    sim.AddPassengerBusiness( IAH, SFO, 12.0); // not bookeed
    sim.AddPassengerBusiness( EWR, ORD, 20.0);
    sim.AddPassengerBusiness( EWR, IAH, 10.0); // not bookeed
    sim.AddPassengerBusiness( IAH, SFO, 16.0); // ****
    sim.AddPassengerBusiness( IAH, SFO, 15.0); // not bookeed
    sim.AddPassengerComfort( IAH, SFO, 9.0, 15.0, 2);
    sim.AddPassengerComfort( EWR, SFO, 9.0, 15.0, 1);
    sim.AddPassengerComfort( EWR, SFO, 11.0, 15.0, 2);
    
    // Now book
    sim.Book();
    
    // dump out flight status
    cout << "***************** STATUS after initial booking..\n";
    sim.GetAirlineOp()->Dump();
    sim.GetAirlineFin()->Dump();

    std::vector<ECFlightItinerary> passengerItineraries;
    sim.GetPassengerItineraries(passengerItineraries);

    for (auto i : passengerItineraries) {
        cout << i.GetPrice() << ", ";
    }
    cout << endl;
    for (auto i : passengerItineraries) {
        cout << i.GetNumSegments() << ", ";
    }
    cout << endl;
    for (auto i : passengerItineraries) {
        cout << i.GetFlightTime() << ", ";
    }
    cout << endl;

    std::vector<double> expectedPrices = {432, 0, 0, 288, 0, 432, 0, 432, 0, 792};
    std::vector<int> expectedNumSegments = {1, 0, 0, 1, 0, 1, 0, 1, 0, 2};
    std::vector<double> expectedFlightTime = {3.6, 0, 0, 2.4, 0, 3.6, 0, 3.6, 0, 6.6};
    for (int i = 0; i < passengerItineraries.size(); i++) {
        ASSERT_EQ(std::to_string(passengerItineraries[i].GetPrice()), std::to_string(expectedPrices[i]));
        ASSERT_EQ(std::to_string(passengerItineraries[i].GetNumSegments()), std::to_string(expectedNumSegments[i]));
        ASSERT_EQ(std::to_string(passengerItineraries[i].GetFlightTime()), std::to_string(expectedFlightTime[i]));
    }
}

// A larger test case: seven airports, xxx flights
static void Test2()
{
    std::cout << "**************Test 2***************" << std::endl;
    ECAirlineSimulator sim;
    
    // Adding four airport
    sim.AddAirport("Chicago", ORD);
    sim.AddAirport("Houston", IAH);
    sim.AddAirport("San Francisco", SFO);
    sim.AddAirport("New York (Newwark, NJ)", EWR);
    sim.AddAirport("Hartford, CT", BDL);
    sim.AddAirport("Boston", BOS);
    sim.AddAirport("Washington, D.C.", IAD);
    
    // Set distances
    sim.SetDistBtwAirports(ORD, BDL, 700);
    sim.SetDistBtwAirports(ORD, SFO, 2000);
    sim.SetDistBtwAirports(ORD, EWR, 1200);
    sim.SetDistBtwAirports(ORD, IAD, 800);
    sim.SetDistBtwAirports(ORD, BOS, 800);
    sim.SetDistBtwAirports(ORD, IAH, 2000);
    sim.SetDistBtwAirports(BDL, IAD, 100);
    sim.SetDistBtwAirports(BDL, IAH, 1500);
    sim.SetDistBtwAirports(SFO, EWR, 3000);
    sim.SetDistBtwAirports(SFO, IAD, 2800);
    sim.SetDistBtwAirports(SFO, BOS, 3300);
    sim.SetDistBtwAirports(SFO, IAH, 1800);
    sim.SetDistBtwAirports(EWR, IAD, 100);
    sim.SetDistBtwAirports(EWR, BOS, 200);
    sim.SetDistBtwAirports(EWR, IAH, 1500);
    sim.SetDistBtwAirports(IAD, BOS, 200);
    sim.SetDistBtwAirports(IAD, IAH, 1300);
    sim.SetDistBtwAirports(BOS, IAH, 1600);
    
    
    // Add flights
    // Flight to/from Chicago
    sim.AddFlight(ORD, BDL, 8.0, B737_CAP, 1000);
    sim.AddFlight(ORD, BDL, 13.0, B737_CAP, 1000);
    sim.AddFlight(ORD, BDL, 20.0, B737_CAP, 1000);
    sim.AddFlight(BDL, ORD, 6.0, B737_CAP, 1000);  // I hate flight this early!
    sim.AddFlight(BDL, ORD, 14.0, B737_CAP, 1000);
    sim.AddFlight(ORD, EWR, 7.0, B737_CAP, 700);
    sim.AddFlight(ORD, EWR, 15.0, B737_CAP, 700);
    sim.AddFlight(ORD, EWR, 20.0, B737_CAP, 700);
    sim.AddFlight(EWR, ORD, 8.0, B737_CAP, 700);
    sim.AddFlight(EWR, ORD, 13.0, B737_CAP, 700);
    sim.AddFlight(EWR, ORD, 19.0, B737_CAP, 700);
    sim.AddFlight(ORD, IAD, 9.0, B737_CAP, 1100);
    sim.AddFlight(ORD, IAD, 17.0, B737_CAP, 1100);
    sim.AddFlight(IAD, ORD, 9.5, B737_CAP, 1100);
    sim.AddFlight(IAD, ORD, 16.5, B737_CAP, 1100);
    sim.AddFlight(ORD, IAH, 9.0, B737_CAP, 1900);
    sim.AddFlight(ORD, IAH, 16.0, B737_CAP, 1900);
    sim.AddFlight(IAH, ORD, 10.0, B737_CAP, 1900);
    sim.AddFlight(IAH, ORD, 18.0, B737_CAP, 1900);
    
    // Flight to/from BDL: not many flights; sigh...
    sim.AddFlight(BDL, IAD, 7.5, CRJ_CAP, 800);
    sim.AddFlight(BDL, IAD, 15.0, CRJ_CAP, 800);
    sim.AddFlight(IAD, BDL, 9.0, CRJ_CAP, 800);
    sim.AddFlight(IAD, BDL, 17.0, CRJ_CAP, 800);
    sim.AddFlight(BDL, IAH, 10.0, CRJ_CAP, 1800);
    sim.AddFlight(IAH, BDL, 15.0, CRJ_CAP, 1800);
    
    // Flight to/from SFO
    sim.AddFlight(SFO, EWR, 8.0, B777_CAP, 2800);
    sim.AddFlight(SFO, EWR, 15.0, B777_CAP, 2800);
    sim.AddFlight(EWR, SFO, 8.5, B777_CAP, 2800);
    sim.AddFlight(EWR, SFO, 14.0, B777_CAP, 2800);
    sim.AddFlight(SFO, IAD, 7.0, B777_CAP, 3000);
    sim.AddFlight(SFO, IAD, 17.5, B777_CAP, 3000);
    sim.AddFlight(IAD, SFO, 9.5, B777_CAP, 3000);
    sim.AddFlight(IAD, SFO, 16.5, B777_CAP, 3000);
    sim.AddFlight(SFO, IAH, 6.5, B757_CAP, 2500);
    sim.AddFlight(SFO, IAH, 13., B757_CAP, 2500);
    sim.AddFlight(IAH, SFO, 9.0, B757_CAP,  2500);
    sim.AddFlight(IAH, SFO, 16.0, B757_CAP, 2500);
    
    // flight to/from EWR
    sim.AddFlight(EWR, IAD, 8.0, B737_CAP, 600);
    sim.AddFlight(EWR, IAD, 12.0, B737_CAP, 600);
    sim.AddFlight(EWR, IAD, 18.0, B737_CAP, 600);
    sim.AddFlight(IAD, EWR, 8.5, B737_CAP, 600);
    sim.AddFlight(IAD, EWR, 12.5, B737_CAP, 600);
    sim.AddFlight(IAD, EWR, 18.5, B737_CAP, 600);
    sim.AddFlight(EWR, IAH, 10.0, B737_CAP, 1700);
    sim.AddFlight(EWR, IAH, 15.0, B737_CAP, 1700);
    sim.AddFlight(IAH, EWR, 9.0, B737_CAP, 1700);
    sim.AddFlight(IAH, EWR, 15.5, B737_CAP, 1700);
    
    // flight to/from IAD
    sim.AddFlight(IAD, BOS, 11.0, CRJ_CAP, 1000);
    sim.AddFlight(BOS, IAD, 12.0, CRJ_CAP, 1000);
    
    // done with flights
    sim.DoneFlightAdding();
    
    // Add passengers
    sim.AddPassengerBudget( ORD, SFO, 1400);
    sim.AddPassengerBudget( EWR, BOS, 300);
    sim.AddPassengerBusiness( ORD, SFO, 18.0);
    sim.AddPassengerBusiness( EWR, SFO, 16.0);
    sim.AddPassengerBusiness( IAH, EWR, 15.0);
    sim.AddPassengerComfort( ORD, SFO, 9.0, 15.0, 2);
    sim.AddPassengerComfort( BDL, BOS, 11.0, 15.0, 1);
    sim.AddPassengerComfort( BDL, SFO, 11.0, 15.0, 2);
    
    sim.Book();

    std::vector<ECFlightItinerary> passengerItineraries;
    sim.GetPassengerItineraries(passengerItineraries);

    for (auto i : passengerItineraries) {
        cout << i.GetPrice() << ", ";
    }
    cout << endl;
    for (auto i : passengerItineraries) {
        cout << i.GetNumSegments() << ", ";
    }
    cout << endl;
    for (auto i : passengerItineraries) {
        cout << i.GetFlightTime() << ", ";
    }
    cout << endl;

    std::vector<double> expectedPrices = {864, 72, 0, 720, 360, 864, 0, 696};
    std::vector<int> expectedNumSegments = {2, 2, 0, 1, 1, 2, 0, 2};
    std::vector<double> expectedFlightTime = {7.2, 0.6, 0, 6, 3, 7.2, 0, 5.8};
    for (int i = 0; i < passengerItineraries.size(); i++) {
        ASSERT_EQ(std::to_string(passengerItineraries[i].GetPrice()), std::to_string(expectedPrices[i]));
        ASSERT_EQ(std::to_string(passengerItineraries[i].GetNumSegments()), std::to_string(expectedNumSegments[i]));
        ASSERT_EQ(std::to_string(passengerItineraries[i].GetFlightTime()), std::to_string(expectedFlightTime[i]));
    }
}


int main()
{
    Test1();
    Test2();
}
