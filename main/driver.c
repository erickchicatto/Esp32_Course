#include <stdio.h>
#include "driver.h"

typedef enum{
    L9733_CMD_TYPE_OUTPUT,
    L9733_CMD_TYPE_DIAG_MODE,
    L9733_CMD_TYPE_PROTECT,
}l9733_cmd_type_t;

/**Use the functions that was written in the driver.h module*/
static fsm_rslt_t l9733_set_cmd(l9733_t *obj,l9733_cmd_type_t cmd ){
   
  const char *strings[]= {
      "out",
      "dia",
      "pro",
  };
  
  uint16_t msg = 0U;
  msg |= L9733_CMD_KEYWORD;

  switch(cmd){
     case L9733_CMD_TYPE_OUTPUT:
         msg |= L9733_CMD_WM_OUTPUT;
         msg |= obj->output;
         break;
     case L9733_CMD_TYPE_DIAG_MODE:
         msg |= L9733_CMD_WM_DIAG;
         msg |= obj->diag_mode;
         break;
     case L9733_CMD_TYPE_PROTECT:
         msg |= L9733_CMD_WM_PROTECT;
         msg |= obj->protection;
         break;
  }
    printf("cmd: %s, msg: 0x%04x\n", strings[cmd], msg);
    obj->bus->tx_buf = msg;
    return FMS_RSLT_CMD_COMPLETE;
}
