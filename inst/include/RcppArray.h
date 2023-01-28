#ifndef RCPP_ARRAY_H_
#define RCPP_ARRAY_H_

#include <RcppCommon.h>
#include <array>

#if !defined(HAVE_SPAN) && __cplusplus >= 202002L && defined(__cpp_lib_span)
#define HAVE_SPAN
#endif

#ifdef HAVE_SPAN
#include <span>
#endif

namespace Rcpp {
  namespace traits {

    // Partial specialisations to allow as<array<T,D>>(...) and the reverse
    template <typename T, std::size_t D> class Exporter<std::array<T,D>>;

    template <typename T, std::size_t D> SEXP wrap(const std::array<T,D>&);

#ifdef HAVE_SPAN
    
    // Ditto for std::span, which is from C++20
    template <typename T, std::size_t D> class Exporter<std::span<T,D>>;
    
    template <typename T, std::size_t D> SEXP wrap(const std::span<T,D>&);
    
#endif
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
    
#ifdef HAVE_SPAN
    
    template <typename T, std::size_t D> class Exporter<std::span<T,D>> {
      typedef typename std::span<T,D> STD;
    
      const static int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
      Rcpp::Vector<RTYPE> vec;
    
    public:
      // std::span is a view, so does type conversion make sense semantically?
      // Does as<span<T>>(...) even make sense?
      Exporter(SEXP x): vec(x) {
        if (D != std::dynamic_extent && vec.size() != D) Rcpp::stop("Span does not have the expected number of elements");
      }
      STD get() {
        // Initialisation of a sized span (D neither 0 nor dynamic) isn't allowed without argument
        return STD(vec.begin(), vec.end());
      }
    };
    
    template <typename T, std::size_t D> SEXP wrap(const std::span<T,D>& object) {
      const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
      return Vector<RTYPE>(object.begin(), object.end());
    }
    
#endif
  }
}

#endif
