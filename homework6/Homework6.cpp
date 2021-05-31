#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <vector>

class PCout
{
public:
    static std::mutex pco_mutex;
    std::stringstream sso;
    template <class T>
    PCout &operator << (const T &arg)
    {
        sso << arg;
        return *this;
    }
    ~PCout()
    {
        std::lock_guard pco_lg {PCout::pco_mutex};
        std::cout << sso.rdbuf();
        std::cout.flush();
    }
};

std::mutex PCout::pco_mutex;

void Print_PCout(const size_t num)
{
    PCout() << "thread number " << num << "\n"; 
}

bool IsPrime (uint64_t number)
{
    if (number == 2)
        return true;
    if (number < 2 || number % 2 == 0)
        return false;
    for(uint64_t i = 3; i <= sqrt(number); ++i)
    {
        if(number % i == 0)
            return false;
    }
    return true;
}

uint64_t FindPrime(uint32_t n, uint32_t &counter)
{
    uint64_t current = 0;
    while (counter < n)
    {
        current++;
        if (IsPrime(current))
            counter++;
    }
    return current;
}

uint64_t FindPrimeAsync(uint32_t n)
{
    uint32_t counter = 0;
    std::future<uint64_t> prime_num = std::async(std::launch::async, FindPrime, n, std::ref(counter));
    while (counter * 100 / n < 100)
    {
        std::cout << counter * 100 / n << "%" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return prime_num.get();
}

struct Object
{
    size_t m_id;
    int32_t m_price;
    Object(size_t id, int32_t price) :
        m_id(id), m_price(price){}
};

bool operator < (const Object &lhs,const Object &rhs)
{
    return lhs.m_price < rhs.m_price;
}

std::mutex mutex;
std::priority_queue <Object> house;
const size_t num_objects = 10;
bool fin;

void Put()
{
    for(size_t i = 0; i < num_objects; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        {
            std::lock_guard lg(mutex);
            const std::pair<size_t, int32_t> obj {i + 1, rand() % 50000};
            house.push(Object(obj.first, obj.second));
            std::cout << "(Owner) Put object - " << obj.first << "; price - " << obj.second << std::endl;  
        }
        std::lock_guard lg (mutex);
        fin = true;
    }
}

void Steal()
{
    for(size_t i = 0; i < num_objects; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            {
                std::lock_guard lg(mutex);
                std::cout << "(Theef) Most valuable item stolen - " << house.top().m_id << "; price - "
                          << house.top().m_price << std::endl;
                house.pop();
            }
        }  
    }


int main()
{
    // Ex1
    
    std::vector<std::thread> threads;
    for(size_t i = 0; i < 10; ++i)
        threads.emplace_back(Print_PCout, i);
    for(auto &t : threads)
        t.join();

    // Ex2

    const auto prime_number = FindPrimeAsync(1000000);
    std::cout << "Prime number = "<< prime_number << std::endl;

    // Ex3

    std::thread owner (Put);
    std::thread theef (Steal);
    owner.join();
    theef.join();
    
    return EXIT_SUCCESS;
}
