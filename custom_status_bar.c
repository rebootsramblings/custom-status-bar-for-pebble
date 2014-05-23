#include "custom_status_bar.h"
#include "pebble.h"

#ifndef PEBBLE_HEIGHT
#define PEBBLE_HEIGHT 168
#endif

#ifndef PEBBLE_WIDTH
#define PEBBLE_WIDTH 144
#endif

typedef struct {
    uint8_t height;
    uint8_t icon_width;
    GColor bar_colour;
    GColor text_colour;
    TextLayer* left_text;
    TextLayer* center_text;
    TextLayer* right_text;
    BitmapLayer* icon_0;
    BitmapLayer* icon_1;
    BitmapLayer* icon_2;
    BitmapLayer* icon_3;
    BitmapLayer* icon_4;
} CustomStatusBarLayerHidden;

static void update_proc(Layer* layer, GContext *context);

CustomStatusBarLayer * custom_status_bar_layer_create(uint8_t height, GColor bar_colour, uint8_t icon_width){

    if(icon_width > MAX_ICON_WIDTH){
        APP_LOG(APP_LOG_LEVEL_ERROR, "ERROR: ICON WIDTH TOO LARGE. SEE MAX_ICON_WIDTH. STATUS BAR NOT CREATED. RETURNING NULL.");
        return NULL;
    }

    //Status bar frame
    GRect frame = (GRect){ .origin = GPointZero,
        .size = {
            .h = height,
            .w = PEBBLE_WIDTH
        }  
    };

    CustomStatusBarLayer* status_bar = layer_create_with_data(frame, sizeof(CustomStatusBarLayerHidden));
    if (status_bar == NULL) {
        APP_LOG(APP_LOG_LEVEL_ERROR, "OOM Couldn't create custom status bar.");
    }

    // Get status hidden pointer
    CustomStatusBarLayerHidden* status_hidden = (CustomStatusBarLayerHidden*) layer_get_data(status_bar);

    layer_set_update_proc(status_bar, update_proc);
    
    // Set up bar variables
    status_hidden->height = height;
    status_hidden->icon_width = icon_width;
    status_hidden->bar_colour = bar_colour;
    // TextColor
    if(bar_colour == GColorBlack){
        status_hidden->text_colour = GColorWhite;    
    }else{
        status_hidden->text_colour = GColorBlack;
    }

    status_hidden->left_text = NULL;
    status_hidden->center_text = NULL;
    status_hidden->right_text = NULL;
    status_hidden->icon_0 = NULL;
    status_hidden->icon_1 = NULL;
    status_hidden->icon_2 = NULL;
    status_hidden->icon_3 = NULL;
    status_hidden->icon_4 = NULL;

    return status_bar;
}

void custom_status_bar_layer_destroy(CustomStatusBarLayer* custom_status_bar_layer){

    CustomStatusBarLayerHidden* status_hidden = (CustomStatusBarLayerHidden*) layer_get_data(custom_status_bar_layer);
    
    if(status_hidden->left_text != NULL) text_layer_destroy(status_hidden->left_text);
    if(status_hidden->right_text != NULL) text_layer_destroy(status_hidden->right_text);
    if(status_hidden->center_text != NULL) text_layer_destroy(status_hidden->center_text);
    if(status_hidden->icon_0 != NULL) bitmap_layer_destroy(status_hidden->icon_0);
    if(status_hidden->icon_1 != NULL) bitmap_layer_destroy(status_hidden->icon_1);
    if(status_hidden->icon_2 != NULL) bitmap_layer_destroy(status_hidden->icon_2);
    if(status_hidden->icon_3 != NULL) bitmap_layer_destroy(status_hidden->icon_3);
    if(status_hidden->icon_4 != NULL) bitmap_layer_destroy(status_hidden->icon_4);

    if(custom_status_bar_layer != NULL) layer_destroy(custom_status_bar_layer);

}

void custom_status_bar_layer_set_height(CustomStatusBarLayer* custom_status_bar_layer, uint32_t height){
    CustomStatusBarLayerHidden* status_hidden = (CustomStatusBarLayerHidden*) layer_get_data(custom_status_bar_layer);
    status_hidden->height = height;
    layer_mark_dirty(custom_status_bar_layer);
}

