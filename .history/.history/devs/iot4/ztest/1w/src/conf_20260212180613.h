#include "temp1w_se.h"

//----config ------
//{gpio, sa, threshold, name, rec, pwd }
static const T1w_Config t1w_config[2] = {
  {4, 0, 1.5, "temp_out", true, ""},
  {4, 1, 1.5, "temp_ari", true, "duck"}
};

//-----(initial) state ------
//{sa, name, lastValue}
static T1w_State t1w_state[2] = {
  {0, "temp_out", 0.0 },
  {1, "temp_ari", 0.0 }
};

