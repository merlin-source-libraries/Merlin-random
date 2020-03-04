#ifndef MERLIN_RANDOM_HPP
#define MERLIN_RANDOM_HPP

#include <merlin_type_traits.hpp>
#include <random>
#include <chrono>

namespace merl
{
    template <typename Integral>
    Integral randi(Integral min, Integral max)
    {
        static_assert(is_strict_integral<Integral>::value, "Error: The given \"Integral\" template type does not match the std::uniform_int_distribution type requirements.");

        if(min > max)
            std::swap(min, max);

        thread_local std::random_device rd;
        thread_local auto seed = []() -> unsigned int
        {
            if(static_cast<bool>(rd.entropy()))
                return rd();
            else
                return static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        };
        thread_local std::mt19937_64 gen(seed());

        return std::uniform_int_distribution<Integral>(min, max)(gen);
    }

    template <typename Real>
    Real randr(Real min, Real max)
    {
        static_assert(std::is_floating_point<Real>::value, "Error: The given \"Real\" template type does not match the std::uniform_real_distribution type requirements.");

        if(min > max)
            std::swap(min, max);

        thread_local std::random_device rd;
        thread_local auto seed = []() -> unsigned int
        {
            if(static_cast<bool>(rd.entropy()))
                return rd();
            else
                return static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        };
        thread_local std::mt19937_64 gen(seed());

        return std::uniform_real_distribution<Real>(min, max)(gen);
    }
}

#endif