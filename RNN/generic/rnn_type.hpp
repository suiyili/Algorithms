#ifndef RNN_TYPE_HPP
#define RNN_TYPE_HPP

#include <Eigen/Core>

namespace rnn::generic {
using real = double;

template<std::size_t row_dim_t_, std::size_t col_dim_t_>
using rnn_matrix = Eigen::Matrix<real, row_dim_t_, col_dim_t_>;

template<std::size_t dim_t_>
using rnn_square_matrix = rnn_matrix<dim_t_, dim_t_>;

template<std::size_t dim_t_>
using rnn_vector = Eigen::Vector<real, dim_t_>;

#ifdef USE_FLOAT
typedef float real;
typedef Eigen::MatrixXf MatD;
typedef Eigen::VectorXf VecD;
#else
typedef Eigen::MatrixXd MatD;
typedef Eigen::VectorXd VecD;
#endif

typedef Eigen::MatrixXi MatI;
typedef Eigen::VectorXi VecI;
#define REAL_MAX std::numeric_limits<real>::max()

} // namespace rnn

#endif