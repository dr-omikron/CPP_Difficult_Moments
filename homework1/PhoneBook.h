#pragma once
#include "Person.h"
#include "PhoneNumber.h"

#include <vector>

class PhoneBook
{
public:
    explicit PhoneBook(std::ifstream& file);
    void SortByName();
    void SortByPhone();
    std::tuple<std::string, PhoneNumber> GetPhoneNumber(std::string const &surname);
    void ChangePhoneNumber (Person const &person, PhoneNumber const &phone_number);
    friend std::ostream& operator << (std::ostream &out, PhoneBook const &phone_book);
private:
    std::pmr::vector<std::pair<Person, PhoneNumber>> _data;
};
