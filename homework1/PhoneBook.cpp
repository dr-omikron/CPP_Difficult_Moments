#include "PhoneBook.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

PhoneBook::PhoneBook(std::ifstream &file)
{
    if(!file.is_open())
        std::cout << "File not found!" << std::endl;

    std::string line;
    while(std::getline(file, line))
    {
        std::string name, surname, patronymic, number, additional_number;
        uint16_t country_code, city_code;
        std::istringstream iss(line);
        iss >> surname >> name >> patronymic >> country_code >> city_code >> number >> additional_number;
        std::optional<uint16_t> o_additional_number;

        if (patronymic == "-")
            patronymic = "";
        
        if (additional_number == "-") 
            o_additional_number = std::nullopt;
        else
            o_additional_number = std::stoi(additional_number);
        
        _data.push_back(std::make_pair(Person(surname, name, patronymic),
            PhoneNumber(country_code, city_code, number, o_additional_number))); 
    }
    file.close();
}

void PhoneBook::SortByName()
{
    std::sort(_data.begin(), _data.end(),[](std::pair<Person,
        PhoneNumber> const &pair1, std::pair<Person, PhoneNumber> const &pair2){return pair1.first < pair2.first;});
}

void PhoneBook::SortByPhone()
{
    std::sort(_data.begin(), _data.end(), [](std::pair<Person,
        PhoneNumber> const &pair1, std::pair<Person, PhoneNumber> const &pair2){return pair1.second < pair2.second;});
}

std::tuple<std::string, PhoneNumber> PhoneBook::GetPhoneNumber(std::string const &surname)
{
    int16_t count = 0;
    PhoneNumber phone_number;
    auto find_surname = [surname, &count, &phone_number](std::pair<Person, PhoneNumber> const &pair1) 
    {
        if (pair1.first == surname)
        {
            count ++;
            phone_number = pair1.second;   
        }
    };
    std::for_each(_data.begin(), _data.end(), find_surname);
    std::string message = "";
    if (!count)
        message = "not found";
    else if(count > 1)
        message = "found more than 1";
    return {message, phone_number};
}

void PhoneBook::ChangePhoneNumber(Person const &person, PhoneNumber const &phone_number)
{
    auto find_person = [&person](std::pair<Person, PhoneNumber> const &pair1){return pair1.first == person;};
    auto result = std::find_if(_data.begin(), _data.end(), find_person);
    if (result != _data.end())
        result->second = phone_number; 
}

std::ostream& operator<<(std::ostream &out, PhoneBook const &phone_book)
{
    for (auto [fst, snd]: phone_book._data)
    std::cout << fst << " " << snd << std::endl;    
    return out; 
}
