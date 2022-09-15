#include "generic/rnn_type.hpp"

using namespace rnn::generic;

namespace rnn::core {

template<std::size_t hidden_dim_t_>
class gru_state final {
public:
  using gru_vector = rnn_vector<hidden_dim_t_>;
  gru_state() noexcept;
  gru_state(const gru_state& other) noexcept;
  gru_state(gru_state&& other) noexcept ;

  gru_state& operator= (const gru_state& other) noexcept;
  gru_state& operator=(gru_state&& other) noexcept;

  gru_vector h_, u_, r_, z_, rh_, delh_;
};


}
