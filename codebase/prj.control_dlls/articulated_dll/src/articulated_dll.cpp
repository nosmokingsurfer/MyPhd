// UMLinearSpringC.cpp : Defines the exported functions for the DLL application.
//


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "stdafx.h"
#include <math.h>

typedef double*  PDouble;
typedef wchar_t*  WChar;

#include <robot/robot.h>

Robot myRobot(Body::BODY_TYPE::ARTICULATED);

void _cdecl EXT_Initialize( int& status)
{
  // Here we should alloc arrays, create classes and initialize all variables
  // status is the exit code 
  //   status==0 means no errors occured

  // Initial values of parameters
  status = 0;
}

void _cdecl EXT_Terminate( int& status )
{
  // Here we should free all arrays and classes and initialize all variables
  // status is the exit code 
  //   status==0 means no errors occured

  status = 0;
}

void _cdecl EXT_GetModelName(WChar name, int& status)
{
  // name is the model name to return
  // status is the exit code 
  //   status==0 means no errors occured

  wcscpy(name, L"Simple hexapod test" );
  status = 0;
}

void _cdecl EXT_GetNumU(int& num, int& status)
{
  // num is the count of input signals
  // status is the exit code 
  //   status==0 means no errors occured

  num = 1*(6 + 6); // for the mainBody
  num += 6*(3 + 3); //for six legs with 3 d.o.f. in each leg + velocities
  num += 2*(1 + 1); //for two joints with 1 d.o.f. + velocities

  // the total number of input signals is 52

  status = 0;
}

void _cdecl EXT_GetUName( int i, WChar name, int& status)
{
  // i is the index of input signals, the first signal has index 0
  // name is the input signal to return
  // status is the exit code 
  //   status==0 means no errors occured

  status = 0;
  switch( i ) // Names of output variables
  {  
  case 0: wcscpy(name, L"body_x"); break;
  case 1: wcscpy(name, L"body_y"); break;
  case 2: wcscpy(name, L"body_z"); break;
  case 3: wcscpy(name, L"body_yaw"); break;
  case 4: wcscpy(name, L"body_pitch"); break;
  case 5: wcscpy(name, L"body_roll"); break;

  case 6:  wcscpy(name, L"body_vx"); break;
  case 7:  wcscpy(name, L"body_vy"); break;
  case 8:  wcscpy(name, L"body_vz"); break;
  case 9:  wcscpy(name, L"body_yaw_v"); break;
  case 10: wcscpy(name, L"body_pitch_v"); break;
  case 11: wcscpy(name, L"body_roll_v"); break;

  case 12: wcscpy(name, L"FB_FL_alpha"); break;
  case 13: wcscpy(name, L"FB_FL_beta"); break;
  case 14: wcscpy(name, L"FB_FL_gamma"); break;
  case 15: wcscpy(name, L"FB_FL_alpha_v"); break;
  case 16: wcscpy(name, L"FB_FL_beta_v"); break;
  case 17: wcscpy(name, L"FB_FL_gamma_v"); break;

  case 18: wcscpy(name, L"FB_ML_alpha"); break;
  case 19: wcscpy(name, L"FB_ML_beta"); break;
  case 20: wcscpy(name, L"FB_ML_gamma"); break;
  case 21: wcscpy(name, L"FB_ML_alpha_v"); break;
  case 22: wcscpy(name, L"FB_ML_beta_v"); break;
  case 23: wcscpy(name, L"FB_ML_gamma_v"); break;

  case 24: wcscpy(name, L"FB_RL_alpha"); break;
  case 25: wcscpy(name, L"FB_RL_beta"); break;
  case 26: wcscpy(name, L"FB_RL_gamma"); break;
  case 27: wcscpy(name, L"FB_RL_alpha_v"); break;
  case 28: wcscpy(name, L"FB_RL_beta_v"); break;
  case 29: wcscpy(name, L"FB_RL_gamma_v"); break;

  case 30: wcscpy(name, L"FB_FR_alpha"); break;
  case 31: wcscpy(name, L"FB_FR_beta"); break;
  case 32: wcscpy(name, L"FB_FR_gamma"); break;
  case 33: wcscpy(name, L"FB_FR_alpha_v"); break;
  case 34: wcscpy(name, L"FB_FR_beta_v"); break;
  case 35: wcscpy(name, L"FB_FR_gamma_v"); break;
                              
  case 36: wcscpy(name, L"FB_MR_alpha"); break;
  case 37: wcscpy(name, L"FB_MR_beta"); break;
  case 38: wcscpy(name, L"FB_MR_gamma"); break;
  case 39: wcscpy(name, L"FB_MR_alpha_v"); break;
  case 40: wcscpy(name, L"FB_MR_beta_v"); break;
  case 41: wcscpy(name, L"FB_MR_gamma_v"); break;
                              
  case 42: wcscpy(name, L"FB_RR_alpha"); break;
  case 43: wcscpy(name, L"FB_RR_beta"); break;
  case 44: wcscpy(name, L"FB_RR_gamma"); break;
  case 45: wcscpy(name, L"FB_RR_alpha_v"); break;
  case 46: wcscpy(name, L"FB_RR_beta_v"); break;
  case 47: wcscpy(name, L"FB_RR_gamma_v"); break;

  case 48: wcscpy(name, L"FB_j_1_2"); break;
  case 49: wcscpy(name, L"FB_j_1_2_v"); break;

  case 50: wcscpy(name, L"FB_j_2_3"); break;
  case 51: wcscpy(name, L"FB_j_2_3_v"); break;

  default: status = 1;
  }
}

