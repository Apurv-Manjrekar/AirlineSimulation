//
//  ECAirlineOperation.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//  About operation of an airline: especially flights management

#ifndef ECAirlineOperation_h
#define ECAirlineOperation_h

#include <vector>
#include "ECFlight.h"


// put your code about airline operation here.  ..

class ECAirlineFinancial;
class ECAirlineTicketing;

class ECAirlineOperation
{
public:
    ECAirlineOperation();
    ECAirlineOperation(ECAirlineFinancial* af, ECAirlineTicketing* at);
    void AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart);
    void AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate);
    void PostFlightSetup();
    std::vector<ECFlight*> GetFlights() const;
    int GetNumFlights() const;
    void SetAirlineFinancial(ECAirlineFinancial* af);
    void SetAirlineFin(ECAirlineFinancial* af);
    void SetAirlineTicketing(ECAirlineTicketing* at);
    void Dump();
private:
    std::vector<ECFlight*> listFlights;
    ECAirlineFinancial* airlineFinancial;
    ECAirlineTicketing* airlineTicketing;
};

#endif
