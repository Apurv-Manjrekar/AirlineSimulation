//
//  ECAirlineTicketing.cpp
//  

#include "ECAirlineTicketing.h"
#include "ECAirlineOperation.h"
#include "ECAirlineFinancial.h"
// #include "ECAirport.h"
#include <stack>
#include <set>
#include <algorithm>
#include <iostream>

ECAirlineTicketing::ECAirlineTicketing()
{
    this->airlineOperation = nullptr;
    this->airlineFinancial = nullptr;
}

ECAirlineTicketing::ECAirlineTicketing(ECAirlineOperation* ao, ECAirlineFinancial* af)
{
    this->airlineOperation = ao;
    this->airlineFinancial = af;
}

void ECAirlineTicketing::SearchForItinerary(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries)
{
    std::vector<ECFlight*> listFlights = this->airlineOperation->GetFlights(); // get flights
    std::stack<std::vector<ECFlight*>> flightStack; // flight stack
    std::stack<std::set<std::string>> airportStack; // airport stack
    // get flights that depart from src
    for(auto& flight : listFlights)
    {
        if(flight && flight->GetSource() == src)
        {
            std::set<std::string> visitedAirports; // set of visited airports for that itinerary
            visitedAirports.insert(flight->GetSource()); // insert src airport
            flightStack.push({flight}); // push flight
            airportStack.push(visitedAirports); // push visited airports
            
        }
    }
    this->BFS(src, dest, flightStack, airportStack, listFlights, listItineraries);
}

void ECAirlineTicketing::SearchForItinerary(const std::string& src, const std::string& dest, const int& tmDepart, std::vector<ECFlightItinerary>& listItineraries)
{
    std::vector<ECFlight*> listFlights = this->airlineOperation->GetFlights(); // get flights
    std::stack<std::vector<ECFlight*>> flightStack; // flight stack
    std::stack<std::set<std::string>> airportStack; // airport stack
    // get flights that depart from src
    for(auto& flight : listFlights)
    {
        if(flight && flight->GetSource() == src && flight->GetDepartureTime() >= tmDepart)
        {
            std::set<std::string> visitedAirports; // set of visited airports for that itinerary
            visitedAirports.insert(flight->GetSource()); // insert src airport
            flightStack.push({flight}); // push flight
            airportStack.push(visitedAirports); // push visited airports
            
        }
    }
    this->BFS(src, dest, flightStack, airportStack, listFlights, listItineraries);
}

void ECAirlineTicketing::BFS(const std::string& src, const std::string& dest, std::stack<std::vector<ECFlight*>>& flightStack, std::stack<std::set<std::string>>& airportStack, std::vector<ECFlight*>& listFlights, std::vector<ECFlightItinerary>& listItineraries)
{
    // while flight stack is not empty
    while(!flightStack.empty())
    {
        // Get the top itinerary and top visited airports
        auto currItinerary = flightStack.top();
        flightStack.pop();
        auto visitedAirports = airportStack.top();
        airportStack.pop();
        // if the top itinerary is empty, continue
        if(currItinerary.empty())
        {
            continue;
        }

        auto lastFlight = currItinerary.back(); // get last flight in itinerary
        // if the last flight is the destination, add the itinerary to the result
        if(lastFlight->GetDest() == dest)
        {
            listItineraries.push_back(ECFlightItinerary(currItinerary));
            continue;
        }
        // get flights that depart from the last flight's destination and are not visited, and add them to the stack
        for(auto& flight : listFlights)
        {
            if(flight->GetSource() == lastFlight->GetDest() && flight->GetDepartureTime() >= lastFlight->GetArrivalTime())
            {
                std::set<std::string> newVisitedAirports = visitedAirports;
                if(visitedAirports.find(flight->GetDest()) == visitedAirports.end())
                {
                    auto newItinerary = currItinerary;
                    newItinerary.push_back(flight);
                    newVisitedAirports.insert(flight->GetSource());
                    flightStack.push(newItinerary);
                    airportStack.push(newVisitedAirports);
                }
                
            }
        }
    }
}

void ECAirlineTicketing::OrderItineraries(std::vector<ECFlightItinerary>& listItineraries)
{
    std::sort(listItineraries.begin(), listItineraries.end(), [&](const ECFlightItinerary& a, const ECFlightItinerary& b)
    {
        for(int i = 0; i < listPreferences.size(); ++i)
        {
            if(listPreferences[i] == ECFlightPreference::ECFlightPreferenceLowPrice)
            {
                if(a.GetPrice() == b.GetPrice())
                {
                    continue;
                }
                return a.GetPrice() < b.GetPrice();
                
            }
            else if(listPreferences[i] == ECFlightPreference::ECFlightPreferenceEarlyArrival)
            {
                if(a.GetArrivalTime() == b.GetArrivalTime())
                {
                    continue;
                }
                return a.GetArrivalTime() < b.GetArrivalTime();
            }
            else if(listPreferences[i] == ECFlightPreference::ECFlightPreferenceShortTime)
            {
                if(a.GetFlightTime() == b.GetFlightTime())
                {
                    continue;
                }
                return a.GetFlightTime() < b.GetFlightTime();
            }
            else if(listPreferences[i] == ECFlightPreference::ECFlightPreferenceSmallestSegments)
            {
                if(a.GetNumSegments() == b.GetNumSegments())
                {
                    continue;
                }
                return a.GetNumSegments() < b.GetNumSegments();
            }
        }
        return false;
    });
}

void ECAirlineTicketing::ClearPreference()
{
    listPreferences.clear();
}

void ECAirlineTicketing::SetPreferences(const std::vector<ECFlightPreference>& listPreferences)
{
    this->listPreferences = listPreferences;
}

void ECAirlineTicketing::PreferLowPrice()
{
    listPreferences.push_back(ECFlightPreference::ECFlightPreferenceLowPrice);
}

void ECAirlineTicketing::PreferEarlyArrival()
{
    listPreferences.push_back(ECFlightPreference::ECFlightPreferenceEarlyArrival);
}

void ECAirlineTicketing::PreferShortTime()
{
    listPreferences.push_back(ECFlightPreference::ECFlightPreferenceShortTime);
}

void ECAirlineTicketing::PreferSmallestSegments()
{
    listPreferences.push_back(ECFlightPreference::ECFlightPreferenceSmallestSegments);
}

void ECAirlineTicketing::SetAirlineFinancial(ECAirlineFinancial* af)
{
    this->airlineFinancial = af;
}

void ECAirlineTicketing::SetAirlineOperation(ECAirlineOperation* ao)
{
    this->airlineOperation = ao;
}

ECAirlineFinancial* ECAirlineTicketing::GetAirlineFinancial()
{
    return this->airlineFinancial;
}