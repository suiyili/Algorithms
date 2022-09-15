
#include "generic/rnn_type.hpp"

using namespace rnn::generic;

namespace rnn::core {

template<std::size_t hidden_dim_t_, std::size_t cat_dim_t_>
class category_vec final {
public:
  explicit category_vec();
  rnn_vector<cat_dim_t_> predict(const rnn_vector<hidden_dim_t_>& input);
  void set_learning(real rate);
  rnn_vector<hidden_dim_t_> train(const rnn_vector<cat_dim_t_>& estimated,
                                  std::size_t sample);

private:
  rnn_matrix<cat_dim_t_, hidden_dim_t_> w_;
  rnn_vector<cat_dim_t_> b_;
  rnn_vector<hidden_dim_t_> input_;
  real learning_rate_ = 1.0f;
};
}
