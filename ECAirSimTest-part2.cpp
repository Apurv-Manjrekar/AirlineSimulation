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


// setup airports
static void TestSetupAirports()
{
    // first create airports
    ECAirportInfo :: Instance()->CreateAirport(ORD, ORD);
    ECAirportInfo :: Instance()->CreateAirport(BDL, BDL);
    ECAirportInfo :: Instance()->CreateAirport(SFO, SFO);
    ECAirportInfo :: Instance()->CreateAirport(EWR, EWR);
    ECAirportInfo :: Instance()->CreateAirport(IAD, IAD);
    ECAirportInfo :: Instance()->CreateAirport(BOS, BOS);
    ECAirportInfo :: Instance()->CreateAirport(IAH, IAH);
    
    // now setup distance
    ECAirportInfo :: Instance()->SetDistanceBtw(ORD, BDL, 700);
    ECAirportInfo :: Instance()->SetDistanceBtw(ORD, SFO, 2500);
    ECAirportInfo :: Instance()->SetDistanceBtw(ORD, EWR, 750);
    ECAirportInfo :: Instance()->SetDistanceBtw(ORD, IAD, 800);
    ECAirportInfo :: Instance()->SetDistanceBtw(ORD, BOS, 800);
    ECAirportInfo :: Instance()->SetDistanceBtw(ORD, IAH, 2000);
    ECAirportInfo :: Instance()->SetDistanceBtw(BDL, IAD, 100);
    ECAirportInfo :: Instance()->SetDistanceBtw(BDL, IAH, 1500);
    ECAirportInfo :: Instance()->SetDistanceBtw(SFO, EWR, 3000);
    ECAirportInfo :: Instance()->SetDistanceBtw(SFO, IAD, 2800);
    ECAirportInfo :: Instance()->SetDistanceBtw(SFO, BOS, 3300);
    ECAirportInfo :: Instance()->SetDistanceBtw(SFO, IAH, 2000);
    ECAirportInfo :: Instance()->SetDistanceBtw(EWR, IAD, 100);
    ECAirportInfo :: Instance()->SetDistanceBtw(EWR, BOS, 200);
    ECAirportInfo :: Instance()->SetDistanceBtw(EWR, IAH, 1300);
    ECAirportInfo :: Instance()->SetDistanceBtw(IAD, BOS, 200);
    ECAirportInfo :: Instance()->SetDistanceBtw(IAD, IAH, 1300);
    ECAirportInfo :: Instance()->SetDistanceBtw(BOS, IAH, 1600);
    
    // now check a bit
    cout << "Distance: " << SFO << "," << IAD << ": " << ECAirportInfo::Instance()->GetDistanceBtw(SFO, IAD) << ", flight time: " << ECAirportInfo::Instance()->GetFlightTimeBtw(SFO, IAD) << endl;
}

// create airline: FancyAir
static ECAirlineOperation fancyAirOps;
static ECAirlineFinancial fancyAirFin(&fancyAirOps);
static ECAirlineTicketing fancyAirTicketing(&fancyAirOps, &fancyAirFin);

// Init tests
static void TestInit()
{
    fancyAirOps.SetAirlineFin( &fancyAirFin );
}

