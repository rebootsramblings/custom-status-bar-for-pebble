custom-status-bar-for-pebble

============================

A plug and play custom status bar implementation for pebble apps and watch faces. Easily populate 3 text layers and/or 5 bitmap layers.

Use:

Choose a status bar height and icon size. Icons should be square with a maximum of 28 pixels.
```c
#define BAR_HEIGHT 20

#define ICON_WIDTH_HEIGHT 15
```

Declare

static CustomStatusBarLayer *custom_status_bar;

Create

custom_status_bar = custom_status_bar_layer_create(BAR_HEIGHT, GColorBlack, ICON_WIDTH_HEIGHT);

Set Text and Icons

Text layers, use positions CSB_TEXT_LEFT, CSB_TEXT_RIGHT, CSB_TEXT_CENTER

char *t = ...;

custom_status_bar_layer_set_text(custom_status_bar, CSB_TEXT_LEFT, t);

Icons, use positions CSB_ICON_0 to CSB_ICON_4 (positions are left to right, 0 indexed)

custom_status_bar_layer_set_bitmap(custom_status_bar, CSB_ICON_4, your_gbitmap); 

When you're done, destroy

custom_status_bar_layer_destroy(custom_status_bar);
