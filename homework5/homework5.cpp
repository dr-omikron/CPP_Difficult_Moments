
#include <algorithm>
#include <deque>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

template<class IT>
void PrintUniqueWordsList(IT begin, IT end)
{
    std::set<std::string> unique_words;
    for(; begin!=end; ++begin)
        unique_words.emplace(*begin);
    std::copy(unique_words.begin(),unique_words.end(), std::ostream_iterator<std::string>{std::cout, " "} );
}

int main()
{
    // Ex1
    
    std::cout << "Vector" << std::endl;
    std::vector<std::string> v_patter {"four", "two", "six", "one", "three", "five",
                                       "seven", "one", "four", "two", "six", "three"};
    PrintUniqueWordsList(v_patter.begin(), v_patter.end());
    std::cout << "\nList" << std::endl;
    std::list<std::string> l_patter {"four", "two", "six", "one", "three", "five",
                                       "seven", "one", "four", "two", "six", "three"};
    PrintUniqueWordsList(l_patter.begin(), l_patter.end());
    std::cout << "\nDeque" << std::endl;
    std::deque<std::string> d_patter {"four", "two", "six", "one", "three", "five",
                                       "seven", "one", "four", "two", "six", "three"};
    PrintUniqueWordsList(d_patter.begin(), d_patter.end());
    std::cout << std::endl;

    // Ex2

    std::multimap<int32_t, std::string> mm_strings;
    std::string user_text;
    const std::string separator = ".!?";
    std:: cout << "Enter text > ";
    std::getline(std::cin, user_text);
    user_text.push_back('.');
    while (!user_text.empty())
    {
        const size_t pos = user_text.find_first_of(separator);
        std::string s_temp = user_text.substr(0, pos);
        user_text.erase(0, pos + 1);
        if(s_temp.empty()){continue;}
        const auto key = std::count_if(s_temp.begin(), s_temp.end(), [](const char ch){return isspace(ch);});
        mm_strings.emplace(key, s_temp);
    } 
    std::for_each (mm_strings.begin(),mm_strings.end(),[](const std::pair<int32_t, std::string> &str)
                                                                       {std::cout << str.second << std::endl;});
    return EXIT_SUCCESS;
}
