#ifndef RCPP_ARRAY_H_
#define RCPP_ARRAY_H_

#include <RcppCommon.h>
#include <array>

namespace Rcpp {
  namespace traits {

    // Partial specialisations to allow as<array<T,D>>(...) and the reverse
    template <typename T, std::size_t D> class Exporter<std::array<T,D>>;

    template <typename T, std::size_t D> SEXP wrap(const std::array<T,D>&);

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
        if (vec.size() != D) Rcpp::stop("Array does not have the expected number of elements");
      }
      ATD get() {
        ATD x;
        std::copy(vec.begin(), vec.end(), x.begin());
        return x;
      }
    };

    template <typename T, std::size_t D> SEXP wrap(const std::array<T,D>& object) {
      const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
      return Vector<RTYPE>(object.begin(), object.end());
    }
  }
}

#endif
