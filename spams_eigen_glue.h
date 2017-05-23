#ifndef SPAMS_EIGEN_GLUE_H
#define SPAMS_EIGEN_GLUE_H

/* SPAMS-Eigen Glue (SEG) v. 1.0
 * Copyright (C) 2017 Benjamin J Phillips
 *
 * This file is part of SEG.
 *
 * SEG is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SEG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SEG.  If not, see <http://www.gnu.org/licenses/>.
 */

// C System-Headers
//
// C++ System headers
//
// Eigen Headers
#include <eigen3/Eigen/Dense>
// Boost Headers
//
// SPAMS Headers
#include "linalg.h" // AbstractMatrix and Matrix
#include "spams.h"
// Project Specific Headers
//


/*! \file
 * \brief Functions that provide an interface between Eigen and Spams linear algebra libraries.
 *
 */

template < typename T, uint m, uint n >
/*!
 * \brief Convert a const- Spams Matrix to an Eigen::Matrix
 *
 * \param spams_mat
 *
 * Spams Matrix pointer to be translated.
 *
 * \return A new Eigen::Matrix with dimensions determined by the Spams Matrix.
 */
inline Eigen::Matrix< T, m, n > Spams2EigenMat ( const Matrix<T>* spams_mat ) {

    auto M = Eigen::Map< Eigen::Matrix< T, n, m, Eigen::ColMajor> >( spams_mat->rawX() );
    return M;
}

template < typename T, uint m, uint n >
/*!
 * \brief Convert a Spams Matrix to an Eigen::Matrix whose rows and cols are known at compile time
 *
 * \param spams_mat
 *
 * Spams Matrix pointer to be translated.
 *
 * \return A new Eigen::Matrix with dimensions determined by the Spams Matrix.
 */
inline Eigen::Matrix< T, m, n > Spams2EigenMat ( Matrix<T>* spams_mat ) {

    auto M = Eigen::Map< Eigen::Matrix< T, n, m, Eigen::ColMajor> >( spams_mat->rawX() );
    return M;
}

template < typename T >
/*!
 * \brief Convert a Spams Matrix to an Eigen::Matrix whose rows and cols are assigned at run time
 *
 * \param spams_mat
 *
 * Spams Matrix pointer to be translated.
 *
 * \return A new Eigen::Matrix with dimensions determined by the Spams Matrix.
 */
inline Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic > Spams2EigenMat ( Matrix<T>* spams_mat ) {

    uint num_cols = spams_mat->n();
    uint num_rows = spams_mat->m();

    return Eigen::Map< Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> >( spams_mat->rawX(), num_cols, num_rows );

}

template < typename T, uint m, uint n >
/*!
 * \brief Get a spams Matrix from an Eigen::Matrix whose dimensions are know at compile time.
 *
 * \param eigen_mat
 *
 * The Eigen::Matrix to be copied.
 *
 * \return A new Spams Matrix ( in pointer form ).
 */
inline Matrix<T>* Eigen2SpamsMat ( const Eigen::Matrix< T, n, m >& eigen_mat ) {

    // Determine number of elements in eigen_mat
    auto eigen_mat_size = eigen_mat.cols() * eigen_mat.rows();
    // Get a non-const copy of data in eigen_mat
    // Spams matrices require non-const data in constructors
    T* non_const_mat_data = new T[ eigen_mat_size ];

    auto mat_data = eigen_mat.data();

    std::copy( mat_data, mat_data + eigen_mat_size, non_const_mat_data);

    auto spams_mat = new Matrix<T> ( non_const_mat_data, m, n );

    return spams_mat;
}

template < typename T >
inline Matrix<T>* Eigen2SpamsMat ( const Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic >& eigen_mat ) {

    uint m = eigen_mat.rows();
    uint n = eigen_mat.cols();

    T* non_const_data = (T*)malloc( n*m*sizeof( T ) );
    memcpy( non_const_data, eigen_mat.data(), n*m*sizeof( T ) );

    auto spams_mat = new Matrix<T> ( non_const_data, m, n );

    return spams_mat;
}

template < typename T, uint m, uint n >
inline AbstractMatrixB<T> Eigen2SpamsAbstractMatB ( const Eigen::Matrix< T, n, m >& eigen_mat ) {
    return AbstractMatrixB<T>( eigen_mat.data(), m, n );
}

/*!
 * \brief Translate a std::string into a pointer to a char array
 *
 * Used with Spams 'print' functions.
 *
 * \param str
 *
 * String to be transformed
 *
 * \return char* populated with data in str and null terminator,
 * Note that the char* will need to be deleted later
 */
inline char* str_to_c_ptr( std::string& str ) {

    char * writable = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), writable);
    writable[str.size()] = '\0'; // don't forget the terminating 0

    return writable;
}

#endif // SPAMS_EIGEN_GLUE_H
