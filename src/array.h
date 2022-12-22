#ifndef ARRAY_H_
#define ARRAY_H_

#include <RcppCommon.h>
#include <array>

namespace Rcpp {
namespace traits {

// Partial specialisation to allow as<array<T,D>>(...)
template <typename ElementType, int Dimensionality>
class Exporter<std::array<ElementType,Dimensionality>>
{
private:
    SEXP value;

public:
    Exporter (SEXP x) : value(x) {}
    
    std::array<ElementType,Dimensionality> get ()
    {
        std::vector<ElementType> vec = as<std::vector<ElementType>>(value);
        if (vec.size() != Dimensionality)
            throw Rcpp::exception("Array does not have the expected number of elements");
        
        std::array<ElementType,Dimensionality> result;
        for (int i=0; i<Dimensionality; i++)
            result[i] = vec[i];
        return result;
    }
};

} // traits namespace
} // Rcpp namespace

#include <Rcpp.h>

#endif
