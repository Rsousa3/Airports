//
// Created by ricardo on 29-12-2022.
//

#ifndef UNTITLED1_CITY_H
#define UNTITLED1_CITY_H

#include <string>

using namespace std;

class City {
    string city;
    string country;

public:
    City();
    City(string cidade, string pais);
    string getCity();
};
#endif //UNTITLED1_CITY_H
