#ifndef RNN_CORE_CATEGORY_VEC_HPP
#define RNN_CORE_CATEGORY_VEC_HPP

#include "category_vec.h"

namespace rnn::core {

template<std::size_t hidden_dim_t_, std::size_t cat_dim_t_>
inline category_vec<hidden_dim_t_, cat_dim_t_>::category_vec()
    :w_(decltype(w_)::Random()),
     b_(decltype(b_)::Zero()) {
}

template<std::size_t hidden_dim_t_, std::size_t cat_dim_t_>
inline rnn_vector<cat_dim_t_>
category_vec<hidden_dim_t_, cat_dim_t_>::predict(const rnn_vector<hidden_dim_t_> &input) {
  input_ = input;
  decltype(b_) output = w_ * input + b_;

  output.array() -= output.maxCoeff();
  output.array() = output.array().exp();
  return output / output.sum();
}

template<std::size_t hidden_dim_t_, std::size_t cat_dim_t_>
inline void category_vec<hidden_dim_t_, cat_dim_t_>::set_learning(real rate) {
  learning_rate_ = rate;
}

template<std::size_t hidden_dim_t_, std::size_t cat_dim_t_>
inline rnn_vector<hidden_dim_t_>
category_vec<hidden_dim_t_, cat_dim_t_>::train(const rnn_vector<cat_dim_t_> &estimated,
                                                  std::size_t sample) {
  rnn_vector<cat_dim_t_> errors(rnn_vector<cat_dim_t_>::Zero());
  errors[sample] = 1.0;
  errors = estimated - errors;

  auto back_error = w_.transpose() * errors;
  errors *= learning_rate_;
  w_.noalias() -= errors * input_.transpose();
  b_.noalias() -= errors;
  return back_error;
}

}

#endif //RNN_CORE_CATEGORY_VEC_HPP
