//
//  ECAirport.h
//  

#ifndef ECAirport_h
#define ECAirport_h

#include <string>
#include <set>
#include <map>

// ****************************************************************************
// Airport: start/end point of a flight

class ECAirport 
{
public:
    // by default, airport is operating (except in default constructor)
    ECAirport(); 
    ECAirport(const std::string &nameAP, const std::string &codeIATA);
    ECAirport(const ECAirport &rhs);
    
    // Get the name of the airport
    std::string GetName() const;
    
    // Get IATA code
    std::string GetCode() const;
    
    // Operating status: is it operating normally?
    bool IsOperating();
    
    // Set operating status
    void SetOperating(bool f);
    
private:
    bool operating; // keeps track of whether the airport is operating
    std::string name; // name of the airport
    std::string code; // IATA code
};

// ****************************************************************************
// Airport info: access airport information
// Use singleton pattern

class ECAirportInfo
{
public:
    
    // Create a new airport in the system
    void CreateAirport(const std::string &name, const std::string &code);
    
    // Get airport by code
    // Throw exception (std::string) if there is no airport with the code
    ECAirport &GetAirport(const std::string &code);
    
    // Set distance (in miles) between airports
    void SetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code, int dist);

    // more to add...

    // Get distance (in miles) between airports
    int GetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code) const;

    void SetFlightTimeBtw(const std::string &ap1Code, const std::string &ap2Code, int dist);

    double GetFlightTimeBtw(const std::string &ap1Code, const std::string &ap2Code) const;

    void GetAllAirportCode(std::set<std::string> &getAirports) const;
    
    // Get singleton instance
    static ECAirportInfo* Instance();
    
private:    
    static ECAirportInfo* _instance; // singleton instance
    std::map<std::string, ECAirport*> airports; // map from IATA code to airport
    std::map<std::pair<std::string, std::string>, int> distances; // map from (code1, code2) to distance
    std::map<std::pair<std::string, std::string>, double> flightTimes;
};


#endif /* ECAirport_h */
