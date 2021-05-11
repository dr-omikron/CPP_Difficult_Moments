#include "Matrix.h"
#include "MatrixFor.h"
#include "Iterator.h"
#include <iostream>
#include <numeric>
#include <vector>




void PushBackAverage(std::vector<double> &v)
{
    const double sum = std::accumulate(v.begin(), v.end(), 0.0);
    v.push_back(sum/v.size());
}

int main()
{
    //Ex 1
    
    std::vector<double> flv {4.5, 6.8, 15.7, 45.9, 8.3};
    PushBackAverage(flv);
    std::cout << flv.back() << std::endl;
        
    //Ex 2

    Matrix m1;
    m1.PrintMatrix();
    std::cout << "Determinant: " << m1.GetDeterminant() << std::endl;
    const size_t v_size = 5;
    std::vector<std::vector<int32_t>> m_for_constr(v_size);
    std::for_each(m_for_constr.begin(), m_for_constr.end(), [v_size](std::vector<int32_t> &m_strings)
        {
           m_strings.assign(v_size,0);
           std::generate(m_strings.begin(), m_strings.end(), [] () {return rand() % 8 - 2;});
        });
    MatrixFor m2(m_for_constr);
    m2.PrintMatrix();
    std::cout << "Determinant: " << m2.GetDeterminant() << std::endl;

    //Ex 3

    for (auto i : Range<int32_t> {100, 150})
        std::cout << i << " ";
    
    return 0;
}
