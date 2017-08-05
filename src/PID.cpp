#include "PID.h"
#include <iostream>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double kp, double ki, double kd) {
  cout<<"INit"<<kp<<" "<<ki<<" "<<kd<<"\n";
  Kp=kp;
  Ki=ki;
  Kd=kd;
  prev_cte=0.;
  i_error=0.;
}

void PID::UpdateError(double cte) {
//  cout<<Kp<<"\n";
//  cout<<Ki<<"\n";
//  cout<<Kd<<"\n";
  p_error=cte;
  d_error=cte-prev_cte;
  prev_cte=cte;
  i_error+=cte;
}

double PID::TotalError() {
  double total = -Kp * p_error - Ki* i_error - Kd * d_error;
  if (total > 1.)
    total=1;
  if(total<-1)
    total=-1;
  return total;
}

//0.0871649
//0.000765761
//1.09
