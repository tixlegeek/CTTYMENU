```
/**
     ██████╗████████╗████████╗██╗   ██╗███╗   ███╗███████╗███╗   ██╗██╗   ██╗
    ██╔════╝╚══██╔══╝╚══██╔══╝╚██╗ ██╔╝████╗ ████║██╔════╝████╗  ██║██║   ██║
    ██║        ██║      ██║    ╚████╔╝ ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║
    ██║        ██║      ██║     ╚██╔╝  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║
    ╚██████╗   ██║      ██║      ██║   ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝
     ╚═════╝   ╚═╝      ╚═╝      ╚═╝   ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝
    A tiny fulltext menu you can use and modify withour worrying about a
    star-coder's bullshit around. Just use it. Coded with love by Tixlegeek

    Tixlegeek < @tixlegeek - http://www.tixlegeek.io >

Example:
--------------------------------------------------------------------------------

--- CTTYMenu ---      

Simple and beautiful menu
you can just USE in C code

[ DOWN ]	: Next entry.
[ LEFT ]	: Back to parent.
[ RIGHT ]	: Select entry.
[ Q ]	: Quit.

"+"	: Nested submenus
"-"	: Executable callbacks

Have fun!        @tixlegeek
[  -- CTTYMenu Example: --  ]
-----------------------------
+  File
-  Edit
-  View
-  Toggle: On
-----------------------------
```
# CTTYMENU
I could not came out with a rad name for this. So it's a tiny MENU logic
code which allows you to create simple yet beautiful UI ncurses style,
but with your own style, without integrating a bunch of crap from a shitty
github overthinked project.

# Example
Lets assume you decide to code an amazing stuff using my little thingy:

A little bit of main.c:

```
int main() {
  menu_ctx_t* menu = menu_init(&root);
  menu_interract(menu);
  return 0;
}
```

A littlebit of structure using a squeletton, lets say "menu_squeletton.h"

```
// A menu node which executes the app_goroot callback.
menu_node_t menu_gobackback = {.name = "Back to root",
                               .fnc = app_goroot,
                               .subnodes = {}};

// A menu node countaining subnodes.
menu_node_t menu_File = {
     .name = "File",
     .fnc = NULL,
     .subnodes = {&menu_goback, &menu_File_newfile, &menu_File_open,
                  &menu_File_save, &menu_File_more, &menu_File_deactivateWiFi}};


```

Then you open your haxor term and call a good make:
```
tixlegeek@devship:~$ make
rm -f main
# COMPILING ###########################################################
cc -o main main.c menu.c utils.c
# RUN #################################################################
cp ./main /tmp/main
chmod +x /tmp/main
/tmp/main
--- CTTYMenu ---      

Simple and beautiful menu
you can just USE in C code

[ DOWN ]	: Next entry.
[ LEFT ]	: Back to parent.
[ RIGHT ]	: Select entry.
[ Q ]	: Quit.

"+"	: Nested submenus
"-"	: Executable callbacks

Have fun!        @tixlegeek
[  DOWN:Next,RIGHT:Select  ]
-----------------------------
+  File
-  Toggle: Off
-----------------------------
tixlegeek@devship:~$
```
BOOM! Laser robots.

# Side note
As i don't write code following any rules (what a punk, you'll say), i sometime
write uncomprehensible commentaries or readmes. Please use your imagination <3

# License                 
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
