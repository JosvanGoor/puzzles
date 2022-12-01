#ifndef SIEVE_H
#define SIEVE_H

#include <array>
#include <concepts>
#include <cstdint>

template <std::uint64_t Max>
class Sieve
{
    std::array<bool, Max> _primes{};

    public:
        Sieve()
        {
            for (bool& primeness : _primes)
                primeness = true;

            for (std::size_t idx = 3; idx < static_cast<std::size_t>(std::sqrt(Max)); idx += 2)
            {
                if (!_primes[index(idx)])
                    continue;

                for (std::size_t value = (2 * idx); value < Max; value += idx)
                {
                    if (value % 2 == 0)
                        continue;
                    _primes[index(value)] = false;
                }
            }
        }

        bool is_prime(std::uint64_t number) const noexcept
        {
            if (number == 2)
                return true;
            
            if ((number == 0) || (number >= Max) || (number % 2 == 0))
                return false;

            return _primes[index(number)];
        }

        std::uint64_t size() const noexcept
        {
            return Max;
        }

    private:
        std::size_t index(std::int64_t number) const noexcept
        {
            return (number - 1) / 2;
        }
};

#endif