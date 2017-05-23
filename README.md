# SPAMS-Eigen3 Interface

This package is designed to provide intercompatiblity between the [SPAMS (SPArse Modeling Software)](http://spams-devel.gforge.inria.fr/)
package and the [Eigen3](http://eigen.tuxfamily.org/) Linear Algebra library.

## Introduction

The SPAMS package, maintained by Julien Mairal, provides a wide array of tools for
solving sparse estimation problems. Although SPAMS is written in C++, it is
designed to be used through one of three available wrappers -- MATLAB, R or Python.
Using SPAMS through any of these three wrappers is a reasonably straight-forward process
as each wrapper is well-documented and reasonably intuitive. However using the
native C++ code base is much more difficult.

The SPAMS package defines its own linear algebra objects, such as Matrices, Vectors
and their Sparse equivalents, which are used by every algorithm defined in the SPAMS package.
Thus one cannot use the functions defined in SPAMS with other Linear Algebra libraries
such as Eigen3, Armadillo, GTML etc.

## Dependencies

### Base

You will need a copy of the SPAMS source-code. There is currently no way to download
just the C++ source code, but it is included with any of the source-wrapper packages.
Any 'precompilied' wrapper packages will not contain the C++ source code.

* [SPAMS](http://spams-devel.gforge.inria.fr/downloads.html)

## History of this package

This package was developed during the construction of FOS,
the Fast and Optimal Selection algorithm for high-dimensional linear regression
as part of the [HDIM](https://github.com/LedererLab/FOS)
package. The original implementation of FOS used the function FistaFlat, as provided
by the SPAMS package.

## License

SPAMS-Eigen3 Glue is licensed under the GPL version 3.

## Author

* **Benjamin J Phillips**
