#ifndef RNN_CORE_GRU_CELL_HPP
#define RNN_CORE_GRU_CELL_HPP

#include "gru_cell.h"

namespace rnn::core {

template<std::size_t hidden_dim_t_>
inline gru_cell<hidden_dim_t_>::gru_cell()
    : wr_(gru_matrix::Random()),
      wz_(gru_matrix::Random()),
      wu_(gru_matrix::Random()),
      br_(gru_state_t::gru_vector::Zero()),
      bz_(gru_state_t::gru_vector::Zero()),
      bu_(gru_state_t::gru_vector::Zero()) {

}

template<std::size_t hidden_dim_t_>
inline gru_state<hidden_dim_t_> gru_cell<hidden_dim_t_>::forward(
    const rnn_vector<hidden_dim_t_> &prev) {

  gru_state<hidden_dim_t_> cur;
  cur.r_ = br_ + wr_ * prev;
  cur.z_ = bz_ + wz_ * prev;

  cur.r_ = logistic(cur.r_);
  cur.z_ = logistic(cur.z_);

  cur.rh_ = cur.r_.array() * prev.array();
  cur.u_ = bu_ + wu_ * cur.rh_;
  cur.u_ = tanh(cur.u_);
  cur.h_ = (1.0 - cur.z_.array()) * cur.u_.array() + cur.z_.array() * prev.array();
  return cur;
}

template<std::size_t hidden_dim_t_>
inline void gru_cell<hidden_dim_t_>::set_learning(real rate) {
  learning_rate_ = rate;
}

template<std::size_t hidden_dim_t_>
inline rnn_vector<hidden_dim_t_> gru_cell<hidden_dim_t_>::backward(const rnn_vector<hidden_dim_t_> &prev,
                                                                   const gru_state_t &cur) {

  rnn_vector<hidden_dim_t_> delz = logistic_prime(cur.z_).array() * cur.delh_.array() * (cur.u_ - prev).array();
  rnn_vector<hidden_dim_t_> delu = tanh_prime(cur.u_).array() * cur.delh_.array() * cur.z_.array();
  rnn_vector<hidden_dim_t_> delrh = wu_.transpose() * delu;
  rnn_vector<hidden_dim_t_> delr = logistic_prime(cur.r_).array() * delrh.array() * prev.array();

  rnn_vector<hidden_dim_t_> del_h = wr_.transpose() * delr + wz_.transpose() * delz;
  del_h.array() += delrh.array() * cur.r_.array() + cur.delh_.array() * (1.0 - cur.z_.array());

  delr *= learning_rate_;
  delz *= learning_rate_;
  delu *= learning_rate_;

  wr_.noalias() -= delr * prev.transpose();
  wz_.noalias() -= delz * prev.transpose();
  wu_.noalias() -= delu * cur.rh_.transpose();

  br_.noalias() -= delr;
  bz_.noalias() -= delz;
  bu_.noalias() -= delu;

  return del_h;
}

template<std::size_t dim_t_>
inline std::ofstream &operator<<(std::ofstream &ofs, const gru_cell<dim_t_> &cell) {
  save(ofs, cell.wr_);
  save(ofs, cell.br_);

  save(ofs, cell.wz_);
  save(ofs, cell.bz_);

  save(ofs, cell.wu_);
  save(ofs, cell.bu_);
  return ofs;
}

template<std::size_t dim_t_>
inline std::ifstream &operator>>(std::ifstream &ifs, gru_cell<dim_t_> &cell) {
  load(ifs, cell.wr_);
  load(ifs, cell.br_);

  load(ifs, cell.wz_);
  load(ifs, cell.bz_);

  load(ifs, cell.wu_);
  load(ifs, cell.bu_);

  return ifs;
}

template<std::size_t hidden_dim_t_>
inline auto gru_cell<hidden_dim_t_>::logistic(typename gru_state_t::gru_vector const &v)
-> std::decay_t<decltype(v)> {
  return v.array().logistic();
}

template<std::size_t hidden_dim_t_>
inline auto gru_cell<hidden_dim_t_>::logistic_prime(typename gru_state_t::gru_vector const &v)
-> std::decay_t<decltype(v)> {
  return v.array() * (1.0 - v.array());
}

template<std::size_t hidden_dim_t_>
inline auto gru_cell<hidden_dim_t_>::tanh(typename gru_state_t::gru_vector const &v)
-> std::decay_t<decltype(v)> {
  return v.array().tanh();
}

template<std::size_t hidden_dim_t_>
inline auto gru_cell<hidden_dim_t_>::tanh_prime(typename gru_state_t::gru_vector const &v)
-> std::decay_t<decltype(v)> {
  return 1.0 - v.array().square();
}
template<std::size_t hidden_dim_t_>
inline void gru_cell<hidden_dim_t_>::save(std::ofstream &ofs,
                                          const gru_cell::gru_matrix &m) {
  real val = 0.0;

  for (int i = 0; i < m.cols(); ++i) {
    for (int j = 0; j < m.rows(); ++j) {
      val = m.coeff(j, i);
      ofs.write((char *) &val, sizeof(real));
    }
  }
}
template<std::size_t hidden_dim_t_>
void gru_cell<hidden_dim_t_>::save(std::ofstream &ofs,
                                   typename gru_cell<hidden_dim_t_>::gru_state_t::gru_vector const &v) {
  real val = 0.0;

  for (int i = 0; i < v.rows(); ++i) {
    val = v.coeff(i, 0);
    ofs.write((char *) &val, sizeof(real));
  }
}

template<std::size_t hidden_dim_t_>
inline void gru_cell<hidden_dim_t_>::load(std::ifstream &ifs, gru_cell::gru_matrix &m) {
  real val = 0.0;

  for (int i = 0; i < m.cols(); ++i) {
    for (int j = 0; j < m.rows(); ++j) {
      ifs.read((char *) &val, sizeof(real));
      m.coeffRef(j, i) = val;
    }
  }
}

template<std::size_t hidden_dim_t_>
inline void gru_cell<hidden_dim_t_>::load(std::ifstream &ifs,
                                          typename gru_cell<hidden_dim_t_>::gru_state_t::gru_vector &v) {
  real val = 0.0;

  for (int i = 0; i < v.rows(); ++i) {
    ifs.read((char *) &val, sizeof(real));
    v.coeffRef(i, 0) = val;
  }
}

}

#endif