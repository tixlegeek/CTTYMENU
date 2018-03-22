#include "menu.h"
#include "utils.h"
/**
     ██████╗████████╗████████╗██╗   ██╗███╗   ███╗███████╗███╗   ██╗██╗   ██╗
    ██╔════╝╚══██╔══╝╚══██╔══╝╚██╗ ██╔╝████╗ ████║██╔════╝████╗  ██║██║   ██║
    ██║        ██║      ██║    ╚████╔╝ ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║
    ██║        ██║      ██║     ╚██╔╝  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║
    ╚██████╗   ██║      ██║      ██║   ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝
     ╚═════╝   ╚═╝      ╚═╝      ╚═╝   ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝
    A tiny fulltext menu you can use and modify without worrying about a
    star-coder's bullshit around. Just use it. Coded with love by Tixlegeek

    Tixlegeek < @tixlegeek - http://www.tixlegeek.io >
*/


/**
        Display valuable informations in console. Feel free
        to pick things up here to code your UI.
*/
void menu_debug(menu_ctx_t* menu) {
  uint8_t i = 0;
  printf("\n\033[7m      --- CTTYMenu ---      \033[m\n\n");
  printf(" Simple and beautiful menu \n");
  printf(" you can just USE in C code \n\n");
  printf(" [ DOWN ]\t: Next entry. \n");
  printf(" [ LEFT ]\t: Back to parent. \n");
  printf(" [ RIGHT ]\t: Select entry. \n");
  printf(" [ Q ]\t: Quit. \n\n");
  printf(" \"+\"\t: Nested submenus\n");
  printf(" \"-\"\t: Executable callbacks\n\n");
  printf(" Have fun!        @tixlegeek");
  printf("\n\033[7m[  %s  ]\033[m\n", menu->currentnode->name);
  printf("-----------------------------\n");
  while (menu->currentnode->subnodes[i] != NULL) {
    if (*menu->currentnode->subnodes[i]->fnc) {
      printf("- ");
    } else {
      printf("+ ");
    }
    if (i == menu->currentsub)
      printf(" \033[7m%s\033[m \n", menu->currentnode->subnodes[i]->name);
    else
      printf(" %s\n", menu->currentnode->subnodes[i]->name);
    i++;
  }
  printf("-----------------------------\n");
}

/**
Initialize a new menu using the rootnode squeletton.
*/
menu_ctx_t* menu_init(menu_node_t* rootnode) {
  menu_ctx_t* newctx = (menu_ctx_t*)malloc(sizeof(menu_ctx_t));
  if (newctx == NULL)
    return NULL;
  newctx->currentsub = 0;
  newctx->currentnode = rootnode;
  newctx->rootnode = rootnode;
  // Array of parent nodes by levels.
  newctx->parentnodes =
      (menu_node_t**)malloc(MENUMAXDEPTH * sizeof(menu_node_t*));
  newctx->deepness = 0;
  newctx->parentids[0] = 0;
  return newctx;
}

/**
        Get number of submenus
*/
uint8_t menu_countSubMenus(menu_ctx_t* menu) {
  uint8_t i = 0;
  while (menu->currentnode->subnodes[++i]) {
  }
  return i;
}

/**
        Set the cursor on the next submenu in the context.
*/
menu_action_t menu_next(menu_ctx_t* menu) {
  uint8_t subn = menu_countSubMenus(menu);

  if (menu->currentsub < subn - 1)
    menu->currentsub++;
  else
    menu->currentsub = 0;

  return SUCCESS;
}

/**
        Setn the cursor on the next submenu in the context.
*/
menu_action_t menu_setFunction(menu_ctx_t* menu,
                               menu_action_t (*fnc)(menu_ctx_t* menu)) {
  if (*fnc != NULL) {
    menu->currentnode->subnodes[menu->currentsub]->fnc = fnc;
    return SUCCESS;
  } else {
    return ERROR;
  }
}

/**
        Setn the cursor on the next submenu in the context.
*/
menu_action_t menu_setName(menu_ctx_t* menu, uint8_t* str) {
  memset(menu->currentnode->subnodes[menu->currentsub]->name, '\0',
         MENUMAXNAMELENGTH);
  strncpy(menu->currentnode->subnodes[menu->currentsub]->name, (char*)str,
          MENUMAXNAMELENGTH - 1);
  return SUCCESS;
}

/**
        Setn the cursor on the next submenu in the context.
*/
menu_action_t menu_setTitle(menu_ctx_t* menu, uint8_t* str) {
  memset(menu->currentnode->name, '\0', MENUMAXNAMELENGTH);
  strncpy(menu->currentnode->name, str, MENUMAXNAMELENGTH - 1);
  // sprintf(menu->currentnode->name, "%s", str);
  return SUCCESS;
}

/**
        Select current item/submenu
*/
menu_action_t menu_select(menu_ctx_t* menu) {
  // If the callback of the menu is set, then execute it
  // instead of going deeper.
  if (*menu->currentnode->subnodes[menu->currentsub]->fnc) {
    menu_action_t ret =
        menu->currentnode->subnodes[menu->currentsub]->fnc(menu);
    return ret;
  }
  // Go deeper as the sub element is selected.
  menu->deepness++;
  menu->parentids[menu->deepness] = menu->currentsub;
  menu->parentnodes[menu->deepness] = menu->currentnode;
  menu->currentnode = menu->currentnode->subnodes[menu->currentsub];
  menu->currentsub = 0;
  return SUCCESS;
}

/**
        Go back a level down.
*/
menu_action_t menu_back(menu_ctx_t* menu) {
  // Can't go up anymore, return "EMPTY"
  if (!menu->deepness) {
    menu->currentsub = 0;
    return EMPTY;
  }
  menu->currentnode = menu->parentnodes[menu->deepness];
  menu->currentsub = menu->parentids[menu->deepness];
  menu->deepness--;

  return SUCCESS;
}

/**
    Launches menu interraction from it's context
*/
menu_action_t menu_interract(menu_ctx_t* menu) {
  menu_action_t result;
  printf("\e[2J\e[H");
  menu_debug(menu);
  int c, quit = 0;
  while (!quit) {
    if (kbhit()) {
      c = getchar();
      switch (c) {
        case 'q':  // Binding a key to "quit" event.
          quit++;
          return EMPTY;
          break;
        case 66:  // Binding a key to "next" sub element.
          result = menu_next(menu);
          printf("\e[2J\e[H");  // CLRSCR
          menu_debug(menu);
          break;
        case 68:  // Binding a key to "parent" element.
          result = menu_back(menu);
          printf("\e[2J\e[H");  // CLRSCR
          menu_debug(menu);
          break;
        case 67:                // Binding a key to element selection.
          printf("\e[2J\e[H");  // CLRSCR
          result = menu_select(menu);
          menu_debug(menu);
          break;
        default:
          continue;
          break;
      }
      switch (result) {
        // Usually app related callback response. Quits the interraction
        case EXEC_SUCCESS:
          return SUCCESS;
          break;
        case EXEC_ERROR:
          return ERROR;
          break;
        // Node related response. Do not quits the interraction
        case SUCCESS:
          // printf("SUCCESS\n");
          // return SUCCESS;
          break;
        case ERROR:
          //  printf("ERROR\n");
          return ERROR;
          break;
        // Unknowwn response from the interraction.
        default:

          break;
      }
    }
  }
}
