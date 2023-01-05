//
// Created by ricardo on 29-12-2022.
//

#include "Airport.h"
#include "City.h"
#include "Position.h"

using namespace std;

Airport::Airport(): code(), name(), city(), position()  {}
Airport::Airport(string codigo, string nome, City cidade, Position pos): code(codigo), name(nome), city(cidade), position(pos) {}

Position Airport::getPosition() {return position;}

City Airport::getCity() {return city;}

string Airport::getCityName() {return city.getCity();}

string Airport::getCode() {return code;}

string Airport::getName() {return name;}

string Airport::getCountryName() {return city.getCountry();}
