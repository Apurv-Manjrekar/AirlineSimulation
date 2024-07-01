//
//  ECAirlineTicketing.h
//  

#ifndef ECAirlineTicketing_h
#define ECAirlineTicketing_h

#include <vector>
#include <stack>
#include <set>
#include <string>
#include "ECFlightItinerary.h"

class ECAirlineOperation;
class ECAirlineFinancial;

typedef enum {
    ECFlightPreferenceLowPrice = 0,
    ECFlightPreferenceEarlyArrival = 1,
    ECFlightPreferenceShortTime = 2,
    ECFlightPreferenceSmallestSegments = 3
} ECFlightPreference;

// ****************************************************************************
// Airline ticketing: search for flights, issue tickets, etc
class ECAirlineTicketing {
public:
    ECAirlineTicketing();
    ECAirlineTicketing(ECAirlineOperation* ao, ECAirlineFinancial* af);
    void SearchForItinerary(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries);
    void SearchForItinerary(const std::string &src, const std::string &dest, const int &tmDepart, std::vector<ECFlightItinerary> &listItineraries);
    void BFS(const std::string& src, const std::string& dest, std::stack<std::vector<ECFlight*>>& flightStack, std::stack<std::set<std::string>>& airportStack, std::vector<ECFlight*>& listFlights, std::vector<ECFlightItinerary>& listItineraries);
    void OrderItineraries(std::vector<ECFlightItinerary>& listItineraries);
    void ClearPreference();
    void SetPreferences(const std::vector<ECFlightPreference>& listPreferences);
    void PreferLowPrice();
    void PreferEarlyArrival();
    void PreferShortTime();
    void PreferSmallestSegments();
    void SetAirlineFinancial(ECAirlineFinancial* af);
    void SetAirlineOperation(ECAirlineOperation* ao);
    ECAirlineFinancial* GetAirlineFinancial();
private:
    ECAirlineOperation* airlineOperation;
    ECAirlineFinancial* airlineFinancial;
    std::vector<ECFlightPreference> listPreferences;
};

#endif /* ECAirlineTicketing_h */
