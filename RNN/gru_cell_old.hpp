#ifndef GRU_CELL_OLD_HPP
#define GRU_CELL_OLD_HPP

#include "generic/rnn_type.hpp"
#include "generic/rand.hpp"
#include <fstream>

using namespace rnn::generic;

namespace rnn {
  class gru_cell_old final {
  public:
    gru_cell_old() = default;;

    gru_cell_old(int inputDim, int hiddenDim);

    class State;

    class Grad;

    MatD Wxr, Whr;
    VecD br;
    MatD Wxz, Whz;
    VecD bz;
    MatD Wxu, Whu;
    VecD bu;

    void init(rnn::generic::rand& rnd, real scale = 1.0);

    gru_cell_old::State forward(const VecD& xt, const State& prev);

    void backward(gru_cell_old::State* prev, gru_cell_old::State* cur, gru_cell_old::Grad& grad,
                          const VecD& xt);

    void sgd(const gru_cell_old::Grad& grad, real learningRate);

    void save(std::ofstream& ofs);

    void load(std::ifstream& ifs);
  };

  class gru_cell_old::State {
  public:
    VecD h, u, r, z;
    VecD rh;

    VecD delh, delx; //for backprop

    void clear();
  };

  class gru_cell_old::Grad {
  public:
    Grad()
    {}

    Grad(const gru_cell_old& gru);

    MatD Wxr, Whr;
    VecD br;
    MatD Wxz, Whz;
    VecD bz;
    MatD Wxu, Whu;
    VecD bu;

    void init();

    real norm();

    void operator+=(const gru_cell_old::Grad& grad);
  };
}

#endif