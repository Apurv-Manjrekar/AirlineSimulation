//
//  ECAirport.cpp
//  

#include "ECAirport.h"

// ****************************************************************************
// Airport: start/end point of a flight

// by default, airport is operating (except in default constructor)
ECAirport::ECAirport()
{
    this->operating = false;
}

// Create a new airport in the system
ECAirport::ECAirport(const std::string &nameAP, const std::string &codeIATA)
{
    this->name = nameAP;
    this->code = codeIATA;
    this->operating = true;
}

// Copy constructor
ECAirport::ECAirport(const ECAirport &rhs)
{
    if(this != &rhs)
    {
        this->name = rhs.name;
        this->code = rhs.code;
        this->operating = rhs.operating;
    }
}

// Get the name of the airport
std::string ECAirport::GetName() const { return this->name; }

// Get IATA code
std::string ECAirport::GetCode() const { return this->code; }

// Operating status: is it operating normally?
bool ECAirport::IsOperating() { return this->operating; }

// Set operating status
void ECAirport::SetOperating(bool f)
{
    this->operating = f;
}

// ****************************************************************************
// Airport info: access airport information
// Use singleton pattern

// Create a new airport in the system
void ECAirportInfo::CreateAirport(const std::string &name, const std::string &code)
{
    this->airports[code] = new ECAirport(name, code);
}

// Get airport by code
// Throw exception (std::string) if there is no airport with the code
ECAirport& ECAirportInfo::GetAirport(const std::string &code)
{
    if(this->airports.find(code) == this->airports.end())
    {
        throw std::string("No airport with code " + code + " found.");
    }
    return *this->airports[code];
}

// Set distance (in miles) between airports
void ECAirportInfo::SetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code, int dist)
{
    this->distances[std::pair<std::string, std::string>(ap1Code, ap2Code)] = dist;
    this->distances[std::pair<std::string, std::string>(ap2Code, ap1Code)] = dist;
    this->SetFlightTimeBtw(ap1Code, ap2Code, dist);
}

// more to add...
int ECAirportInfo::GetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code) const
{
    auto iter = this->distances.find(std::pair<std::string, std::string>(ap1Code, ap2Code));
    if(iter == distances.end())
    {
        throw std::string("No distance between " + ap1Code + " and " + ap2Code + " found.");
    }
    return iter->second;
}

void ECAirportInfo::SetFlightTimeBtw(const std::string &ap1Code, const std::string &ap2Code, int dist)
{
    this->flightTimes[std::pair<std::string, std::string>(ap1Code, ap2Code)] = dist/500.0;
}

double ECAirportInfo::GetFlightTimeBtw(const std::string &ap1Code, const std::string &ap2Code) const
{
    auto iter = this->flightTimes.find(std::pair<std::string, std::string>(ap1Code, ap2Code));
    if(iter == flightTimes.end())
    {
        throw std::string("No flight time between " + ap1Code + " and " + ap2Code + " found.");
    }
    return iter->second;
}

void ECAirportInfo::GetAllAirportCode(std::set<std::string> &getAirports) const
{
    for(auto airportCode : this->airports)
    {
        getAirports.insert(airportCode.first);
    }
}

// Singleton
ECAirportInfo* ECAirportInfo::_instance = nullptr;

// Get the instance
ECAirportInfo* ECAirportInfo::Instance()
{
    if(_instance == nullptr)
    {
        _instance = new ECAirportInfo();
    }
    return _instance;
}
