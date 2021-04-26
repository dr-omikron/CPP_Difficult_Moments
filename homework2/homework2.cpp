#include "Timer.h"
#include "functions.h"

int main()
{
    // Ex1

    std::cout << "Ex 1" << std::endl;
    const int16_t value1 = 32;
    const int16_t value2 = 155;
    const int16_t *ipt = new int16_t (value1);
    const int16_t *dpt = new int16_t (value2);
    std::cout << *ipt <<"\t" << *dpt <<std::endl;
    Swap(ipt, dpt);
    std::cout << *ipt <<"\t" << *dpt << std::endl;
    delete ipt, dpt;

    // Ex2

    std::cout << "Ex 2" << std::endl;
    constexpr uint16_t ARR_SIZE = 8;
    std::vector<int16_t*> arr_ptr;
    for(size_t i = 0; i < ARR_SIZE; ++i)
    {
        int16_t *vpt = new int16_t;
        *vpt = rand() % 100;
        arr_ptr.push_back(vpt);
    }
    PrintVector(arr_ptr);
    SortPointers(arr_ptr);
    PrintVector(arr_ptr);
    std::for_each(arr_ptr.begin(), arr_ptr.end(),[](int16_t *vpt){delete vpt;});
    
    // Ex3
    
    std::cout << "Ex 3" << std::endl;
    setlocale (LC_ALL, "Russian_Russia.1251");    
    std::ifstream file ("war_and_peace.txt");
    if(file.is_open())
    {
        int64_t vowel_counter = 0;
        const Timer timerFO("VowelCounterForOnly");
        VowelCounterForOnly(file, vowel_counter);
        timerFO.Print();
        PrintCounter(vowel_counter);
        file.close();
        vowel_counter = 0;
        file.open("war_and_peace.txt");
        const Timer timerFF("VowelCounterForFind");
        VowelCounterForFind(file, vowel_counter);
        timerFF.Print();
        PrintCounter(vowel_counter);
        file.close();
        vowel_counter = 0;
        file.open("war_and_peace.txt");
        const Timer timerFCF("VowelCounterCifFor");
        VowelCounterCifFor(file, vowel_counter);
        timerFCF.Print();
        PrintCounter(vowel_counter);
        file.close();
        vowel_counter = 0;
        file.open("war_and_peace.txt");
        const Timer timerFCFind("VowelCounterCifFind");
        VowelCounterCifFind(file, vowel_counter);
        timerFCFind.Print();
        PrintCounter(vowel_counter);
        file.close();
    }
    else
    {
        std::cout << "File not found!" << std::endl;
    }

    // Debug
    // Vowel characters:       157883
    // VowelCounterForOnly:    133.625 ms
    // VowelCounterForFind:    812.234 ms
    // VowelCounterCifFor:     218.344 ms
    // VowelCounterCifFind:    199.441 ms

    // Release
    // VowelCounterForOnly:    10.9076 ms
    // VowelCounterForFind:    39.9499 ms
    // VowelCounterCifFor:     12.7851 ms
    // VowelCounterCifFind:    10.9789 ms

    return EXIT_SUCCESS;
}
