//
//  ECAirlineOperation.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECAirlineOperation.h"
#include "ECAirlineFinancial.h"
#include "ECAirlineTicketing.h"

#include <iostream>
#include <string>
using namespace std;

ECAirlineOperation::ECAirlineOperation()
{
    this->airlineFinancial = nullptr;
    this->airlineTicketing = nullptr;
}

ECAirlineOperation::ECAirlineOperation(ECAirlineFinancial* af, ECAirlineTicketing* at)
{
    this->airlineFinancial = af;
    this->airlineTicketing = at;
}

void ECAirlineOperation::AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart)
{
    ECFlight* newFlight = new ECFlight(srcAirport, destAirport, tmDepart);
    this->listFlights.push_back(newFlight);
}

void ECAirlineOperation::AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate)
{
    ECFlight* newFlight = new ECFlight(srcAirport, destAirport, tmDepart, maxPassengers);
    this->listFlights.push_back(newFlight);
    this->airlineFinancial->Charged(costOperate);
}
void ECAirlineOperation::PostFlightSetup() {}

std::vector<ECFlight*> ECAirlineOperation::GetFlights() const
{
    return this->listFlights;
}

int ECAirlineOperation::GetNumFlights() const
{
    return this->listFlights.size();
}

void ECAirlineOperation::SetAirlineFinancial(ECAirlineFinancial* af)
{
    this->airlineFinancial = af;
}

void ECAirlineOperation::SetAirlineFin(ECAirlineFinancial* af)
{
    this->SetAirlineFinancial(af);
}

void ECAirlineOperation::SetAirlineTicketing(ECAirlineTicketing* at)
{
    this->airlineTicketing = at;
}

void ECAirlineOperation::Dump()
{
    cout << "Airline Operation: " << endl;
    cout << "Num Flights: " << this->GetNumFlights() << endl;
}

