//
//  ECAirlineSimulator.cpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//

#include "ECAirlineSimulator.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECAirport.h"
#include "ECFlight.h"
#include "ECPassenger.h"

#include <iostream>
using namespace std;

ECAirlineSimulator::ECAirlineSimulator()
{
    this->Init();
}
ECAirlineSimulator::~ECAirlineSimulator()
{
    delete this->airlineOperation;
    delete this->airlineFinancial;
    delete this->airlineTicketing;
}

// *****************************************************
// Configuration

// Adding airport with name and IATA code
void ECAirlineSimulator::AddAirport(const std::string &name, const std::string &code)
{
    ECAirportInfo::Instance()->CreateAirport(name, code);
}

// Setup distaince between airport; note distance is symmetric: the distance from dest to src is the same as from src to dest
void ECAirlineSimulator::SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist)
{
    ECAirportInfo::Instance()->SetDistanceBtw(srcAirport, destAirport, dist);
}

// Adding flights: src airport, dest airport, depart time, max number of passenger, operating cost
void ECAirlineSimulator::AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate)
{
    this->airlineOperation->AddFlight(srcAirport, destAirport, tmDepart, maxPassengers, costOperate);
}

// Called to indicate no more flights to add
void ECAirlineSimulator::DoneFlightAdding()
{
    this->airlineOperation->PostFlightSetup();
}

// get all airport codes in record
void ECAirlineSimulator::GetAllAirportCode(std::set<std::string> &getAirports) const
{
    ECAirportInfo::Instance()->GetAllAirportCode(getAirports);
}

// *****************************************************
// Flight search

// Search for flights; return all flights in listItineraries that go from src to dest
void ECAirlineSimulator::SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries) const
{
    return this->airlineTicketing->SearchForItinerary(src, dest, listItineraries);
}

// Prefer functions
void ECAirlineSimulator::ClearPreference()
{
    this->airlineTicketing->ClearPreference();
}
void ECAirlineSimulator::PreferLowPrice() 
{
    this->airlineTicketing->PreferLowPrice();
}
void ECAirlineSimulator::PreferEarlyArrival() 
{
    this->airlineTicketing->PreferEarlyArrival();
}
void ECAirlineSimulator::PreferShortTime() 
{
    this->airlineTicketing->PreferShortTime();
}
void ECAirlineSimulator::PreferSmallestSegments()
{
    this->airlineTicketing->PreferSmallestSegments();
}

void ECAirlineSimulator::OrderItineraries(std::vector<ECFlightItinerary>& listItineraries)
{
    this->airlineTicketing->OrderItineraries(listItineraries);
}

// *****************************************************
// Flight booking and optimization
// Book flights for all unbooked passengers
// In the order of passenger adding. That is, the first added passenger is to be booked the first
void ECAirlineSimulator::Book()
{
    for(int i=0; i<this->airlineFinancial->GetNumPassengers(); ++i)
    {
        this->airlineFinancial->GetPassenger(i)->Book((*this->airlineTicketing));
    }
}

ECPassenger* ECAirlineSimulator::GetPassenger(int index)
{
    return this->airlineFinancial->GetPassenger(index);
}

void ECAirlineSimulator::AddPassengerBudget(const std::string &srcAirport, const std::string &destAirport, double budget)
{
    ECPassenger* p = new ECPassengerBudget(srcAirport, destAirport, budget);
    this->airlineFinancial->RegisterPassenger(p);
}

void ECAirlineSimulator::AddPassengerBusiness(const std::string &srcAirport, const std::string &destAirport, double tmArrivalLatest)
{
    ECPassenger* p = new ECPassengerBusiness(srcAirport, destAirport, tmArrivalLatest);
    this->airlineFinancial->RegisterPassenger(p);
}

void ECAirlineSimulator::AddPassengerComfort(const std::string &srcAirport, const std::string &destAirport, double tmEarliestDepartIn, double maxFlightTimeIn, int maxSegmentsIn)
{
    ECPassenger* p = new ECPassengerComfort(srcAirport, destAirport, tmEarliestDepartIn, maxFlightTimeIn, maxSegmentsIn);
    this->airlineFinancial->RegisterPassenger(p);
}

void ECAirlineSimulator::GetPassengerItineraries(std::vector<ECFlightItinerary>& passengerItineraries)
{
    passengerItineraries.clear();
    for(int i=0; i<this->airlineFinancial->GetNumPassengers(); ++i)
    {
        passengerItineraries.push_back(this->airlineFinancial->GetPassenger(i)->GetItinerary());    
    }
}


// Access airlines
ECAirlineFinancial* ECAirlineSimulator::GetAirlineFin() { return this->airlineFinancial; }
ECAirlineOperation* ECAirlineSimulator::GetAirlineOp() { return this->airlineOperation; }
ECAirlineTicketing* ECAirlineSimulator::GetAirlineTicketing() { return this->airlineTicketing; }

// Initialization
void ECAirlineSimulator::Init()
{
    this->airlineOperation = new ECAirlineOperation();
    this->airlineFinancial = new ECAirlineFinancial();
    this->airlineTicketing = new ECAirlineTicketing();
    this->airlineOperation->SetAirlineFinancial(this->airlineFinancial);
    this->airlineOperation->SetAirlineTicketing(this->airlineTicketing);
    this->airlineFinancial->SetAirlineOperation(this->airlineOperation);
    this->airlineFinancial->SetAirlineTicketing(this->airlineTicketing);
    this->airlineTicketing->SetAirlineOperation(this->airlineOperation);
    this->airlineTicketing->SetAirlineFinancial(this->airlineFinancial);
}
 