#include "Person.h"

#include <iomanip>
#include <iostream>
#include <tuple>

bool Person::operator < (Person const &person) const
{
   return std::tie(_surname, _name, _patronymic) <
      std::tie(person._surname, person._name, person._patronymic);
}

bool Person::operator == (Person const &person) const
{
    return std::tie(_name, _surname, _patronymic) ==
       std::tie(person._name, person._surname, person._patronymic); 
}
bool Person::operator == (std::string const &str) const
{
    return _surname == str; 
}
std::ostream& operator<<(std::ostream& out, Person const &person)
{
    return out << std::right << std::setw(12) << person._surname << "  "
    << std::right << std::setw(10) << person._name << "  "
    << std::right << std::setw(15) << person._patronymic << " ";
}
