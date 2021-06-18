#pragma once
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

class MatrixFor
{
public:
    explicit MatrixFor(std::vector<std::vector<int32_t>> matrix) : _matrix(matrix), _size(matrix.size()),
                                                                   _determinant(0){}
    void PrintMatrix() const
    {
        std::for_each(_matrix.begin(), _matrix.end(), [](std::vector<int32_t> m_strings)
          {
             std::for_each(m_strings.begin(), m_strings.end(), [] (int32_t &value) {std::cout << std::setw(2) << value << "  ";});
             std::cout << std::endl;
          });
    }
    int32_t GetDeterminant() 
    {
        return Determinant(_matrix, _size);
    }
private:
    std::vector<std::vector<int32_t>> _matrix;
    size_t _size;
    int32_t _determinant;
    int32_t Determinant(std::vector<std::vector<int32_t>> matrix, size_t size) 
    {
        if (size == 1)
            return matrix[0][0];
        if (size == 2)
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        if (size >= 3)
        {
            std::vector<std::vector<int32_t>> minor;
            minor.assign(size-1, {0});
            std::for_each(minor.begin(), minor.end(), [size](std::vector<int32_t> &m_strings)
            {
                m_strings.assign(size-1,0);
            });
            for(size_t k = 0; k < size; k++)
            {
                int32_t a = 0;
                for(size_t i = 1; i < size; i++)
                {
                    int32_t b = 0;
                    for(size_t j = 0; j < size; j++)
                    {
                        if (j != k)
                        {
                            minor[a][b] = matrix[i][j];
                            b++;
                        }
                    }
                    a++;
                }
                _determinant += static_cast<int32_t>(pow(-1, k + 2)) * matrix[0][k] * Determinant(minor, size-1);
            }
            return _determinant;
        }
    }
};
