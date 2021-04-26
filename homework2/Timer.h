#pragma once
#include <iostream>
#include <chrono>

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;
    std::string _name;
    std::chrono::time_point<clock_t> _beg;
    double Elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - _beg).count();
    }
public:
    Timer() : _beg(clock_t::now()){}
    explicit Timer(std::string name) : _name(name), _beg(clock_t::now()) {}
    void Start (std::string name)
    {
        _name = name;
        _beg = clock_t::now();
    }
    void Print() const
    {
        std::cout << _name << ":\t" << Elapsed() * 1000 << " ms" << std::endl;
    }
};
