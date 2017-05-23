#ifndef TEST_FISTA_H
#define TEST_FISTA_H

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
#include <cmath>
// Eigen Headers
#include <eigen3/Eigen/Dense>
// Boost Headers
//
// SPAMS Headers
//
// Armadillo Headers
//
// Project Specific Headers
#include "spams_eigen_glue.h"

void TestFistaFlat( uint num_rows, uint num_cols ) {

    Eigen::MatrixXd X = Eigen::MatrixXd::Random( num_rows, num_cols );
    Eigen::VectorXd Y = X.col(0);

    Eigen::VectorXd W_0 = Eigen::VectorXd::Zero( num_rows );
//    W_0.setZero();

    double lambda = 1.0;

    Eigen::MatrixXd spams_retval =  FistaFlat< double >( Y, X, W_0, 0.5*lambda );

    std::cout << "fistaFlat result:\n" << spams_retval.squaredNorm() << std::endl;
}

void RunFistaTests() {

    for ( uint k = 200; k <= 2000; k+= 200 ) {

        std::cout << "Testing fistaFlat for a " \
                  << k \
                  << "x" \
                  << k \
                  << "Matrix" \
                  << std::endl;

        TestFistaFlat( k, k );
    }
}

#endif // TEST_FISTA_H
