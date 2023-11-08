This file documents the significant user-visible changes in each release of the `RcppArray` R package.

## Version 0.3.0

- Support for `std::tuple` has been added, with help from Andrew Johnson (cf. [`Rcpp` issue #1278](https://github.com/RcppCore/Rcpp/issues/1278)). Since this C++ type can hold a mixture of basic types, it converts to and from an R list.

## Version 0.2.0

- First public release.
