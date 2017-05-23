#ifndef FISTA_FLAT_H
#define FISTA_FLAT_H

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
//
// Project Specific Headers
#include "spams_eigen_glue.h"

/*! \file
 * \brief Wrapper over Spams fistaFlat function.
 *
 */

namespace internal {

template < typename T >
/*!
 * \brief Performed _fistaFlat on Spams objects, returning parameters useful for the FOS algorithim.
 *
 * \param Y
 *
 * A n x 1 vector
 * \param X
 *
 * An n x m desgin matrix
 *
 * \param Omega_0
 *
 * An n x 1 vector of initial guesses ( probably )
 *
 * \param lambda_1
 *
 * Regularization parameter
 *
 * \return Omega, a 1 x n matrix
 */
inline Matrix<T>* FistaFlat( Matrix<T>* Y, Matrix<T>* X, Matrix<T>* Omega_0, const T lambda_1 ) {

    uint num_cols = Omega_0->n();
    uint num_rows = Omega_0->m();

    //Initialize alpha
    auto W = new Matrix<T> ( num_rows, num_cols );
    W->setZeros();

    //Initialize groups
    auto groups = new Vector<int>( num_rows );
    groups->setZeros();

    //Initialize num_threads
    int num_threads = omp_get_max_threads();

    auto inner_weights = (Vector< T > *) 0;

    char regul[] = "l1";
    char loss[] = "square";
    char log_name[] = "";

    //Return value is optimization info which we do not need
    //We are interested in 'W' which is implicitly modified
    auto optim_info = _fistaFlat(Y, //X
                                 X, //D
                                 Omega_0, //alpha0
                                 W, // alpha
                                 groups, // groups
                                 num_threads, // num_threads
                                 1, // mat_it
                                 static_cast<T>( 0.1 ), //L0
                                 false, //fixed_step
                                 static_cast<T>( 1.5 ), // gamma
                                 lambda_1, //lambda_
                                 static_cast<T>( 1.0 ), //delta
                                 static_cast<T>( 0.0 ), //lambda2
                                 static_cast<T>( 0.0 ), //lambda3
                                 static_cast<T>( 1.0 ), //a
                                 static_cast<T>( 0.0 ), //b
                                 static_cast<T>( 1.0 ), //c
                                 static_cast<T>( 0.000001 ), //tol
                                 100, //it0
                                 1000, //max_iter_backtracking
                                 false, //compute_gram
                                 false, //lin_admm
                                 false, //admm
                                 false, //intercept
                                 false, //resetflow
                                 regul, //name_regul
                                 loss, //name_loss
                                 false, //verbose
                                 false, //pos
                                 false, //clever
                                 false, //log
                                 true, //ista
                                 false, //subgrad
                                 log_name, //logName
                                 false, //is_inner_weights
                                 inner_weights, //inner_weights
                                 1, //size_group
                                 true, //sqrt_step
                                 false, //transpose
                                 0 //linesearch_mode
                                );

    delete optim_info;
    delete groups;
    delete inner_weights;

    return W;
}

}

template < typename T >
/*!
 * \brief Perform fistaFlat on Eigen objects, returning parameters useful for the FOS algorithim.
 *
 * \param Y
 *
 * A n x 1 vector
 * \param X
 *
 * An n x m desgin matrix
 *
 * \param Omega_0
 *
 * An n x 1 vector of initial guesses
 *
 * \param lambda_1
 *
 * Regularization parameter
 *
 * \return Omega, a 1 x n matrix
 */
inline Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic> FistaFlat(
    const Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic>& Y,
    const Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic>& X,
    const Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic>& Omega_0,
    const T lambda_1 ) {


    auto spams_Y = Eigen2SpamsMat<T>( Y );
    auto spams_X = Eigen2SpamsMat<T>( X );
    auto spams_omega =  Eigen2SpamsMat<T>( Omega_0 );

    auto spams_ret_val = internal::FistaFlat< T >( spams_Y, spams_X, spams_omega, lambda_1 );

    free ( spams_Y->rawX() );
    delete spams_Y;

    free ( spams_X->rawX() );
    delete spams_X;

    free ( spams_omega->rawX() );
    delete spams_omega;

    auto ret_val = Spams2EigenMat<T>( spams_ret_val );

    delete spams_ret_val;

    return ret_val.transpose();
}

#endif // FISTA_FLAT_H
