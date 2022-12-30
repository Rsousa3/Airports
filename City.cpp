//
// Created by ricardo on 29-12-2022.
//

#include "City.h"

using namespace std;

City::City(): city(), country() {}

City::City(string cidade, string pais): city(cidade), country(pais) {}

string City::getCity() {return city;}