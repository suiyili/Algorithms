#include "core/gru_cell.hpp"

namespace rnn::core {

template<std::size_t hidden_dim_t_>
class gru_transition final {
public:
  gru_transition() noexcept = default;
  void forward(const rnn_vector<hidden_dim_t_> &prev);
  const rnn_vector<hidden_dim_t_> &get_output() const;
  rnn_vector<hidden_dim_t_> backward(const rnn_vector<hidden_dim_t_> &prev);
  void set_cell(gru_cell <hidden_dim_t_> &cell);
  void add_bias(const rnn_vector<hidden_dim_t_> &bias);
private:
  gru_cell <hidden_dim_t_> *cell_ = nullptr;
  gru_state <hidden_dim_t_> output_;
};

template<std::size_t hidden_dim_t_>
gru_transition(gru_cell <hidden_dim_t_> &cell) -> gru_transition<hidden_dim_t_>;

}
