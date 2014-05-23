custom-status-bar-for-pebble
============================

A plug and play custom status bar implementation for pebble apps and watch faces. Easily populate 3 text layers and/or 5 bitmap layers.

Use:

1) Choose a status bar height and icon size. Icons should be square with a maximum of 28 pixels.
#define BAR_HEIGHT 20
#define ICON_WIDTH_HEIGHT 15

2) Declare
static CustomStatusBarLayer *custom_status_bar;

3) Create
custom_status_bar = custom_status_bar_layer_create(BAR_HEIGHT, GColorBlack, ICON_WIDTH_HEIGHT);

4) Set Text and Icons
//Text layers, use positions CSB_TEXT_LEFT, CSB_TEXT_RIGHT, CSB_TEXT_CENTER
char *t = ...;
custom_status_bar_layer_set_text(custom_status_bar, CSB_TEXT_LEFT, t);

//Icons: Use positions CSB_ICON_0 to CSB_ICON_4 (positions are left to right, 0 indexed)
custom_status_bar_layer_set_bitmap(custom_status_bar, CSB_ICON_4, your_gbitmap); 

5) When you're done, destroy
custom_status_bar_layer_destroy(custom_status_bar);
