//
//  ECAirlineFinancial.cpp
//  
//
//  Created by Yufeng Wu on 5/16/23.
//

#include "ECAirlineFinancial.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"


#include <string>
#include <iostream>
using namespace std;

ECAirlineFinancial::ECAirlineFinancial()
{
    this->airlineOperation = nullptr;
}

ECAirlineFinancial::ECAirlineFinancial(ECAirlineOperation *pOperateIn)
{
    this->airlineOperation = pOperateIn;
}


// Get the price of the itinerary
double ECAirlineFinancial::CalculatePrice(const ECFlightItinerary& itinerary)
{
    return itinerary.GetPrice();
}

// Set airline operation
void ECAirlineFinancial::SetAirlineOperation(ECAirlineOperation* ao)
{
    this->airlineOperation = ao;
}

void ECAirlineFinancial::SetAirlineTicketing(ECAirlineTicketing* at)
{
    this->airlineTicketing = at;
}

void ECAirlineFinancial::RegisterPassenger(ECPassenger *pPassenger)
{
    this->listPassengers.push_back(pPassenger);
}

int ECAirlineFinancial::GetNumPassengers() const
{
    return this->listPassengers.size();
}

ECPassenger* ECAirlineFinancial::GetPassenger(int k) const
{
    return this->listPassengers[k];
}

double ECAirlineFinancial::Quote(const ECFlightItinerary& itin) const
{
    return itin.GetPrice();
}

double ECAirlineFinancial::GetRevenue() const
{
    return this->balance;
}

double ECAirlineFinancial::GetBalance() const
{
    return this->balance;
}

void ECAirlineFinancial::Paid(double amt)
{
    this->balance += amt;
}

void ECAirlineFinancial::Charged(double amt)
{
    this->balance -= amt;
}

void ECAirlineFinancial::Dump() const
{
    cout << "Balance: " << this->balance << endl;
}