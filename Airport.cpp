//
// Created by ricardo on 29-12-2022.
//

#include "Airport.h"
#include "City.h"
#include "Position.h"

using namespace std;

Airport::Airport(string codigo, string nome, City cidade, Position pos): code(codigo), name(nome), city(cidade), position(pos) {}

