#include "BearLibTerminal.h"
#include "Components.h"

int main() {
  Position pos = { 0, 0 };


  terminal_open();

  // Printing text
  terminal_color("blue");
  terminal_print(pos.x,  pos.y, "Salut, world!");
  terminal_put(10, 10, 205);
  terminal_refresh();

  // Wait until user close the window
  while (terminal_read() != TK_CLOSE);

  terminal_close();
}
