//
//  ECFlightItinerary.cpp
//  

#include "ECFlightItinerary.h"
#include "ECFlight.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

// ****************************************************************************
// Flight itineary: consisting segments of flights so to go from one airport to another airport


// default constructor
ECFlightItinerary::ECFlightItinerary() {}

// constructor that takes a list of flight segments
ECFlightItinerary::ECFlightItinerary(std::vector<ECFlight*>& flightSegments) : flightSegments(flightSegments) {}

// access/edit segments
// Return the number of segments of the itineary
int ECFlightItinerary::GetNumSegments() const
{
    return this->flightSegments.size();
}

// Return a segment
ECFlight* ECFlightItinerary::GetSegment(int segIndex) const
{
    return this->flightSegments[segIndex];
}

// Get flight time: from departure to arrival
double ECFlightItinerary::GetFlightTime() const
{
    double flightTime = 0.0;
    for(auto& flight : this->flightSegments)
    {
        flightTime += flight->GetFlightTime();
    }
    return flightTime;
}

// Get segment time: add the time of all segments
double ECFlightItinerary::GetTimeAllSegments() const
{
    return this->GetSegment(this->GetNumSegments() - 1)->GetArrivalTime() - this->GetSegment(0)->GetDepartureTime();
}

// Get departure time
double ECFlightItinerary::GetDepartTime() const
{
    return this->GetSegment(0)->GetDepartureTime();
}

// Get arrival time
double ECFlightItinerary::GetArrivalTime() const
{
    return this->GetSegment(this->GetNumSegments() - 1)->GetArrivalTime();
}

// Price 
double ECFlightItinerary::GetPrice() const
{
    return (this->GetFlightTime() * 120.0);
}

// Dump
void ECFlightItinerary::Dump() const
{
    std::cout << "Flight itinerary: " << std::endl;
    std::cout << "\tSrc: " << this->GetSegment(0)->GetSource() << " Dst: " << this->GetSegment(this->GetNumSegments() - 1)->GetDest() << " Num Flights: " << this->GetNumSegments() << std::endl;
    std::cout << "\tDeparture Time: " << this->GetDepartTime() << " Arrival Time: " << this->GetArrivalTime() << " Flight Time: " << this->GetFlightTime() << " Price: " << this->GetPrice() << std::endl; 
}

std::string ECFlightItinerary::ToString() const
{
    std::string str = "";
    for(int i = 0; i < this->GetNumSegments()-1; i++)
    {
        str += this->GetSegment(i)->ToString() + ", ";

    }
    str += this->GetSegment(this->GetNumSegments()-1)->ToString();
    return str;
}

// Add segment
void ECFlightItinerary::AddSegment(ECFlight* flight)
{
    this->flightSegments.push_back(flight);
}
    