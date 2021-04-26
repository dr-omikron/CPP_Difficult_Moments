#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

template <class T1>

void Swap(const T1 *&ptr1, const T1 *&ptr2)
{
    const T1 *ptr_temp = ptr2;
    ptr2 = ptr1;
    ptr1 = ptr_temp;
}

void SortPointers (std::vector<int16_t*> &arr_ptr)
{
    const size_t size = arr_ptr.size();
    for (int counter = 1; counter < size; counter++)
    {
        int16_t *temp = arr_ptr[counter];
        int16_t item = counter - 1;
        while (item >= 0 && *arr_ptr[item] > *temp)
        {
            arr_ptr[item + 1] = arr_ptr[item];
            arr_ptr[item] = temp;
            item--;
        }
    }
}

void PrintVector(std::vector<int16_t*> const &arr_ptr)
{
    for (auto vpt: arr_ptr)
        std::cout << *vpt << " ";
    std::cout << std::endl;
}

void VowelCounterForOnly(std::ifstream &file, int64_t &counter)
{
    for(std::string word; file >> word;)
        for(char &ch : word)
        {
            if(ch == 'À'||ch == 'à'||ch == 'È' ||ch == 'è' ||ch == 'Å'||ch == 'å'||ch == 'Î'||ch == 'î'|| ch == 'Ó'
                ||ch == 'ó'||ch == 'û'||ch == 'Ý'||ch == 'ý'||ch == 'Þ'||ch == 'þ'||ch == 'ß'||ch == 'ÿ')
                counter++;
        }
}

void VowelCounterForFind(std::ifstream &file, int64_t &counter)
{
    for(char ch; file.get(ch);)
    {
        std::string vowels("ÀÈÅÎÓÝÞßàèåîóûýþÿ");
        const auto found = vowels.find(ch);
        if(found != std::string::npos)
            counter++;
    }
}

void VowelCounterCifFor(std::ifstream &file, int64_t &counter)
{
    std::string vowels("ÀÈÅÎÓÝÞßàèåîóûýþÿ");
    for(std::string word; file >> word;)
    {
        counter += std::count_if(word.begin(), word.end(), [&vowels] (char const &ch)
                                        {for (char &vowel: vowels)
                                             if (vowel == ch)
                                                 return true;
                                         return false;});
    } 
}

void VowelCounterCifFind(std::ifstream &file, int64_t &counter)
{
    std::string vowels("ÀÈÅÎÓÝÞßàèåîóûýþÿ");
    for(std::string word; file >> word;)
    {
        counter += std::count_if(word.begin(), word.end(), [&vowels] (char const &ch)
                                       {return vowels.find(ch) != std::string::npos;});
    }
    
}

void PrintCounter(int64_t &counter)
{
    std::cout << "Vowel characters:\t" << counter << std::endl;   
}
