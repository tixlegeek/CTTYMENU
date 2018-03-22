#ifndef MENU_H
#define MENU_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define MENUMAXDEPTH 10
#define MENUMAXWIDTH 10
#define MENUMAXNAMELENGTH 32
typedef enum menu_action_t {
  ERROR,
  SUCCESS,
  EXEC_SUCCESS,
  EXEC_ERROR,
  EXEC_EMPTY,
  POSSIBLE,
  IMPOSSIBLE,
  EMPTY
} menu_action_t;

typedef struct menu_node_t {
  uint8_t name[MENUMAXNAMELENGTH];
  menu_action_t (*fnc)();
  struct menu_node_t* subnodes[MENUMAXWIDTH];
} menu_node_t;

typedef struct menu_ctx_t {
  uint8_t deepness;
  uint8_t currentsub;
  struct menu_node_t* rootnode;
  struct menu_node_t* currentnode;
  struct menu_node_t** parentnodes;
  uint8_t parentids[MENUMAXDEPTH];
} menu_ctx_t;

void menu_debug(menu_ctx_t* menu);
menu_ctx_t* menu_init(menu_node_t* rootnode);
menu_node_t** getSubMenus(menu_ctx_t* menu);
uint8_t menu_countSubMenus(menu_ctx_t* menu);
menu_action_t menu_next(menu_ctx_t* menu);
menu_action_t menu_select(menu_ctx_t* menu);
menu_action_t menu_back(menu_ctx_t* menu);
menu_action_t menu_interract(menu_ctx_t* menu);
menu_action_t menu_setTitle(menu_ctx_t* menu, uint8_t* str);
menu_action_t menu_setName(menu_ctx_t* menu, uint8_t *str);
menu_action_t menu_setFunction(menu_ctx_t* menu,
                               menu_action_t (*fnc)(menu_ctx_t* menu));

#endif
