#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "menu_squeletton.h"
#include "utils.h"


int main() {
  menu_ctx_t* menu = menu_init(&root);
  menu_interract(menu);
  return 0;
}
