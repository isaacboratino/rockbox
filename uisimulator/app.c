/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2002 Daniel Stenberg
 *
 * All files in this archive are subject to the GNU General Public License.
 * See the file COPYING in the source tree root for full license agreement.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/

#include "types.h"
#include "lcd.h"
#include "button.h"
#include "kernel.h"

#include "tree.h"

extern void tetris(void);

#define LINE_HEIGHT 8

#define MAX_LINE 3 /* the last index with info, starting on 0 */

/* global cursor */
int cursor = 0;

void menu_init(void)
{
  lcd_puts(6, 0,  "Rockabox", 0);
  lcd_puts(6, 8,  "Boxrock", 0);
  lcd_puts(6, 16, "Browse", 0);
#define LINE_BROWSE 2
  lcd_puts(6, 24, "Tetris", 0);
#define LINE_TETRIS 3
  lcd_puts(8, 38, "Rockbox!", 2);

  lcd_puts(0, cursor, "-", 0);
}

void app_main(void)
{
  int key;

  menu_init();

  while(1) {
    key = button_get();

    if(!key) {
      sleep(1);
      continue;
    }
    switch(key) {
    case BUTTON_UP:
      if(cursor) {
        lcd_puts(0, cursor, " ", 0);
        cursor-= LINE_HEIGHT;
        lcd_puts(0, cursor, "-", 0);
      }
      break;
    case BUTTON_DOWN:
      if(cursor<(MAX_LINE*LINE_HEIGHT)) {
        lcd_puts(0, cursor, " ", 0);
        cursor+=LINE_HEIGHT;
        lcd_puts(0, cursor, "-", 0);
      }
      break;
    case BUTTON_RIGHT:      
    case BUTTON_PLAY:      
      switch(cursor) {
      case (LINE_TETRIS * LINE_HEIGHT):
        lcd_clearrect(0, 0, LCD_WIDTH, LCD_HEIGHT);
        tetris();
        lcd_clearrect(0, 0, LCD_WIDTH, LCD_HEIGHT);
        menu_init();
        break;
      case (LINE_BROWSE * LINE_HEIGHT):
        dirbrowse("/");
        lcd_clearrect(0, 0, LCD_WIDTH, LCD_HEIGHT);
        menu_init();
        break;
      }
      break;
    }
    lcd_update();
  }
}
