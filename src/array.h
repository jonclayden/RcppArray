#ifndef ARRAY_H_
#define ARRAY_H_

#include <RcppCommon.h>
#include <array>

namespace Rcpp {
namespace traits {

// Forward declaration before including Rcpp.h
template <typename ElementType, int Dimensionality>
class Exporter<std::array<ElementType,Dimensionality>>;

} }

// Needed for Rcpp::Vector
#include <Rcpp.h>

namespace Rcpp {
namespace traits {

// Partial specialisation to allow as<array<T,D>>(...)
template <typename ElementType, int Dimensionality>
class Exporter<std::array<ElementType,Dimensionality>>
{
private:
    const static int RTYPE = r_sexptype_traits<ElementType>::rtype;
    Rcpp::Vector<RTYPE> vec;
    
public:
    Exporter (SEXP x) : vec(x) {}
    
    std::array<ElementType,Dimensionality> get ()
    {
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

#endif
