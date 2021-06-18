#include <fstream>
#include <iostream>
#include <variant>

#include "Person.h"
#include "PhoneNumber.h"
#include "PhoneBook.h"

int main()
{
    std::ifstream file("PhoneBook.txt");
    PhoneBook book(file);
    std::cout << book;
 
    std::cout << "------SortByPhone-------" << std::endl;
    book.SortByPhone();
    std::cout << book;
 
    std::cout << "------SortByName--------" << std::endl;
    book.SortByName();
    std::cout << book;
 
    std::cout << "-----GetPhoneNumber-----" << std::endl;
    auto print_phone_number = [&book](std::string const surname)
    {   auto result = book.GetPhoneNumber(surname);
        if(std::get<0>(result) == "")
            std::cout << surname << " " << std::get<1>(result) << std::endl;  
        else
            std::cout << surname << " " << std::get<0>(result) << std::endl; 
    };

    print_phone_number("Ivanov");
    print_phone_number("Petrov");
 
    std::cout << "----ChangePhoneNumber----" << std::endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
    PhoneNumber{7, 123, "15344458", std::nullopt});
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
                      PhoneNumber{ 16, 465, "9155448", 13 });
    std::cout << book;

    return EXIT_SUCCESS;
}
