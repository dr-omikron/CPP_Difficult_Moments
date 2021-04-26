#pragma once
#include <string>

struct Person
{
private:
    std::string _name, _surname, _patronymic;
public:
    Person(std::string surname, std::string name , std::string patronymic = ""):
    _name(name), _surname(surname), _patronymic(patronymic){}
    bool operator < (Person const &person) const;
    bool operator == (Person const &person) const;
    bool operator==(std::string const &str) const;
    friend std::ostream& operator <<(std::ostream& out, Person const &person);
};