// setup this airline
static void TestSetupAirlineOperation()
{
    // Flight to/from Chicago
    fancyAirOps.AddFlight(ORD, BDL, 8.0);
    fancyAirOps.AddFlight(ORD, BDL, 13.0);
    fancyAirOps.AddFlight(ORD, BDL, 20.0);
    fancyAirOps.AddFlight(BDL, ORD, 6.0);  // I hate flight this early!
    fancyAirOps.AddFlight(BDL, ORD, 14.0);
    fancyAirOps.AddFlight(ORD, EWR, 7.0);
    fancyAirOps.AddFlight(ORD, EWR, 15.0);
    fancyAirOps.AddFlight(ORD, EWR, 20.0);
    fancyAirOps.AddFlight(EWR, ORD, 8.0);
    fancyAirOps.AddFlight(EWR, ORD, 13.0);
    fancyAirOps.AddFlight(EWR, ORD, 19.0);
    fancyAirOps.AddFlight(ORD, IAD, 9.0);
    fancyAirOps.AddFlight(ORD, IAD, 17.0);
    fancyAirOps.AddFlight(IAD, ORD, 9.5);
    fancyAirOps.AddFlight(IAD, ORD, 16.5);
    fancyAirOps.AddFlight(ORD, IAH, 9.0);
    fancyAirOps.AddFlight(ORD, IAH, 16.0);
    fancyAirOps.AddFlight(IAH, ORD, 10.0);
    fancyAirOps.AddFlight(IAH, ORD, 18.0);
    
    // Flight to/from BDL: not many flights; sigh...
    fancyAirOps.AddFlight(BDL, IAD, 7.5);
    fancyAirOps.AddFlight(BDL, IAD, 15.0);
    fancyAirOps.AddFlight(IAD, BDL, 9.0);
    fancyAirOps.AddFlight(IAD, BDL, 17.0);
    fancyAirOps.AddFlight(BDL, IAH, 10.0);
    fancyAirOps.AddFlight(IAH, BDL, 15.0);
    
    // Flight to/from SFO
    fancyAirOps.AddFlight(SFO, EWR, 8.0);
    fancyAirOps.AddFlight(SFO, EWR, 15.0);
    fancyAirOps.AddFlight(EWR, SFO, 8.5);
    fancyAirOps.AddFlight(EWR, SFO, 14.0);
    fancyAirOps.AddFlight(SFO, IAD, 7.0);
    fancyAirOps.AddFlight(SFO, IAD, 17.5);
    fancyAirOps.AddFlight(IAD, SFO, 9.5);
    fancyAirOps.AddFlight(IAD, SFO, 16.5);
    fancyAirOps.AddFlight(SFO, IAH, 6.5);
    fancyAirOps.AddFlight(SFO, IAH, 13.0);
    fancyAirOps.AddFlight(IAH, SFO, 9.0);
    fancyAirOps.AddFlight(IAH, SFO, 16.0);
    
    // flight to/from EWR
    fancyAirOps.AddFlight(EWR, IAD, 8.0);
    fancyAirOps.AddFlight(EWR, IAD, 12.0);
    fancyAirOps.AddFlight(EWR, IAD, 18.0);
    fancyAirOps.AddFlight(IAD, EWR, 8.5);
    fancyAirOps.AddFlight(IAD, EWR, 12.5);
    fancyAirOps.AddFlight(IAD, EWR, 18.5);
    fancyAirOps.AddFlight(EWR, IAH, 10.0);
    fancyAirOps.AddFlight(EWR, IAH, 15.0);
    fancyAirOps.AddFlight(IAH, EWR, 9.0);
    fancyAirOps.AddFlight(IAH, EWR, 15.5);
    
    // flight to/from IAD
    fancyAirOps.AddFlight(IAD, BOS, 11.0);
    fancyAirOps.AddFlight(BOS, IAD, 12.0);
    
    // setup observers
    fancyAirOps.PostFlightSetup();
    
    // test a little
    cout << "FancyAir has " << fancyAirOps.GetNumFlights() << " operating flights\n"; // should be 49
}