void custom_status_bar_layer_set_text(CustomStatusBarLayer* custom_status_bar_layer, CsbTextPosition position, char * status_bar_text){

    CustomStatusBarLayerHidden* status_hidden = (CustomStatusBarLayerHidden*) layer_get_data(custom_status_bar_layer);

    switch(position){
        case CSB_TEXT_LEFT:
        if(status_hidden->left_text == NULL){
            status_hidden->left_text = text_layer_create(GRect(0, 0, PEBBLE_WIDTH, status_hidden->height));
            text_layer_set_text_alignment(status_hidden->left_text, GAlignLeft);
            text_layer_set_font(status_hidden->left_text, fonts_get_system_font(FONT_KEY_GOTHIC_14));
            text_layer_set_text_color(status_hidden->left_text, status_hidden->text_colour);
            text_layer_set_background_color(status_hidden->left_text, GColorClear);
            layer_add_child(custom_status_bar_layer, text_layer_get_layer(status_hidden->left_text));
        }
        text_layer_set_text(status_hidden->left_text, status_bar_text);
        break;

        case CSB_TEXT_RIGHT:
        if(status_hidden->right_text == NULL){
            status_hidden->right_text = text_layer_create(GRect(0, 0, PEBBLE_WIDTH, status_hidden->height));
            text_layer_set_text_alignment(status_hidden->right_text, GAlignRight);
            text_layer_set_font(status_hidden->right_text, fonts_get_system_font(FONT_KEY_GOTHIC_14));
            text_layer_set_text_color(status_hidden->right_text, status_hidden->text_colour);
            text_layer_set_background_color(status_hidden->right_text, GColorClear);
            layer_add_child(custom_status_bar_layer, text_layer_get_layer(status_hidden->right_text));
        }
        text_layer_set_text(status_hidden->right_text, status_bar_text);
        break;

        case CSB_TEXT_CENTER:
        if(status_hidden->center_text == NULL){  
            status_hidden->center_text = text_layer_create(GRect(0, 0, PEBBLE_WIDTH, status_hidden->height));
            text_layer_set_text_alignment(status_hidden->center_text, GTextAlignmentCenter);
            text_layer_set_font(status_hidden->center_text, fonts_get_system_font(FONT_KEY_GOTHIC_14));
            text_layer_set_text_color(status_hidden->center_text, status_hidden->text_colour);
            text_layer_set_background_color(status_hidden->center_text, GColorClear);
            layer_add_child(custom_status_bar_layer, text_layer_get_layer(status_hidden->center_text));
        }
        text_layer_set_text(status_hidden->center_text, status_bar_text);
        break;

    } 

}

void custom_status_bar_layer_set_text_font(CustomStatusBarLayer* custom_status_bar_layer, CsbTextPosition position, GFont font){

    CustomStatusBarLayerHidden* status_hidden = (CustomStatusBarLayerHidden*) layer_get_data(custom_status_bar_layer);

    switch(position){
        case CSB_TEXT_LEFT:
        text_layer_set_font(status_hidden->left_text, font);
        break;

        case CSB_TEXT_RIGHT:
        text_layer_set_font(status_hidden->right_text, font);
        break;

        case CSB_TEXT_CENTER:
        text_layer_set_font(status_hidden->center_text, font);
        break;
    } 

}

void custom_status_bar_layer_set_text_hidden(CustomStatusBarLayer* custom_status_bar_layer, CsbTextPosition position, bool hidden){

    CustomStatusBarLayerHidden* status_hidden = (CustomStatusBarLayerHidden*) layer_get_data(custom_status_bar_layer);

    switch(position){
        case CSB_TEXT_LEFT:
        layer_set_hidden(text_layer_get_layer(status_hidden->left_text), hidden);
        break;

        case CSB_TEXT_RIGHT:
        layer_set_hidden(text_layer_get_layer(status_hidden->right_text), hidden);
        break;

        case CSB_TEXT_CENTER:
        layer_set_hidden(text_layer_get_layer(status_hidden->center_text), hidden);
        break;
    } 

}

