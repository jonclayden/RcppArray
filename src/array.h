#ifndef ARRAY_H_
#define ARRAY_H_

#include <RcppCommon.h>
#include <array>

namespace Rcpp {
namespace traits {

// Partial specialisation to allow as<array<T,D>>(...)
template <typename ElementType, size_t Dimensionality>
class Exporter<std::array<ElementType,Dimensionality>>
{
private:
    std::array<ElementType,Dimensionality> value;

public:
    Exporter (SEXP x)
    {
        std::vector<ElementType> vec = as<std::vector<ElementType>>(x);
        if (vec.size() != Dimensionality)
            throw Rcpp::exception("Array does not have the expected number of elements");
        for (int i=0; i<Dimensionality; i++)
            value[i] = vec[i];
    }
    
    std::array<ElementType,Dimensionality> get () { return value; }
};

} // traits namespace
} // Rcpp namespace

#include <Rcpp.h>

#endif
