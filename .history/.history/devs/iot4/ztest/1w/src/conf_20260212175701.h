#include "temp1w_se.h"

//----config ------

static const T1w_Config config = {
  .gpio = 4,
  .sa = 0,
  .threshold = 1.5,
  .name = "temp_out",
  .rec = true,
  .pwd = ""
},
{
  .gpio = 4,
  .sa = 1,
  .threshold = 1.5,
  .name = "ari_room",
  .rec = true,
  .pwd = "duck"
};

//-----(initial) state ------
static T1w_State state = {
  .sa = 0,
  .name = "temp_out",
  .lastValue = 0.0
};