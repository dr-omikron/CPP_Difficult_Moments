#pragma once
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

class Matrix
{
public:
    Matrix()
    {
        while (true)
        {
            _size = 0;
            std::cout << "Enter the order of the matrix (1/3) > ";
            std::cin >> _size;
            if(_size > 0 && _size <= 3)
                break;
            std::cin.clear();
            std::cin.ignore(20,'\n');
        }
        _matrix.assign(_size, {0});
        std::cout << "Enter matrix values:" << std::endl;
        std::for_each(_matrix.begin(), _matrix.end(), [this](std::vector<int32_t> &m_strings)
        {
           m_strings.assign(_size,0);
           std::for_each(m_strings.begin(), m_strings.end(), [] (int32_t &value) {std::cin >> value;});
           std::cout << std::endl;
        });
    }
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
    int32_t _determinant = 0;
    int32_t Determinant(std::vector<std::vector<int32_t>> matrix, size_t size)
    {
        if (size == 1)
            return matrix[0][0];
        if (size == 2)
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        if (size == 3)
        {
            int32_t str_counter = 0;
            std::for_each(_matrix.begin(), _matrix.end(), [this, &str_counter, &size, &matrix](std::vector<int32_t> &m_string)
            {
                _determinant = _determinant + (str_counter % 2 == 0 ? 1 : -1) * m_string[0] * Determinant(Minor(matrix, str_counter), size - 1);
                str_counter++;
            });
            return _determinant;
        }
    }
    std::vector<std::vector<int32_t>> Minor(std::vector<std::vector<int32_t>> matrix, int32_t const &str_counter) const
    {
        std::vector<std::vector<int32_t>> minor(matrix);
        minor.erase(minor.begin() + str_counter);
        std::for_each(minor.begin(), minor.end(), [](std::vector<int32_t> &m_string){m_string.erase(m_string.begin());});
        return minor;
    }
};