void _cdecl EXT_GetNumY(int &num, int& status)
{
  // num is the count of output signals
  // status is the exit code 
  //   status==0 means no errors occured

  num = 6*3; // control torques for leg's joints
  num += 6*3; // target angles for leg joints
  num += 2; // control torques for body joints
  num += 2; // desired angles for body joints
  num += 3; // calculated COM of the Robot

  //total number of output signals is 43

  status = 0;
}

void _cdecl EXT_GetYName(int i, WChar name, int& status)
{
  // i is the index of parameter, the first parameter has index 0
  // name is the output signal name to return
  // status is the exit code 
  //   status==0 means no errors occured

  status = 0;
  switch( i ) // Names of output variables
  {  
    //control torques
  case 0: wcscpy(name, L"FL_alpha"); break;
  case 1: wcscpy(name, L"FL_beta"); break;
  case 2: wcscpy(name, L"FL_gamma"); break;

  case 3: wcscpy(name, L"ML_alpha"); break;
  case 4: wcscpy(name, L"ML_beta"); break;
  case 5: wcscpy(name, L"ML_gamma"); break;

  case 6: wcscpy(name, L"RL_alpha"); break;
  case 7: wcscpy(name, L"RL_beta"); break;
  case 8: wcscpy(name, L"RL_gamma"); break;

  case  9: wcscpy(name, L"FR_alpha"); break;
  case 10: wcscpy(name, L"FR_beta"); break;
  case 11: wcscpy(name, L"FR_gamma"); break;

  case 12: wcscpy(name, L"MR_alpha"); break;
  case 13: wcscpy(name, L"MR_beta"); break;
  case 14: wcscpy(name, L"MR_gamma"); break;

  case 15: wcscpy(name, L"RR_alpha"); break;
  case 16: wcscpy(name, L"RR_beta"); break;
  case 17: wcscpy(name, L"RR_gamma"); break;

  
    //desired angles
    
  case 18: wcscpy(name, L"FL_alpha_target"); break;
  case 19: wcscpy(name, L"FL_beta_target"); break;
  case 20: wcscpy(name, L"FL_gamma_target"); break;

  case 21: wcscpy(name, L"ML_alpha_target"); break;
  case 22: wcscpy(name, L"ML_beta_target"); break;
  case 23: wcscpy(name, L"ML_gamma_target"); break;

  case 24: wcscpy(name, L"RL_alpha_target"); break;
  case 25: wcscpy(name, L"RL_beta_target"); break;
  case 26: wcscpy(name, L"RL_gamma_target"); break;

  case 27: wcscpy(name, L"FR_alpha_target"); break;
  case 28: wcscpy(name, L"FR_beta_target"); break;
  case 29: wcscpy(name, L"FR_gamma_target"); break;

  case 30: wcscpy(name, L"MR_alpha_target"); break;
  case 31: wcscpy(name, L"MR_beta_target"); break;
  case 32: wcscpy(name, L"MR_gamma_target"); break;

  case 33: wcscpy(name, L"RR_alpha_target"); break;
  case 34: wcscpy(name, L"RR_beta_target"); break;
  case 35: wcscpy(name, L"RR_gamma_target"); break;


  //control torques for body joints
  case 36:  wcscpy(name, L"j_1_2_torque"); break;
  case 37:  wcscpy(name, L"j_2_3_torque"); break;

  //target angles for body joints
  case 38:  wcscpy(name, L"j_1_2_target"); break;
  case 39:  wcscpy(name, L"j_2_3_target"); break;

  //COM of the robot
  case 40: wcscpy(name, L"ROBOT_COM_X_CALCULATED"); break;
  case 41: wcscpy(name, L"ROBOT_COM_Y_CALCULATED"); break;
  case 42: wcscpy(name, L"ROBOT_COM_Z_CALCULATED"); break;

  default: status = 1;
  }
}

