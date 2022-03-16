//
// Created by KK on 2022/3/9.
//

#ifndef ALGORITHM_EXERCISES_RANDOM_DATA_SETS_HPP
#define ALGORITHM_EXERCISES_RANDOM_DATA_SETS_HPP

#include <vector>
#include <chrono>
#include <random>

std::vector<int> random_dataset(int low, int high, int num) {
  auto now = std::chrono::system_clock::now();
  std::default_random_engine e(now.time_since_epoch().count());
  std::uniform_int_distribution<int> u(low, high);
  std::vector<int> res;
  res.reserve(num);
  for (int i = 0; i < num; ++i) {
    res.push_back(u(e));
  }
  return res;
}


#endif //ALGORITHM_EXERCISES_RANDOM_DATA_SETS_HPP
