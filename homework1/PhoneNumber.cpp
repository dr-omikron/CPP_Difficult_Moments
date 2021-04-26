#include <iostream>
#include "PhoneNumber.h"

PhoneNumber::PhoneNumber(const uint16_t country_code, const uint16_t city_code,
    const std::string number, const std::optional<uint16_t> additional_number):
    _country_code(country_code), _city_code(city_code), _number(number),
    _additional_number(additional_number){}

/*void PhoneNumber::SetNumber(PhoneNumber const &phone_number)
{
    _country_code = phone_number._country_code;
    _city_code = phone_number._city_code;
    _number = phone_number._number;
    _additional_number =  phone_number._additional_number;
}*/

bool PhoneNumber::operator < (PhoneNumber const &phone_number) const
{
    return std::tie(_country_code, _city_code, _number, _additional_number) <
        std::tie(phone_number._country_code, phone_number._city_code,
        phone_number._number, phone_number._additional_number);
}

std::ostream& operator << (std::ostream &out, PhoneNumber const &phone_number)
{
    out << "+" << phone_number._country_code << "(" << phone_number._city_code << ")" << phone_number._number << " ";
    if (phone_number._additional_number.has_value()) out << phone_number._additional_number.value();
    return out;
}
