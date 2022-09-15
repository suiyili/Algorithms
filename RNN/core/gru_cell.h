#include <fstream>
#include <Eigen/Core>
#include "gru_state.hpp"

namespace rnn::core {

template<std::size_t hidden_dim_t_>
class gru_cell final {
public:
  using gru_state_t = gru_state<hidden_dim_t_>;
  gru_cell();

  gru_state_t forward(const rnn_vector<hidden_dim_t_> &prev);

  rnn_vector<hidden_dim_t_> backward(const rnn_vector<hidden_dim_t_> &prev, const gru_state_t &cur);

  void set_learning(real rate);

  template<std::size_t dim_t_>
  friend std::ofstream &operator<<(std::ofstream &ofs, const gru_cell<dim_t_> &cell);

  template<std::size_t dim_t_>
  friend std::ifstream &operator>>(std::ifstream &ifs, gru_cell<dim_t_> &cell);

private:
  using gru_matrix = rnn_square_matrix<hidden_dim_t_>;
  static auto logistic(typename gru_state_t::gru_vector const &v) -> std::decay_t<decltype(v)>;
  static auto logistic_prime(typename gru_state_t::gru_vector const &v) -> std::decay_t<decltype(v)>;

  static auto tanh(typename gru_state_t::gru_vector const &v)->std::decay_t<decltype(v)>;
  static auto tanh_prime(typename gru_state_t::gru_vector const &v)-> std::decay_t<decltype(v)>;

  static void save(std::ofstream &ofs, const gru_matrix &m);
  static void save(std::ofstream &ofs, typename gru_state_t::gru_vector const &v);

  static void load(std::ifstream &ifs, gru_matrix &m);
  static void load(std::ifstream &ifs, typename gru_state_t::gru_vector &v);

  gru_matrix wr_, wz_, wu_;
  typename gru_state_t::gru_vector br_, bz_, bu_;
  real learning_rate_ = 1.f;
};

}
