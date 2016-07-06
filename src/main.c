#include <pebble.h>

Window *my_window;

//Bitmaps
static BitmapLayer *photoBitmapBackgroundLayer;
static BitmapLayer *normalBatteryBitmapBackgroundLayer;
static BitmapLayer *chargingBatteryBitmapBackgroundLayer;
static BitmapLayer *feetBitmapBackgroundLayer;
static GBitmap *photoBitmapLayer;
static GBitmap *normalBatteryBitmapLayer;
static GBitmap *chargingBatteryBitmapLayer;
static GBitmap *feetBitmapLayer;

//Rectangular text layer
TextLayer *rectBarHorizontal_layer;
TextLayer *rectBarVertical_layer;


void handle_init(void) {
  my_window = window_create();
  window_set_background_color(my_window, GColorBlack);
  
  #if defined(PBL_COLOR)
    
    //Bitmaps
    photoBitmapLayer = gbitmap_create_with_resource(PBL_IF_ROUND_ELSE(RESOURCE_ID_PHOTO1_ROUND, RESOURCE_ID_PHOTO1_COLOR));
    normalBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT1_ICON);
    chargingBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT2_ICON);
    feetBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_FEET_ICON);
    
    photoBitmapBackgroundLayer = bitmap_layer_create(GRect(0, 0, PBL_IF_ROUND_ELSE(180, 144), PBL_IF_ROUND_ELSE(180, 169)));
    normalBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(141, 0), PBL_IF_ROUND_ELSE(50, 0), PBL_IF_ROUND_ELSE(50, 144), PBL_IF_ROUND_ELSE(50, 169)));
    chargingBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(141, 0), PBL_IF_ROUND_ELSE(50, 0), PBL_IF_ROUND_ELSE(50, 144), PBL_IF_ROUND_ELSE(50, 169)));
    feetBitmapBackgroundLayer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(141, 0), PBL_IF_ROUND_ELSE(50, 0), PBL_IF_ROUND_ELSE(50, 144), PBL_IF_ROUND_ELSE(50, 169)));
    
    //Rectangular layers
    rectBarHorizontal_layer = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(132, 145), PBL_IF_ROUND_ELSE(180, 144), PBL_IF_ROUND_ELSE(48, 24)));
    rectBarVertical_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(122, 103), PBL_IF_ROUND_ELSE(55, 52), 41, 93));
    
    text_layer_set_background_color(rectBarHorizontal_layer,GColorDarkCandyAppleRed);
    text_layer_set_background_color(rectBarVertical_layer,GColorDarkCandyAppleRed);
    
    
  #elif defined(PBL_BW)
    
    //Bitmaps
    photoBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_PHOTO1_BW);
    normalBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT1_ICON);
    chargingBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT2_ICON);
    
    photoBitmapBackgroundLayer = bitmap_layer_create(GRect(0, 0, 144, 169));
    normalBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(0, 0, 144, 169));
    chargingBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(0, 0, 144, 169));
    
    //Rectangular layers
    rectBarHorizontal_layer = text_layer_create(GRect(0, 145, 144, 24));
    rectBarVertical_layer = text_layer_create(GRect(103, 52, 41, 93));
    
    text_layer_set_background_color(rectBarHorizontal_layer,GColorWhite);
    text_layer_set_background_color(rectBarVertical_layer,GColorWhite);
    
    
  #endif
  
  
  //Adding background bitmaps
  bitmap_layer_set_bitmap(photoBitmapBackgroundLayer, photoBitmapLayer);
  layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(photoBitmapBackgroundLayer));
  
  
  //Add rectangle Layers to window
  layer_add_child(window_get_root_layer(my_window), (Layer*) rectBarHorizontal_layer);
  layer_add_child(window_get_root_layer(my_window), (Layer*) rectBarVertical_layer);
  
  
  //Adding aditional bitmaps
  bitmap_layer_set_bitmap(normalBatteryBitmapBackgroundLayer, normalBatteryBitmapLayer);
  bitmap_layer_set_bitmap(chargingBatteryBitmapBackgroundLayer, chargingBatteryBitmapLayer);
  bitmap_layer_set_bitmap(feetBitmapBackgroundLayer, feetBitmapLayer);
  layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(normalBatteryBitmapBackgroundLayer));
  layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(chargingBatteryBitmapBackgroundLayer));
  layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(feetBitmapBackgroundLayer));
  
  
  
  window_stack_push(my_window, true);
}

void handle_deinit(void) {
  
  
  //Deinit Bitmaps
  gbitmap_destroy(photoBitmapLayer);
  gbitmap_destroy(normalBatteryBitmapLayer);
  gbitmap_destroy(chargingBatteryBitmapLayer);
  gbitmap_destroy(feetBitmapLayer);
  bitmap_layer_destroy(photoBitmapBackgroundLayer);
  bitmap_layer_destroy(normalBatteryBitmapBackgroundLayer);
  bitmap_layer_destroy(chargingBatteryBitmapBackgroundLayer);
  bitmap_layer_destroy(feetBitmapBackgroundLayer);
  
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}