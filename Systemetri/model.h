#pragma once
#include "types.h"
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <tuple>

namespace model {

struct Model;
using Reducer = std::function<Model(Model)>;
using OptionalReducer = std::optional<Reducer>;
using TransitionActionMap =
    std::unordered_map<types::Transition, std::function<OptionalReducer()>>;

struct Model {
  Model(const std::chrono::steady_clock::time_point &t, const types::Marking &M,
        const types::TransitionMutation &Dm, const types::TransitionMutation &Dp)
      : data(std::make_shared<shared>(t, M, Dm, Dp)) {}
  struct shared {
    shared(const std::chrono::steady_clock::time_point &t, const types::Marking &M,
           const types::TransitionMutation &Dm, const types::TransitionMutation &Dp)
        : timestamp(t), M(M), Dm(Dm), Dp(Dp) {}
    mutable std::chrono::steady_clock::time_point timestamp;
    mutable types::Marking M;
    const types::TransitionMutation Dm;
    const types::TransitionMutation Dp;
    mutable std::vector<std::tuple<size_t, int64_t, int64_t, types::Transition>> log;
  };
  std::shared_ptr<shared> data;
};

std::pair<Model, types::Transitions> run(Model model);

} // namespace model
