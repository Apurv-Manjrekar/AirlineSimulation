//
//  ECPassenger.cpp
//  

#include "ECPassenger.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECFlight.h"

#include <vector>
#include <iostream>
using namespace std;

class ECAirlineTicketing;


//****************************************************************************
// Passenger: generic

ECPassenger::ECPassenger(const std::string &srcAirportIn, const std::string &destAirportIn) : srcAirport(srcAirportIn), destAirport(destAirportIn), status(EC_PASSENGER_UNBOOKED)
{}
ECPassenger::~ECPassenger() {}

// Book with the airline; return true if booked; false otherwise
// Template method pattern
bool ECPassenger::Book(ECAirlineTicketing &airlineTicketing)
{
    airlineTicketing.SetPreferences(this->GetFlightPreference());
    vector<ECFlightItinerary> itineraries;
    airlineTicketing.SearchForItinerary(this->srcAirport, this->destAirport, itineraries);
    airlineTicketing.OrderItineraries(itineraries);
    if(itineraries.size() == 0)
    {
        return false;
    }
    else
    {
        this->status = EC_PASSENGER_BOOKED;
        this->itin = itineraries[0];
        airlineTicketing.GetAirlineFinancial()->Paid(this->GetItinerary().GetPrice());
        return true;
    }
}

// Get current itinerary
const ECFlightItinerary& ECPassenger::GetItinerary() const { return this->itin; }

// Get status
EC_PASSENGER_STATUS ECPassenger::GetStatus() const { return this->status; }

// Dump out info
void ECPassenger::Dump() const
{
    cout << "Regular Passenger: " << this->srcAirport << " -> " << this->destAirport << endl;
    if(this->GetStatus() == EC_PASSENGER_BOOKED)
    {
        this->GetItinerary().Dump();
    }
    else
    {
        cout << "NOT booked!" << endl;
    }
    cout << endl;
}

std::vector<ECFlightPreference> ECPassenger::GetFlightPreference() const
{
    return std::vector<ECFlightPreference>({});
}

std::string ECPassenger::GetSrcAirport() const
{
    return this->srcAirport;
}
std::string ECPassenger::GetDestAirport() const
{
    return this->destAirport;
}
void ECPassenger::SetStatus(EC_PASSENGER_STATUS statusIn)
{
    this->status = statusIn;
}
void ECPassenger::SetItinerary(const ECFlightItinerary &itinIn)
{
    this->itin = itinIn;
}

// Passenger: budget (with a fixed upper limit on budget)
ECPassengerBudget::ECPassengerBudget(const std::string &srcAirportIn, const std::string &destAirportIn, double budgetIn) : ECPassenger(srcAirportIn, destAirportIn), budget(budgetIn)
{}
bool ECPassengerBudget::Book(ECAirlineTicketing &airlineTicketing)
{
    airlineTicketing.SetPreferences(this->GetFlightPreference());
    vector<ECFlightItinerary> itineraries;
    airlineTicketing.SearchForItinerary(this->GetSrcAirport(), this->GetDestAirport(), itineraries);
    airlineTicketing.OrderItineraries(itineraries);
    if(itineraries.size() == 0 || itineraries[0].GetPrice() > this->budget)
    {
        return false;
    }
    else
    {
        this->SetStatus(EC_PASSENGER_BOOKED);
        this->SetItinerary(itineraries[0]);
        airlineTicketing.GetAirlineFinancial()->Paid(this->GetItinerary().GetPrice());
        return true;
    }
}
void ECPassengerBudget::Dump() const
{
    cout << "Budget Passenger: " << this->GetSrcAirport() << " -> " << this->GetDestAirport() << " Budget: " << this->budget << endl;
    if(this->GetStatus() == EC_PASSENGER_BOOKED)
    {
        this->GetItinerary().Dump();
    }
    else
    {
        cout << "NOT booked!" << endl;
    }
    cout << endl;
}
std::vector<ECFlightPreference> ECPassengerBudget::GetFlightPreference() const
{
    return std::vector<ECFlightPreference>({ECFlightPreferenceLowPrice, ECFlightPreferenceShortTime, ECFlightPreferenceSmallestSegments, ECFlightPreferenceEarlyArrival});
}



