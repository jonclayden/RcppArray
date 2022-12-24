#ifndef ARRAY_H_
#define ARRAY_H_

#include <RcppCommon.h>
#include <array>

namespace Rcpp {
  namespace traits {

    // Partial specialisation to allow as<array<T,D>>(...)
    template <typename T, std::size_t D> class Exporter<std::array<T,D>>;

  }
}

#include <Rcpp.h>

namespace Rcpp {
  namespace traits {

    template <typename T, std::size_t D> class Exporter<std::array<T,D>> {
      typedef typename std::array<T,D> ATD;

      // Convert the type to a valid rtype.
      const static int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
      Rcpp::Vector<RTYPE> vec;

    public:
      Exporter(SEXP x): vec(x) {
        if (TYPEOF(x) != RTYPE) Rcpp::stop("Wrong R type for array");
      }
      ATD get() {
        ATD x;                  // resize step neeed? or implicit because of D?
        if (vec.size() != D) Rcpp::stop("Array does not have the expected number of elements");
        for (size_t i=0; i<D; i++) x[i] = vec[i];
        return x;
      }
    };
  }
}

#endif