void _cdecl EXT_GetY(double time, PDouble U, PDouble X, PDouble Y, int& status)
{
  // Basic computation procedure that calculates values of output signals based
  // on the current time, input values and values of model parameters
  //
  // Parameters:
  // time is the current model time, sec
  // U is the pointer to the first element of vector of input values
  // X is reserved for future use (state variables)
  // Y is the pointer to the first element of vector of output variables
  // status is the exit code 
  //   status==0 means no errors occured

  int numberOfInputs = 0;
  EXT_GetNumU(numberOfInputs, status);
  myRobot.recieveFeedBack(U, numberOfInputs);

  Eigen::VectorXd output(43);
  output.fill(0); 

  output = myRobot.getControls(time);
  for(int i = 0; i < output.size(); i++)
  {
    Y[i] = output[i];
  }

  status = 0;
}

void _cdecl EXT_GetNumParameters(int& num, int& status)
{
  // num - count of model parameters
  // status - exit code (0 - no errors)

  num    = 3;    // Count of model parameters
  status = 0;
}

void _cdecl EXT_GetParameters(PDouble value, int& status)
{
  // value is the pointer to the first element of vector of parameters
  // status is the exit code 
  //   status==0 means no errors occured

  status = 0;
}

void _cdecl EXT_GetParameterName(int i, WChar name, int& status)
{
  // i is the index of parameter, first parameter has index 0
  // name is the name of parameter
  // status is the exit code 
  //   status==0 means no errors occured

  status = 0;
  switch(i)
  {
    case 0: wcscpy(name, L"kP"); break;
    case 1: wcscpy(name, L"kI"); break;
    case 2: wcscpy(name, L"kD"); break;
    default: status = 1;
  }
}

void _cdecl EXT_SetParameters(int numpara, PDouble para, int& status)
{
  // numpara is the length of vector of parameters
  // para is the pointer to the first element of vector of parameter
  // status is the exit code 
  //   status==0 means no errors occured
  int numParams = 0;
  EXT_GetNumParameters(numParams, status);
  myRobot.recieveParameters(para, numParams);
  status = 0;
}

void _cdecl EXT_StepConfirmed()
{
  // Universal Mechanism uses numerical integration methods with a variable step
  // size. If this external library includes built-in intergation method it
  // should use this procedure to shift current time.
}