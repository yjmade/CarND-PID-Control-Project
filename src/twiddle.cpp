//
//  twiddle.cpp
//  PID
//
//  Created by Yang Jian on 03/08/2017.
//
//

#include "twiddle.hpp"
#include <iostream>

Twiddle::Twiddle(double params[3], double initial_diff[3], double upscale, double downscale){
//  params_count_=params_count_;
  params_=params;
  diff_=initial_diff;

  upscale_=upscale;
  downscale_=downscale;

//  best_error_=99999999999999;
  iter_count=0;
}

Twiddle::~Twiddle(){
}


void Twiddle::update(double total_error){
  iter_count++;
  std::cout<<"Iter: "<<iter_count<<" Error: "<<total_error<<" Best Error: "<<best_error_<<"\n";
  if (iter_count<3)return;
  if(!initialized_){
    initialized_=true;
    best_error_=total_error;
    params_[updating_param_index_]+=diff_[updating_param_index_];
    return;
  }
  if(total_error<best_error_){
    best_error_=total_error;
    diff_[updating_param_index_]*=upscale_;
    inc_updating_param_index();
    params_[updating_param_index_]+=diff_[updating_param_index_];
    is_up_=true;
  }else{
    if(is_up_){
      params_[updating_param_index_]-=2*diff_[updating_param_index_];
      is_up_=false;
    }else{
      params_[updating_param_index_]+=diff_[updating_param_index_];
      diff_[updating_param_index_]*=downscale_;
      is_up_=true;
      inc_updating_param_index();
      params_[updating_param_index_]+=diff_[updating_param_index_];
    }
  }
}


void Twiddle::inc_updating_param_index(){
  updating_param_index_++;
  if(updating_param_index_>=PARAMS_COUNT){
    updating_param_index_=0;
  }
}
