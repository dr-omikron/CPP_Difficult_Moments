
#include <algorithm>
#include <complex>
#include <deque>
#include <iostream>
#include <numeric>
#include <ostream>
#include <stdlib.h>
#include <vector>

template <class T, class CNT>
void InsertSorted(CNT &cnt, const T ins_num)
{
    typename CNT::iterator it;
    it = std::upper_bound(cnt.begin(), cnt.end(), ins_num);
    cnt.insert(it, ins_num);
}
template <class CNT>
void PrintContainer(CNT const &cnt)
{
    for (auto i : cnt)
       std::cout << i << " ";
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    // Ex1
    srand(time(NULL));
    std::vector<int32_t> sorted_vector(10);
    std::generate(sorted_vector.begin(), sorted_vector.end(),[](){return rand() % 50;});
    std::sort(sorted_vector.begin(), sorted_vector.end());
    PrintContainer(sorted_vector);
    InsertSorted(sorted_vector, 25);
    PrintContainer(sorted_vector);
    std::deque<int32_t> sorted_deque(10);
    std::generate(sorted_deque.begin(), sorted_deque.end(),[](){return rand() % 50;});
    std::sort(sorted_deque.begin(), sorted_deque.end());
    PrintContainer(sorted_deque);
    InsertSorted(sorted_deque, 25);
    PrintContainer(sorted_deque);
    
    // Ex2
    std::vector<double> analog_signal(100);
    std::vector<int32_t> digital_signal(100);
    std::generate(analog_signal.begin(), analog_signal.end(),[](){return static_cast<double>(rand())/RAND_MAX * 10 - 5;});
    std::transform(analog_signal.begin(), analog_signal.end(), digital_signal.begin(), [](double x)
        {return static_cast<int32_t>(round(x));});
    PrintContainer(analog_signal);
    PrintContainer(digital_signal);
    const auto result = std::inner_product(digital_signal.begin(),digital_signal.end(),
                analog_signal.begin(), 0.0, std::plus<>(), std::minus<>());
    std::cout << result*result << "\n";
    
    return EXIT_SUCCESS;
}
