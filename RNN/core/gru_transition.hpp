#ifndef RNN_CORE_GRU_TRANSITION_HPP
#define RNN_CORE_GRU_TRANSITION_HPP

#include "core/gru_transition.h"

namespace rnn::core {

template<std::size_t hidden_dim_t_>
inline void gru_transition<hidden_dim_t_>::forward(const rnn_vector<hidden_dim_t_> &prev) {
  output_ = cell_->forward(prev);
}

template<std::size_t hidden_dim_t_>
inline const rnn_vector<hidden_dim_t_> &gru_transition<hidden_dim_t_>::get_output() const {
  return output_.h_;
}

template<std::size_t hidden_dim_t_>
inline rnn_vector<hidden_dim_t_> gru_transition<hidden_dim_t_>::backward(const rnn_vector<hidden_dim_t_> &prev) {
  return cell_->backward(prev, output_);
}

template<std::size_t hidden_dim_t_>
inline void gru_transition<hidden_dim_t_>::add_bias(const rnn_vector<hidden_dim_t_> &bias) {
  output_.delh_ += bias;
}

template<std::size_t hidden_dim_t_>
inline void gru_transition<hidden_dim_t_>::set_cell(gru_cell<hidden_dim_t_> &cell) {
  cell_ = &cell;
}

}

#endif //RNN_CORE_GRU_TRANSITION_HPP
