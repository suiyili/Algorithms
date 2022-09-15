
#include <list>
#include <array>
#include "core/gru_cell.hpp"
#include "core/gru_transition.hpp"
#include "core/category_vec.hpp"

using namespace rnn::core;

namespace rnn {

template<std::size_t word_capacity_t_, std::size_t hidden_dim_t_, std::size_t cat_dim_t_>
class category_net final{
public:
  explicit category_net(real learning_rate = 1.0f);
  void train(const std::vector<size_t>& input, size_t label);
  size_t predict(const std::vector<size_t>& input);
private:
  rnn_vector<cat_dim_t_> estimate(const std::vector<size_t>& input);
  typename gru_state<hidden_dim_t_>::gru_vector const init_h_;
  std::array<gru_cell<hidden_dim_t_>, word_capacity_t_> words_;
  std::list<gru_transition<hidden_dim_t_>> series_;
  typename decltype(series_)::iterator last_;
  category_vec<hidden_dim_t_, cat_dim_t_> output_;
};

}  // namespace rnn
