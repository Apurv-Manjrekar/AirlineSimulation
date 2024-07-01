//
//  ECFlight.h
//  

#ifndef ECFlight_h
#define ECFlight_h

#include <string>


// ****************************************************************************
// Flight: service between two airports at a specific time;

class ECFlight 
{
public:
    ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn);
    ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn);
    
    virtual ~ECFlight();
    
    // Get departure time
    double GetDepartureTime() const;
    
    // Get arrival time
    double GetArrivalTime() const;
    
    // Set max passenger for this flight
    void SetMaxNumPassengers(int m);
    
    // Get src airport code
    std::string GetSource() const;
    
    // Get destination code
    std::string GetDest() const;

    // more to add...

    // Print flight   
    void Dump() const;
    
    std::string ToString() const;

    // Get flight time 
    double GetFlightTime() const;

private:
    std::string src; // source airport
    std::string dest; // destination airport
    double tmDepart; // departure time
    int maxPassengers; // max number of passengers
};

#endif /* ECFlight_h */
