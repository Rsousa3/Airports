//
// Created by ricardo on 29-12-2022.
//

#include "Airline.h"

using namespace std;

Airline::Airline(): code(), name(), callsign(), country() {}

Airline::Airline(string cod, string nome, string sign, string pais): code(cod), name(nome), callsign(sign), country(pais) {}

string Airline::getName() {return name;}