//
//  ECFlight.cpp
//  

#include "ECFlight.h"
#include "ECAirport.h"

#include <iostream>
using namespace std;

// ECFlight constructor

ECFlight::ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn)
{
    this->src = srcIn;
    this->dest = destIn;
    this->tmDepart = tmDepartIn;
}

ECFlight::ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn)
{
    this->src = srcIn; 
    this->dest = destIn;
    this->tmDepart = tmDepartIn;
    this->maxPassengers = maxPassengersIn;
}

// ECFlight destructor
ECFlight::~ECFlight() {}

// Get departure time
double ECFlight::GetDepartureTime() const { return this->tmDepart; }

// Get arrival time
double ECFlight::GetArrivalTime() const
{
    return (this->GetDepartureTime() + (ECAirportInfo::Instance()->GetDistanceBtw(this->GetSource(), this->GetDest()) / 500.0));
}

// Set max passenger for this flight
void ECFlight::SetMaxNumPassengers(int m)
{
    this->maxPassengers = m;
}

// Get src airport code
std::string ECFlight::GetSource() const { return this->src; }

// Get destination code
std::string ECFlight::GetDest() const { return this->dest; }

// more to add...    

// print flight
void ECFlight::Dump() const
{
    cout << "Src: " << this->src << " Dest: " << this->dest << " Depart: " << this->tmDepart << " Arrive: " << this->GetArrivalTime() << " Passengers: " << this->maxPassengers << endl;
}

std::string ECFlight::ToString() const
{
    std::string departTime = std::to_string(this->GetDepartureTime());
    std::string arriveTime = std::to_string(this->GetArrivalTime());
    departTime = departTime.substr(0, departTime.find_last_not_of("0")+2);
    arriveTime = arriveTime.substr(0, arriveTime.find_last_not_of("0")+2);
    std::string str = this->src + " -> " + this->dest + " (" + departTime + "-" + arriveTime + ")";
    return str;
}

// get flight time
double ECFlight::GetFlightTime() const
{
    return (this->GetArrivalTime() - this->GetDepartureTime());
}