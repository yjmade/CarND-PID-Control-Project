//
//  twiddle.hpp
//  PID
//
//  Created by Yang Jian on 03/08/2017.
//
//

#ifndef twiddle_hpp
#define twiddle_hpp

#define PARAMS_COUNT 3

#include <stdio.h>
class Twiddle{
public:
//  int params_count_;
  int iter_count;
  double best_error_;
  double* params_;
  double* diff_;
  double upscale_;
  double downscale_;
  Twiddle(double params[PARAMS_COUNT], double initial_diff[PARAMS_COUNT], double upscale, double downscale);
  virtual ~Twiddle();

  void update(double total_error);

  int updating_param_index_=0;
  bool initialized_=false;
  void inc_updating_param_index();
  bool is_up_=true;
};
#endif /* twiddle_hpp */
