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

string Airport::getCityName() {return city.getCity();}

string Airport::getCode() {return code;}
