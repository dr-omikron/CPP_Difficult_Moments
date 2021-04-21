#pragma once
#include <cstdint>
#include <optional>
#include <string>

struct PhoneNumber
{
private:
   uint16_t _country_code;
   uint16_t _city_code;
   std::string _number;
   std::optional <uint16_t> _additional_number;
public:
   PhoneNumber(): _country_code(0), _city_code(0), _additional_number(std::nullopt){}
   PhoneNumber(uint16_t country_code, uint16_t city_code,
   std::string number, std::optional <uint16_t> additional_number);
   //void SetNumber(PhoneNumber const &phone_number);
   bool operator < (PhoneNumber const &phone_number) const;
   friend std::ostream& operator << (std::ostream &out, PhoneNumber const &phone_number);
};
