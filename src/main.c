#include <pebble.h>

Window *my_window;

//Bitmaps
static BitmapLayer *photoBitmapBackgroundLayer;
static GBitmap *photoBitmapLayer;


void handle_init(void) {
  my_window = window_create();
  window_set_background_color(my_window, GColorBlack);
  
  
  #if defined(PBL_COLOR)
    
    //Background bitmap
    photoBitmapLayer = gbitmap_create_with_resource(PBL_IF_ROUND_ELSE(RESOURCE_ID_TESTE_1, RESOURCE_ID_TESTE_1));
    photoBitmapBackgroundLayer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(141, 0), PBL_IF_ROUND_ELSE(50, 0), PBL_IF_ROUND_ELSE(50, 144), PBL_IF_ROUND_ELSE(50, 169)));
    
  #elif defined(PBL_BW)
    
    //Background bitmaps
    photoBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_TESTE_1);
    photoBitmapBackgroundLayer = bitmap_layer_create(GRect(0, 0, 144, 169));
    
  #endif
  
  
  //Adding bitmaps
  bitmap_layer_set_bitmap(photoBitmapBackgroundLayer, photoBitmapLayer);
  layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(photoBitmapBackgroundLayer));
  
  
  window_stack_push(my_window, true);
}

void handle_deinit(void) {
  
  //Deinit Bitmaps
  gbitmap_destroy(photoBitmapLayer);
  bitmap_layer_destroy(photoBitmapBackgroundLayer);
  
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}