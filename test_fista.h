#ifndef TEST_FISTA_H
#define TEST_FISTA_H

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