// Passenger: business (with a deadline to arrive on time; i.e., must arrive by certain time)
ECPassengerBusiness::ECPassengerBusiness(const std::string &srcAirportIn, const std::string &destAirportIn, double tmArrivalLatestIn) : ECPassenger(srcAirportIn, destAirportIn), tmArrivalLatest(tmArrivalLatestIn)
{}
bool ECPassengerBusiness::Book(ECAirlineTicketing &airlineTicketing)
{
    airlineTicketing.SetPreferences(this->GetFlightPreference());
    vector<ECFlightItinerary> itineraries;
    airlineTicketing.SearchForItinerary(this->GetSrcAirport(), this->GetDestAirport(), itineraries);
    airlineTicketing.OrderItineraries(itineraries);
    if(itineraries.size() == 0 || itineraries[0].GetArrivalTime() > this->tmArrivalLatest)
    {
        return false;
    }
    else
    {
        this->SetStatus(EC_PASSENGER_BOOKED);
        this->SetItinerary(itineraries[0]);
        airlineTicketing.GetAirlineFinancial()->Paid(this->GetItinerary().GetPrice());
        return true;
    }
}
void ECPassengerBusiness::Dump() const
{
    
    cout << "Business Passenger: " << this->GetSrcAirport() << " -> " << this->GetDestAirport() << " Latest Arrival: " << this->tmArrivalLatest << endl;
    if(this->GetStatus() == EC_PASSENGER_BOOKED)
    {
        this->GetItinerary().Dump();
    }
    else
    {
        cout << "NOT booked!" << endl;
    }
    cout << endl;
}
std::vector<ECFlightPreference> ECPassengerBusiness::GetFlightPreference() const
{
    return std::vector<ECFlightPreference>({ECFlightPreferenceEarlyArrival, ECFlightPreferenceShortTime, ECFlightPreferenceSmallestSegments, ECFlightPreferenceLowPrice});
}

// Passenger: comfort (with upper bounds on departure time, flight time and number of segments)
ECPassengerComfort::ECPassengerComfort(const std::string &srcAirportIn, const std::string &destAirportIn, double tmEarliestDepartIn, double maxFlightTimeIn, int maxSegmentsIn) : ECPassenger(srcAirportIn, destAirportIn), tmEarliestDepart(tmEarliestDepartIn), maxFlightTime(maxFlightTimeIn), maxSegments(maxSegmentsIn)
{}
bool ECPassengerComfort::Book(ECAirlineTicketing &airlineTicketing)
{
    airlineTicketing.SetPreferences(this->GetFlightPreference());
    vector<ECFlightItinerary> itineraries;
    airlineTicketing.SearchForItinerary(this->GetSrcAirport(), this->GetDestAirport(), this->tmEarliestDepart, itineraries);
    airlineTicketing.OrderItineraries(itineraries);
    for(auto itinerary : itineraries)
    {
        if(itinerary.GetFlightTime() <= this->maxFlightTime && itinerary.GetNumSegments() <= this->maxSegments)
        {
            this->SetStatus(EC_PASSENGER_BOOKED);
            this->SetItinerary(itinerary);
            airlineTicketing.GetAirlineFinancial()->Paid(this->GetItinerary().GetPrice());
            return true;
        }
    }
    return false;
}
void ECPassengerComfort::Dump() const
{
    cout << "Comfort Passenger: " << this->GetSrcAirport() << " -> " << this->GetDestAirport() << " Earliest Depart: " << this->tmEarliestDepart << endl;
    if(this->GetStatus() == EC_PASSENGER_BOOKED)
    {
        this->GetItinerary().Dump();
    }
    else
    {
        cout << "NOT booked!" << endl;
    }
    cout << endl;
}
std::vector<ECFlightPreference> ECPassengerComfort::GetFlightPreference() const
{
    return std::vector<ECFlightPreference>({ECFlightPreferenceSmallestSegments, ECFlightPreferenceShortTime, ECFlightPreferenceEarlyArrival, ECFlightPreferenceLowPrice});
}