// Test search for itinerary
static void TestSearchItinerary()
{    
    // Search for itineraries
    vector<ECFlightItinerary> listItineraries;
    fancyAirTicketing.SearchForItinerary(BDL, SFO, 6.0, listItineraries);
    
    // You can choose different preference; combinations allowed!
    // I encourage you to play with the changes of priority
    // aboev all, prefer low price!
    //fancyAirTicketing.PreferLowPrice();
    
    // then prefer early arrival; if tied, prfer the cheaper ones
    fancyAirTicketing.PreferEarlyArrival();
    fancyAirTicketing.PreferLowPrice();
    
    // prefer smallest num of segments as first preferencce and then flight time
    //fancyAirTicketing.PreferSmallestSegments();
    //fancyAirTicketing.PreferShortTime();
    
    // Order itineraries
    fancyAirTicketing.OrderItineraries(listItineraries);
    
    cout << "Number of found itineraries: " << listItineraries.size() << endl;
    // dump the first 10
    for(unsigned int i=0; i<10 && i<listItineraries.size(); ++i)
    {
        listItineraries[i].Dump();
    }
}
// test passenger
static void TestPassengers()
{
    cout << "TESTING passengers..\n";
    // budget: try to vary budget; 800 is too low, 
    const double budget1 = 1000;
    ECPassenger *p1 = new ECPassengerBudget(BDL, SFO, budget1 );
    fancyAirFin.RegisterPassenger(p1);
    bool f1 = p1->Book(fancyAirTicketing);
    if( f1 )
    {
        cout << "Passenger 1: booked! ";
        p1->GetItinerary().Dump();
    }
    else
    {
        cout << "Passenger 1: NOT booked! " << endl;
    }
    // business: 12 pm arrival is not possible
    ECPassenger *p2 = new ECPassengerBusiness(SFO, BDL, 12.0);
    bool f2 = p2->Book(fancyAirTicketing);
    fancyAirFin.RegisterPassenger(p2);
    if( f2 )
    {
        cout << "Passenger 2: booked! ";
        p2->GetItinerary().Dump();
    }
    else
    {
        cout << "Passenger 2: NOT booked! " << endl;
    }
    // comfort: yes this is possible
    ECPassenger *p3 = new ECPassengerComfort(BOS, SFO, 8.0, 12.0, 2);
    fancyAirFin.RegisterPassenger(p3);
    bool f3 = p3->Book(fancyAirTicketing);
    if( f3 )
    {
        cout << "Passenger 3: booked! ";
        p3->GetItinerary().Dump();
    }
    else
    {
        cout << "Passenger 3: NOT booked! " << endl;
    }
    
    // what is the revenue of the airline
    cout << "Revenue of Fancy air: " << fancyAirFin.GetRevenue() << endl;

    //cout << "--- Operating cost: " << fancyAirOps.GetOperatingCost() << endl;

    // the following are not required. Just for you to see airline operatio can be much more complex
#if 0
    // test flight canellation
    // cancel BDL to IAD 7.5 time
    const int FLIGHT_BDL_IAD = 19;
    cout << "Canceling flight from BDL to IAD...\n";
    ECFlight *pFlight = fancyAirOps.GetFlight(FLIGHT_BDL_IAD);
    if( pFlight == NULL )
    {
        throw std::string("Flight: not found");
    }
    cout << "Flight to cancel: ";
    pFlight->Dump();
    // now cancel
    pFlight->Cancel();
    
    // Cancel IAD to SFO at 9.5
    const int FLIGHT_IAD_SFO = 31;
    cout << "Canceling flight from IAD to SFO...\n";
    ECFlight *pFlight2 = fancyAirOps.GetFlight(FLIGHT_IAD_SFO);
    if( pFlight2 == NULL )
    {
        throw std::string("Flight: not found");
    }
    cout << "Flight to cancel: ";
    pFlight2->Dump();
    // now cancel
    pFlight2->Cancel();
    
    cout << "--- Operating cost (after cancel two flights): " << fancyAirOps.GetOperatingCost() << endl;
    
    // Test flight delay
    // Delay SFO to IAD from 7 to 11
    const int FLIGHT_SFO_IAD = 29;
    const double TM_DEP_NEW_3 = 11.0;
    cout << "Delaying flight from SFO to IAD...\n";
    ECFlight *pFlight3 = fancyAirOps.GetFlight(FLIGHT_SFO_IAD);
    if( pFlight3 == NULL )
    {
        throw std::string("Flight: not found");
    }
    cout << "Flight to delay: ";
    pFlight3->Dump();
    // now cancel
    pFlight3->ChangeDepartTime(TM_DEP_NEW_3);
    
    // Test airport shutdown of BDL
    //ECAirportInfo::Instance().GetAirport(BDL).SetOperating(false);
#endif
    cout << "^^^^ Passenger status: \n";
    p1->Dump();
    p2->Dump();
    p3->Dump();
}
#if 0
static void TestPlanning()
{
    const int FLIGHT_SFO_IAD = 29;
    ECFlight *pFlight3 = fancyAirOps.GetFlight(FLIGHT_SFO_IAD);
    double fRev = fancyAirFin.EstimateRevenueByFlight(pFlight3);
    cout << "Revenue generated by flight SFO to IAD: " << fRev << endl;
    
    // now optimize:
    const double RATIO_REV_TO_COST = 0.6;
    fancyAirOps.OptimizeFlights(RATIO_REV_TO_COST);
}
#endif

int main()
{
    // do some init
    TestInit();
    
    // setup airports first
    TestSetupAirports();
    
    // setup airline
    TestSetupAirlineOperation();
    
    //search for itinaries
    TestSearchItinerary();
    
    // Test passenger
    TestPassengers();
    
    // Test planning
    //TestPlanning();
    
    // dump out flight status
    //fancyAirOps.Dump();
    
    //cout << "Airline balance: " << fancyAirFin.GetBalance() << endl;
}