void custom_status_bar_layer_set_bitmap(CustomStatusBarLayer* custom_status_bar_layer, CsbIconPosition position, GBitmap* gbitmap){

    CustomStatusBarLayerHidden* status_hidden = (CustomStatusBarLayerHidden*) layer_get_data(custom_status_bar_layer);

    uint8_t icon_width = status_hidden->icon_width;
    uint8_t height = status_hidden->height;

    switch(position){
        case CSB_ICON_0:
        if(status_hidden->icon_0 == NULL){
            status_hidden->icon_0 = bitmap_layer_create(GRect(PEBBLE_WIDTH/10 - icon_width/2, height/2 - icon_width/2, icon_width, icon_width));
            bitmap_layer_set_background_color(status_hidden->icon_0 , GColorClear);
            layer_add_child(custom_status_bar_layer, bitmap_layer_get_layer(status_hidden->icon_0));
        }
        bitmap_layer_set_bitmap(status_hidden->icon_0, gbitmap);
        break;

        case CSB_ICON_1:
        if(status_hidden->icon_1 == NULL){
             status_hidden->icon_1 = bitmap_layer_create(GRect(PEBBLE_WIDTH * 3/10 - icon_width/2, height/2 - icon_width/2, icon_width, icon_width));
            bitmap_layer_set_background_color(status_hidden->icon_1 , GColorClear);
            layer_add_child(custom_status_bar_layer, bitmap_layer_get_layer(status_hidden->icon_1));
        }
        bitmap_layer_set_bitmap(status_hidden->icon_1, gbitmap);
        break;

        case CSB_ICON_2:
        if(status_hidden->icon_2 == NULL){
            status_hidden->icon_2 = bitmap_layer_create(GRect(PEBBLE_WIDTH/2 - icon_width/2, height/2 - icon_width/2, icon_width, icon_width));
            bitmap_layer_set_background_color(status_hidden->icon_2 , GColorClear);
            layer_add_child(custom_status_bar_layer, bitmap_layer_get_layer(status_hidden->icon_2));
        }
        bitmap_layer_set_bitmap(status_hidden->icon_2, gbitmap);
        break;

        case CSB_ICON_3:
        if(status_hidden->icon_3 == NULL){
            status_hidden->icon_3 = bitmap_layer_create(GRect(PEBBLE_WIDTH * 7/10 - icon_width/2, height/2 - icon_width/2, icon_width, icon_width));
            bitmap_layer_set_background_color(status_hidden->icon_3 , GColorClear);
            layer_add_child(custom_status_bar_layer, bitmap_layer_get_layer(status_hidden->icon_3));
        }
        bitmap_layer_set_bitmap(status_hidden->icon_3, gbitmap);
        break;

        case CSB_ICON_4:
        if(status_hidden->icon_4 == NULL){
            status_hidden->icon_4 = bitmap_layer_create(GRect(PEBBLE_WIDTH * 9/10 - icon_width/2, height/2 - icon_width/2, icon_width, icon_width));
            bitmap_layer_set_background_color(status_hidden->icon_4 , GColorClear);
            layer_add_child(custom_status_bar_layer, bitmap_layer_get_layer(status_hidden->icon_4));
        }
        bitmap_layer_set_bitmap(status_hidden->icon_4, gbitmap);
        break;
    } 


}

void custom_status_bar_layer_set_bitmap_hidden(CustomStatusBarLayer* custom_status_bar_layer, CsbIconPosition position, bool hidden){

    CustomStatusBarLayerHidden* status_hidden = (CustomStatusBarLayerHidden*) layer_get_data(custom_status_bar_layer);

    switch(position){
        case CSB_ICON_0:
        layer_set_hidden(bitmap_layer_get_layer(status_hidden->icon_0), hidden);
        break;

        case CSB_ICON_1:
        layer_set_hidden(bitmap_layer_get_layer(status_hidden->icon_1), hidden);
        break;

        case CSB_ICON_2:
        layer_set_hidden(bitmap_layer_get_layer(status_hidden->icon_2), hidden);
        break;

        case CSB_ICON_3:
        layer_set_hidden(bitmap_layer_get_layer(status_hidden->icon_3), hidden);
        break;

        case CSB_ICON_4:
        layer_set_hidden(bitmap_layer_get_layer(status_hidden->icon_4), hidden);
        break;
    } 
}

void custom_status_bar_layer_set_all_text_hidden(CustomStatusBarLayer* custom_status_bar_layer, bool hidden){
    
    CustomStatusBarLayerHidden* status_hidden = (CustomStatusBarLayerHidden*) layer_get_data(custom_status_bar_layer);

    layer_set_hidden(text_layer_get_layer(status_hidden->left_text), hidden);
    layer_set_hidden(text_layer_get_layer(status_hidden->right_text), hidden);    
    layer_set_hidden(text_layer_get_layer(status_hidden->center_text), hidden);  

}

void custom_status_bar_layer_set_all_bitmaps_hidden(CustomStatusBarLayer* custom_status_bar_layer, bool hidden){

    CustomStatusBarLayerHidden* status_hidden = (CustomStatusBarLayerHidden*) layer_get_data(custom_status_bar_layer);

    layer_set_hidden(bitmap_layer_get_layer(status_hidden->icon_0), hidden);
    layer_set_hidden(bitmap_layer_get_layer(status_hidden->icon_1), hidden);
    layer_set_hidden(bitmap_layer_get_layer(status_hidden->icon_2), hidden);
    layer_set_hidden(bitmap_layer_get_layer(status_hidden->icon_3), hidden);
    layer_set_hidden(bitmap_layer_get_layer(status_hidden->icon_4), hidden);

}

static void update_proc(Layer* layer, GContext *context) {

    CustomStatusBarLayerHidden* status_hidden = (CustomStatusBarLayerHidden*) layer_get_data(layer);
    
    GRect bounds = layer_get_bounds(layer);

    graphics_context_set_fill_color(context, status_hidden->bar_colour);
    graphics_fill_rect(context, bounds, 0, GCornersAll);


}

