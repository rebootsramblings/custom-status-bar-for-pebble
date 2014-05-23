#include "pebble.h"

typedef struct Layer CustomStatusBarLayer;

#define MAX_ICON_WIDTH 28

typedef enum {
  CSB_TEXT_LEFT,
  CSB_TEXT_RIGHT,
  CSB_TEXT_CENTER,
} CsbTextPosition;

//ICON positions start left to right, 0 indexed
typedef enum {
  CSB_ICON_0,
  CSB_ICON_1,
  CSB_ICON_2,
  CSB_ICON_3,
  CSB_ICON_4,
} CsbIconPosition;

//icon_width determines both the width and height of the BitmapLayers being created in the status bar
CustomStatusBarLayer * custom_status_bar_layer_create(uint8_t height, GColor bar_colour, uint8_t icon_width);
void custom_status_bar_layer_destroy(CustomStatusBarLayer* custom_status_bar_layer);
void custom_status_bar_layer_set_text(CustomStatusBarLayer* custom_status_bar_layer, CsbTextPosition position, char* status_bar_text);
void custom_status_bar_layer_set_text_font(CustomStatusBarLayer* custom_status_bar_layer, CsbTextPosition position, GFont font);
void custom_status_bar_layer_set_text_hidden(CustomStatusBarLayer* custom_status_bar_layer, CsbTextPosition position, bool hidden);
void custom_status_bar_layer_set_bitmap(CustomStatusBarLayer* custom_status_bar_layer, CsbIconPosition position, GBitmap* gbitmap);
void custom_status_bar_layer_set_bitmap_hidden(CustomStatusBarLayer* custom_status_bar_layer, CsbIconPosition position, bool hidden);
void custom_status_bar_layer_set_all_text_hidden(CustomStatusBarLayer* custom_status_bar_layer, bool hidden);
void custom_status_bar_layer_set_all_bitmaps_hidden(CustomStatusBarLayer* custom_status_bar_layer, bool hidden);


