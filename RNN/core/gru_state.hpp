#ifndef RNN_CORE_GRU_STATE_HPP
#define RNN_CORE_GRU_STATE_HPP

#include "gru_state.h"

namespace rnn::core {

template<std::size_t hidden_dim_t_>
inline gru_state<hidden_dim_t_>::gru_state() noexcept
:h_(decltype(h_)::Zero()), u_(decltype(u_)::Zero()),
r_(decltype(r_)::Zero()), z_(decltype(z_)::Zero()),
rh_(decltype(rh_)::Zero()), delh_(decltype(delh_)::Zero()){
}

template<std::size_t hidden_dim_t_>
inline gru_state<hidden_dim_t_>::gru_state(const gru_state &other) noexcept
: h_(other.h_), u_(other.u_), r_(other.r_), z_(other.z_),
rh_(other.rh_), delh_(other.delh_) {
}

template<std::size_t hidden_dim_t_>
inline gru_state<hidden_dim_t_>::gru_state(gru_state &&other) noexcept
: h_(std::move(other.h_)),
u_(std::move(other.u_)),
r_(std::move(other.r_)),
z_(std::move(other.z_)),
rh_(std::move(other.rh_)),
delh_(std::move(other.delh_)) {
}

template<std::size_t hidden_dim_t_>
inline gru_state<hidden_dim_t_> &gru_state<hidden_dim_t_>::operator=(const gru_state &other) noexcept {
  if(this != &other) {
    h_ = other.h_;
    u_ = other.u_;
    r_ = other.r_;
    z_ = other.z_;
    rh_ = other.rh_;
    delh_ = other.delh_;
  }
  return *this;
}

template<std::size_t hidden_dim_t_>
gru_state<hidden_dim_t_> &gru_state<hidden_dim_t_>::operator=(gru_state &&other) noexcept {
  if(this != &other) {
    h_ = std::move(other.h_);
    u_ = std::move(other.u_);
    r_ = std::move(other.r_);
    z_ = std::move(other.z_);
    rh_ = std::move(other.rh_);
    delh_ = std::move(other.delh_);
  }
  return *this;
}

}

#endif //RNN_CORE_GRU_STATE_HPP
