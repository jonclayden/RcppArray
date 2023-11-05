#ifndef RCPP_ARRAY_H_
#define RCPP_ARRAY_H_

#include <RcppCommon.h>
#include <array>
#include <tuple>

#if !defined(HAVE_SPAN) && __cplusplus >= 202002L && defined(__cpp_lib_span)
#define HAVE_SPAN
#endif

#ifdef HAVE_SPAN
#include <span>
#endif

namespace Rcpp {
  namespace traits {

    // Partial specialisation to allow as<array<T,D>>(...)
    template <typename T, std::size_t D> class Exporter<std::array<T,D>>;
    
    // Ditto for std::tuple
    template <typename... T> class Exporter<std::tuple<T...>>;
  }
  
  // Partial specialisations for wrap()
  template <typename T, std::size_t D> SEXP wrap(const std::array<T,D>&);
  template <typename... T> SEXP wrap(const std::tuple<T...>&);

#ifdef HAVE_SPAN
  // Version for std::span, which is from C++20
  namespace traits {
    template <typename T, std::size_t D> class Exporter<std::span<T,D>>;
  }
  
  template <typename T, std::size_t D> SEXP wrap(const std::span<T,D>&);
#endif

}

#include <Rcpp.h>

namespace RcppArray {
  namespace internal {
    // Helper class to copy between a std::tuple and an R list. Each element
    // has its own specialisation, which contains a child object that handles
    // the previous element, down to element zero which terminates the chain
    template <std::size_t N, typename... T> struct Copier {
      typedef typename std::tuple<T...> TT;
      
    private:
      TT& tuple;
      Rcpp::List& list;
      Copier<N-1, T...> child;
      
    public:
      Copier(TT& t, Rcpp::List& l): tuple(t), list(l), child(t,l) {}
      
      void list2tuple() const {
        std::get<N-1>(tuple) = Rcpp::as<typename std::tuple_element<N-1,TT>::type>(list[N-1]);
        child.list2tuple();
      }
      
      void tuple2list() const {
        list[N-1] = std::get<N-1>(tuple);
        child.tuple2list();
      }
    };
    
    // Zeroth-level copier does nothing
    template <typename... T> struct Copier<0, T...> {
      typedef typename std::tuple<T...> TT;
      
      Copier(TT& t, Rcpp::List& l) {}
      
      void list2tuple() const {}
      void tuple2list() const {}
    };
  }
}

namespace Rcpp {
  namespace traits {

    template <typename T, std::size_t D> class Exporter<std::array<T,D>> {
      typedef typename std::array<T,D> ATD;

      // Convert the type to a valid R type
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
    
    template <typename... T> class Exporter<std::tuple<T...>> {
      typedef typename std::tuple<T...> TT;
      
      // Tuples are (in general) a mixed type, analogous to an R list
      Rcpp::List list;
      
    public:
      Exporter(SEXP x): list(x) {
        if (list.size() != sizeof...(T)) Rcpp::stop("Tuple does not have the expected number of elements");
      }
      TT get() {
        TT x;
        RcppArray::internal::Copier<sizeof...(T), T...> copier(x, list);
        copier.list2tuple();
        return x;
      }
    };
    
#ifdef HAVE_SPAN
    template <typename T, std::size_t D> class Exporter<std::span<T,D>> {
      typedef typename std::span<T,D> STD;
    
      const static int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
      Rcpp::Vector<RTYPE> vec;
    
    public:
      Exporter(SEXP x): vec(x) {
        if (D != std::dynamic_extent && vec.size() != D) Rcpp::stop("Span does not have the expected number of elements");
      }
      STD get() {
        // NB: Will not compile if T does not match the underlying type of vec,
        // i.e., where T is not a type that R uses directly (int, double, ...).
        // This is also a view into an object owned by the Exporter, which may
        // be invalidated, so use with care
        return STD(vec.begin(), vec.end());
      }
    };
#endif
  }   // traits namespace
  
  template <typename T, std::size_t D> SEXP wrap(const std::array<T,D>& object) {
    const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
    return Vector<RTYPE>(object.begin(), object.end());
  }
  
  template <typename... T> SEXP wrap(const std::tuple<T...>& object) {
    Rcpp::List list(sizeof...(T));
    const RcppArray::internal::Copier<sizeof...(T), T...> copier(const_cast<std::tuple<T...>&>(object), list);
    copier.tuple2list();
    return list;
  }

#ifdef HAVE_SPAN
  template <typename T, std::size_t D> SEXP wrap(const std::span<T,D>& object) {
    const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
    return Vector<RTYPE>(object.begin(), object.end());
  }
#endif
  
}

#endif
