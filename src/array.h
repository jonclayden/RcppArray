#ifndef ARRAY_H_
#define ARRAY_H_

#include <RcppCommon.h>
#include <array>

namespace Rcpp {
namespace traits {

// Partial specialisation to allow as<array<T,D>>(...)
template <typename ElementType>
class Exporter<std::array<ElementType,3>>
{
private:
    std::array<ElementType,3> value;

public:
    Exporter (SEXP x)
    {
        std::vector<ElementType> vec = as<std::vector<ElementType>>(x);
        if (vec.size() != 3)
            throw Rcpp::exception("Array does not have the expected number of elements");
        for (int i=0; i<3; i++)
            value[i] = vec[i];
    }
    
    std::array<ElementType,3> get () { return value; }
};

} // traits namespace
} // Rcpp namespace

#include <Rcpp.h>

#endif
