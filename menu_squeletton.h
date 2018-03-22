#ifndef MENU_SQUELETTON_H
#define MENU_SQUELETTON_H
#include "menu.h"
#include "utils.h"
/**
    Those are all functions and nodes. You can make whatever
    files you like to split every menu/section/node/app.
*/

/*
  Dummy apps which are triggered from the menu.
*/

// Callbacks used to turn on and off the "WiFi" menu.
menu_action_t app_wifi_ac(menu_ctx_t* menu);
menu_action_t app_wifi_dc(menu_ctx_t* menu);
// Callback that shows how to go fast to the ROOT menu.
menu_action_t app_goroot(menu_ctx_t* menu);
// Callback used as example for every "File" submenus
menu_action_t app_File_menu(menu_ctx_t* menu);

// Menu node initialisation. Every links between menu & the other submenu as a
// structure with Callbacks
// and subnodes..
menu_node_t menu_goback = {.name = "Back", .fnc = menu_back, .subnodes = {}};
menu_node_t menu_gobackback = {.name = "Back to root",
                               .fnc = app_goroot,
                               .subnodes = {}};

menu_node_t menu_File_newfile = {.name = "New File",
                                 .fnc = app_File_menu,
                                 .subnodes = {}};
menu_node_t menu_File_open = {.name = "Open",
                              .fnc = app_File_menu,
                              .subnodes = {}};
menu_node_t menu_File_save = {.name = "Save",
                              .fnc = app_File_menu,
                              .subnodes = {}};
menu_node_t menu_File_more_A = {.name = "More A",
                                .fnc = app_File_menu,
                                .subnodes = {}};
menu_node_t menu_File_more_B = {.name = "More B",
                                .fnc = app_File_menu,
                                .subnodes = {}};
menu_node_t menu_File_more = {
    .name = "File/More",
    .fnc = NULL,
    .subnodes = {&menu_gobackback, &menu_goback, &menu_File_more_A,
                 &menu_File_more_B}};

menu_node_t menu_File_deactivateWiFi = {.name = "Toggle: On",
                                        .fnc = app_wifi_dc,
                                        .subnodes = {}};
menu_node_t menu_File_activateWiFi = {.name = "Toggle: Off",
                                      .fnc = app_wifi_ac,
                                      .subnodes = {}};
menu_node_t menu_File = {
    .name = "File",
    .fnc = NULL,
    .subnodes = {&menu_goback, &menu_File_newfile, &menu_File_open,
                 &menu_File_save, &menu_File_more, &menu_File_deactivateWiFi}};

menu_node_t menu_Edit = {.name = "Edit", .fnc = app_File_menu, .subnodes = {}};
menu_node_t menu_View = {.name = "View", .fnc = app_File_menu, .subnodes = {}};

menu_action_t app_File_menu(menu_ctx_t* menu) {
  printf("This callback has been reached.");
  printf("\"%s\" got executed from \"%s\"! \n",
         menu->currentnode->subnodes[menu->currentsub]->name,
         menu->currentnode->name);
  return SUCCESS;
}
menu_action_t app_wifi_ac(menu_ctx_t* menu) {
  menu_setFunction(menu, &app_wifi_dc);
  menu_setName(menu, "Toggle: On");
  return SUCCESS;
}

menu_action_t app_wifi_dc(menu_ctx_t* menu) {
  //  menu->currentsub = &app_wifi_ac;
  menu_setFunction(menu, &app_wifi_ac);
  menu_setName(menu, "Toggle: Off");
  return SUCCESS;
}

menu_action_t app_goroot(menu_ctx_t* menu) {
  while (menu_back(menu) == SUCCESS) {
  };
  return SUCCESS;
}

menu_node_t root = {.name = "-- CTTYMenu Example: --",
                    .fnc = NULL,
                    .subnodes = {&menu_File, &menu_Edit, &menu_View, &menu_File_deactivateWiFi}};
#endif
