//FRAKKING TOASTER!
#include <pebble.h>
#include <math.h>

#define SETTINGS_KEY 1

Window *my_window;

//Fonts
static GFont bsg_font;

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
TextLayer *rectBatteryStatus_layer;

//Text Layers
TextLayer *time1Text_layer;
TextLayer *time2Text_layer;
TextLayer *batteryText_layer;
TextLayer *stepsText_layer;
TextLayer *dateText_layer;

//Complications booleans struct
// A structure containing settings
typedef struct ClaySettings {
  bool displayBattery;
  bool displayDate;
  bool displaySteps;
} __attribute__((__packed__)) ClaySettings;

ClaySettings settings;

//Other vars
char stepsStatus[20];
char batteryStatus[5];
float batteryBarCalculation;
int batteryStatusBarSize;
int backgroundTimeControl = 1;
int currentBackgroundImage = 1;

//Update background image
static void updateImage(){
  
  if(currentBackgroundImage >= 3){
      currentBackgroundImage = 0;
  }
  currentBackgroundImage++;
  
  
  if(backgroundTimeControl >= 5){
    
    //Change background image
    gbitmap_destroy(photoBitmapLayer);
    
    switch (currentBackgroundImage){
      case 1:
        photoBitmapLayer = gbitmap_create_with_resource(PBL_IF_BW_ELSE(RESOURCE_ID_PHOTO1_BW,PBL_IF_ROUND_ELSE(RESOURCE_ID_PHOTO1_ROUND, RESOURCE_ID_PHOTO1_COLOR)));
        layer_set_frame(text_layer_get_layer(rectBarVertical_layer), GRect(PBL_IF_BW_ELSE(103,PBL_IF_ROUND_ELSE(122, 103)),PBL_IF_BW_ELSE(91,PBL_IF_ROUND_ELSE(55, 65)),PBL_IF_BW_ELSE(41,41),PBL_IF_BW_ELSE(93,93)));
        
        layer_set_frame(text_layer_get_layer(time1Text_layer), GRect(PBL_IF_BW_ELSE(103,PBL_IF_ROUND_ELSE(122, 103)),PBL_IF_BW_ELSE(91,PBL_IF_ROUND_ELSE(55, 65)),PBL_IF_BW_ELSE(41,41),PBL_IF_BW_ELSE(24,24)));
        layer_set_frame(text_layer_get_layer(time2Text_layer), GRect(PBL_IF_BW_ELSE(103,PBL_IF_ROUND_ELSE(122, 103)),PBL_IF_BW_ELSE(117,PBL_IF_ROUND_ELSE(81, 91)),PBL_IF_BW_ELSE(41,41),PBL_IF_BW_ELSE(24,24)));
        layer_set_frame(text_layer_get_layer(dateText_layer), GRect(PBL_IF_BW_ELSE(62,PBL_IF_ROUND_ELSE(122, 103)),PBL_IF_BW_ELSE(146,PBL_IF_ROUND_ELSE(104, 114)),PBL_IF_BW_ELSE(80,41),PBL_IF_BW_ELSE(22,36)));
      
      break;
      case 2:
        photoBitmapLayer = gbitmap_create_with_resource(PBL_IF_BW_ELSE(RESOURCE_ID_PHOTO2_BW,PBL_IF_ROUND_ELSE(RESOURCE_ID_PHOTO2_ROUND, RESOURCE_ID_PHOTO2_COLOR)));
        layer_set_frame(text_layer_get_layer(rectBarVertical_layer), GRect(PBL_IF_BW_ELSE(0,PBL_IF_ROUND_ELSE(17, 0)),PBL_IF_BW_ELSE(91,PBL_IF_ROUND_ELSE(55, 65)),PBL_IF_BW_ELSE(41,41),PBL_IF_BW_ELSE(93,93)));
      
        layer_set_frame(text_layer_get_layer(time1Text_layer), GRect(PBL_IF_BW_ELSE(0,PBL_IF_ROUND_ELSE(17, 0)),PBL_IF_BW_ELSE(91,PBL_IF_ROUND_ELSE(55, 65)),PBL_IF_BW_ELSE(41,41),PBL_IF_BW_ELSE(24,24)));
        layer_set_frame(text_layer_get_layer(time2Text_layer), GRect(PBL_IF_BW_ELSE(0,PBL_IF_ROUND_ELSE(17, 0)),PBL_IF_BW_ELSE(117,PBL_IF_ROUND_ELSE(81, 91)),PBL_IF_BW_ELSE(41,41),PBL_IF_BW_ELSE(24,24)));
        layer_set_frame(text_layer_get_layer(dateText_layer), GRect(PBL_IF_BW_ELSE(62,PBL_IF_ROUND_ELSE(17, 0)),PBL_IF_BW_ELSE(146,PBL_IF_ROUND_ELSE(104, 114)),PBL_IF_BW_ELSE(80,41),PBL_IF_BW_ELSE(22,36)));
      
      break;
      case 3:
        photoBitmapLayer = gbitmap_create_with_resource(PBL_IF_BW_ELSE(RESOURCE_ID_PHOTO3_BW,PBL_IF_ROUND_ELSE(RESOURCE_ID_PHOTO3_ROUND, RESOURCE_ID_PHOTO3_COLOR)));
        layer_set_frame(text_layer_get_layer(rectBarVertical_layer), GRect(PBL_IF_BW_ELSE(103,PBL_IF_ROUND_ELSE(122, 103)),PBL_IF_BW_ELSE(91,PBL_IF_ROUND_ELSE(55, 65)),PBL_IF_BW_ELSE(41,41),PBL_IF_BW_ELSE(93,93)));
      
        layer_set_frame(text_layer_get_layer(time1Text_layer), GRect(PBL_IF_BW_ELSE(103,PBL_IF_ROUND_ELSE(122, 103)),PBL_IF_BW_ELSE(91,PBL_IF_ROUND_ELSE(55, 65)),PBL_IF_BW_ELSE(41,41),PBL_IF_BW_ELSE(24,24)));
        layer_set_frame(text_layer_get_layer(time2Text_layer), GRect(PBL_IF_BW_ELSE(103,PBL_IF_ROUND_ELSE(122, 103)),PBL_IF_BW_ELSE(117,PBL_IF_ROUND_ELSE(81, 91)),PBL_IF_BW_ELSE(41,41),PBL_IF_BW_ELSE(24,24)));
        layer_set_frame(text_layer_get_layer(dateText_layer), GRect(PBL_IF_BW_ELSE(62,PBL_IF_ROUND_ELSE(122, 103)),PBL_IF_BW_ELSE(146,PBL_IF_ROUND_ELSE(104, 114)),PBL_IF_BW_ELSE(80,41),PBL_IF_BW_ELSE(22,36)));
      
      break;
    }
    
    //bitmap_layer_set_bitmap(photoBitmapBackgroundLayer, photoBitmapLayer);
    
    backgroundTimeControl = 0;
    
  }
  backgroundTimeControl++;
  
  
}


//Steps count update

static void health_handler(HealthEventType event, void *context) {
  
  if(settings.displaySteps){
  
    HealthMetric metric = HealthMetricStepCount;
    time_t start = time_start_of_today();
    time_t end = time(NULL);
    
    int totalSteps;
    
    HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, 
    start, end);
    
    if(mask & HealthServiceAccessibilityMaskAvailable) {
      
      totalSteps = (int)health_service_sum_today(metric);
      
      snprintf(stepsStatus,20, "%d", totalSteps);
      
      text_layer_set_text(stepsText_layer, stepsStatus);
      
      //Test only
      //text_layer_set_text(stepsText_layer, "999999");
      
    }
    
    layer_set_hidden(bitmap_layer_get_layer(feetBitmapBackgroundLayer),false);
    layer_set_hidden(text_layer_get_layer(stepsText_layer),false);
    
  }else{
    
    layer_set_hidden(bitmap_layer_get_layer(feetBitmapBackgroundLayer),true);
    layer_set_hidden(text_layer_get_layer(stepsText_layer),true);
    
  }
  
  
}

//Battery update
static void updateBattery() {
  
  if(settings.displayBattery){
  
    //Battery status
    BatteryChargeState state = battery_state_service_peek();
    int statusValue = (int)state.charge_percent;
    snprintf(batteryStatus,5, "%d%%", statusValue);
    text_layer_set_text(batteryText_layer, batteryStatus);
    
    batteryBarCalculation = statusValue*19;
    batteryBarCalculation = batteryBarCalculation/100;
    
    batteryStatusBarSize = roundf(batteryBarCalculation);
    
    //Change size
    text_layer_set_size(rectBatteryStatus_layer, GSize(batteryStatusBarSize,5));
    
    if(statusValue <= 20){
      text_layer_set_background_color(rectBatteryStatus_layer, PBL_IF_COLOR_ELSE(GColorOrange,GColorLightGray));
    }else{
      text_layer_set_background_color(rectBatteryStatus_layer, PBL_IF_COLOR_ELSE(GColorYellow,GColorWhite));
    }
    
    //Check if battery is charging
    if(state.is_charging){
      //Hide normal battery icon and show charging battery bitmap
      
      layer_set_hidden(bitmap_layer_get_layer(normalBatteryBitmapBackgroundLayer),true);
      layer_set_hidden(bitmap_layer_get_layer(chargingBatteryBitmapBackgroundLayer),false);
      layer_set_hidden(text_layer_get_layer(rectBatteryStatus_layer),true);
      layer_set_hidden(text_layer_get_layer(batteryText_layer),true);
      
    }else{
      //You know...
      
      layer_set_hidden(bitmap_layer_get_layer(normalBatteryBitmapBackgroundLayer),false);
      layer_set_hidden(bitmap_layer_get_layer(chargingBatteryBitmapBackgroundLayer),true);
      layer_set_hidden(text_layer_get_layer(rectBatteryStatus_layer),false);
      layer_set_hidden(text_layer_get_layer(batteryText_layer),false);
      
    }
    
  }else{
    //hide elements
    layer_set_hidden(bitmap_layer_get_layer(normalBatteryBitmapBackgroundLayer),true);
    layer_set_hidden(bitmap_layer_get_layer(chargingBatteryBitmapBackgroundLayer),true);
    layer_set_hidden(text_layer_get_layer(rectBatteryStatus_layer),true);
    layer_set_hidden(text_layer_get_layer(batteryText_layer),true);
    
  }
  
  
}

static void battery_state_handler(BatteryChargeState charge) {
  updateBattery();
}



//Time loop
static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
  // Write the current hours and minutes into a buffer
  static char H_buffer[8];
  static char M_buffer[8];
  
  strftime(H_buffer, sizeof(H_buffer), clock_is_24h_style() ?
                                          "%H" : "%I", tick_time);
  strftime(M_buffer, sizeof(M_buffer), clock_is_24h_style() ?
                                          "%M" : "%M", tick_time);
  
  // Display this time on the TextLayer
  text_layer_set_text(time1Text_layer, H_buffer);
  text_layer_set_text(time2Text_layer, M_buffer);
  
  
  
  if(settings.displayDate){
  
    //date
    static char date_buffer[18];
    
    #if defined(PBL_COLOR)
      strftime(date_buffer, sizeof(date_buffer), "%a\n%d %b", tick_time);
    #elif defined(PBL_BW)
      strftime(date_buffer, sizeof(date_buffer), "%a, %d %b", tick_time);
    #endif
    
    // Show date
    text_layer_set_text(dateText_layer, date_buffer);
  }else{
    text_layer_set_text(dateText_layer, "");
  }
  
  //update background
  updateImage();
  
  
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}
//End of time loop





//Clay settings

static void prv_default_settings() {
  settings.displayBattery = true;
  settings.displayDate = true;
  settings.displaySteps = true;
}

// Read settings from persistent storage
static void prv_load_settings() {
  // Load the default settings
  prv_default_settings();
  // Read settings from persistent storage, if they exist
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

// Save the settings to persistent storage
static void prv_save_settings() {
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}


static void prv_inbox_received_handler(DictionaryIterator *iter, void *context) {
  
  // Read boolean preferences
  Tuple *toggleBattery = dict_find(iter, MESSAGE_KEY_showBattery);
  if(toggleBattery) {
    settings.displayBattery = toggleBattery->value->int32 == 1;
  }
  
  Tuple *toggleDate = dict_find(iter, MESSAGE_KEY_showDate);
  if(toggleDate) {
    settings.displayDate = toggleDate->value->int32 == 1;
  }
  
  Tuple *toggleSteps = dict_find(iter, MESSAGE_KEY_showSteps);
  if(toggleSteps) {
    settings.displaySteps = toggleSteps->value->int32 == 1;
  }
  
  updateBattery();
  update_time();
  
  if(!settings.displaySteps){
    layer_set_hidden(bitmap_layer_get_layer(feetBitmapBackgroundLayer),true);
    layer_set_hidden(text_layer_get_layer(stepsText_layer),true);
  }else{
    layer_set_hidden(bitmap_layer_get_layer(feetBitmapBackgroundLayer),false);
    layer_set_hidden(text_layer_get_layer(stepsText_layer),false);
  }
  
  
  
  
  
  // Save the new settings to persistent storage
  prv_save_settings();
  
}

void prv_init(void) {
  
  //Load default or stored settings
  prv_load_settings();
  
  // Open AppMessage connection
  app_message_register_inbox_received(prv_inbox_received_handler);
  app_message_open(128, 128);
}






void handle_init(void) {
  my_window = window_create();
  window_set_background_color(my_window, GColorBlack);
  
  
  
  //Font
  bsg_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_BSG_FONT_22));
  
  
  
  #if defined(PBL_COLOR)
    
    //Bitmaps
    photoBitmapLayer = gbitmap_create_with_resource(PBL_IF_ROUND_ELSE(RESOURCE_ID_PHOTO1_ROUND, RESOURCE_ID_PHOTO1_COLOR));
    normalBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT1_ICON);
    chargingBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT2_ICON);
    feetBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_FEET_ICON);
    
    photoBitmapBackgroundLayer = bitmap_layer_create(GRect(0, 0, PBL_IF_ROUND_ELSE(180, 144), PBL_IF_ROUND_ELSE(180, 169)));
    normalBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(39, 4), PBL_IF_ROUND_ELSE(138, 151), 27, 11));
    chargingBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(39, 4), PBL_IF_ROUND_ELSE(138, 151), 27, 11));
    feetBitmapBackgroundLayer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(105, 115), PBL_IF_ROUND_ELSE(134, 147), 24, 15));
  
    bitmap_layer_set_background_color(normalBatteryBitmapBackgroundLayer,GColorClear);
    bitmap_layer_set_background_color(chargingBatteryBitmapBackgroundLayer,GColorClear);
    bitmap_layer_set_background_color(feetBitmapBackgroundLayer,GColorClear);
    
    bitmap_layer_set_compositing_mode(normalBatteryBitmapBackgroundLayer, GCompOpSet);
    bitmap_layer_set_compositing_mode(chargingBatteryBitmapBackgroundLayer, GCompOpSet);
    bitmap_layer_set_compositing_mode(feetBitmapBackgroundLayer, GCompOpSet);
    
    //Rectangular layers
    rectBarHorizontal_layer = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(132, 145), PBL_IF_ROUND_ELSE(180, 144), PBL_IF_ROUND_ELSE(48, 24)));
    rectBarVertical_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(122, 103), PBL_IF_ROUND_ELSE(55, 65), 41, 93));
    rectBatteryStatus_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(42, 7), PBL_IF_ROUND_ELSE(141, 154), 19, 5));
    
    text_layer_set_background_color(rectBarHorizontal_layer,GColorDarkCandyAppleRed);
    text_layer_set_background_color(rectBarVertical_layer,GColorDarkCandyAppleRed);
    text_layer_set_background_color(rectBatteryStatus_layer,GColorDarkCandyAppleRed);
    
    //Text Layers
    time1Text_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(122, 103), PBL_IF_ROUND_ELSE(55, 65), 41, 24));
    time2Text_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(122, 103), PBL_IF_ROUND_ELSE(81, 91), 41, 24));
    dateText_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(122, 103), PBL_IF_ROUND_ELSE(104, 114), 41, 36));
    batteryText_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(36, 32), PBL_IF_ROUND_ELSE(146, 146), 32, 22));
    stepsText_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(92, 62), PBL_IF_ROUND_ELSE(146, 146), 51, 22));
    
    text_layer_set_text_color(time1Text_layer, GColorYellow);
    text_layer_set_text_color(time2Text_layer, GColorYellow);
    text_layer_set_text_color(dateText_layer, GColorYellow);
    text_layer_set_text_color(batteryText_layer, GColorYellow);
    text_layer_set_text_color(stepsText_layer, GColorYellow);
  
    text_layer_set_background_color(time1Text_layer,GColorClear);
    text_layer_set_background_color(time2Text_layer,GColorClear);
    text_layer_set_background_color(dateText_layer,GColorClear);
    text_layer_set_background_color(batteryText_layer,GColorClear);
    text_layer_set_background_color(stepsText_layer,GColorClear);
    
    
  #elif defined(PBL_BW)
    
    //Bitmaps
    photoBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_PHOTO1_BW);
    normalBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT1_ICON);
    chargingBatteryBitmapLayer = gbitmap_create_with_resource(RESOURCE_ID_BAT2_ICON);
    
    photoBitmapBackgroundLayer = bitmap_layer_create(GRect(0, 0, 144, 169));
    normalBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(4, 151, 27, 11));
    chargingBatteryBitmapBackgroundLayer = bitmap_layer_create(GRect(4, 151, 27, 11));
    
    bitmap_layer_set_background_color(normalBatteryBitmapBackgroundLayer,GColorClear);
    bitmap_layer_set_background_color(chargingBatteryBitmapBackgroundLayer,GColorClear);
    
    bitmap_layer_set_compositing_mode(normalBatteryBitmapBackgroundLayer, GCompOpSet);
    bitmap_layer_set_compositing_mode(chargingBatteryBitmapBackgroundLayer, GCompOpSet);
    
    //Rectangular layers
    rectBarHorizontal_layer = text_layer_create(GRect(0, 145, 144, 24));
    rectBarVertical_layer = text_layer_create(GRect(103, 91, 41, 93));
    rectBatteryStatus_layer = text_layer_create(GRect(7, 154, 19, 5));
    
    text_layer_set_background_color(rectBarHorizontal_layer,GColorBlack);
    text_layer_set_background_color(rectBarVertical_layer,GColorBlack);
    text_layer_set_background_color(rectBatteryStatus_layer,GColorWhite);
  
    //Text Layers
    time1Text_layer = text_layer_create(GRect(103, 94, 41, 24));
    time2Text_layer = text_layer_create(GRect(103, 120, 41, 24));
    dateText_layer = text_layer_create(GRect(62, 146, 80, 22));
    batteryText_layer = text_layer_create(GRect(32, 146, 32, 22));
    stepsText_layer = text_layer_create(GRect(63, 146, 51, 22));
    
    text_layer_set_text_color(time1Text_layer, GColorWhite);
    text_layer_set_text_color(time2Text_layer, GColorWhite);
    text_layer_set_text_color(dateText_layer, GColorWhite);
    text_layer_set_text_color(batteryText_layer, GColorWhite);
    
    text_layer_set_background_color(time1Text_layer,GColorClear);
    text_layer_set_background_color(time2Text_layer,GColorClear);
    text_layer_set_background_color(dateText_layer,GColorClear);
    text_layer_set_background_color(batteryText_layer,GColorClear);
    
    
    
  #endif
  
  
  
  
  //Adding background bitmaps
  bitmap_layer_set_bitmap(photoBitmapBackgroundLayer, photoBitmapLayer);
  layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(photoBitmapBackgroundLayer));
  
  
  //Add rectangle Layers to window
  layer_add_child(window_get_root_layer(my_window), (Layer*) rectBarHorizontal_layer);
  layer_add_child(window_get_root_layer(my_window), (Layer*) rectBarVertical_layer);
  layer_add_child(window_get_root_layer(my_window), (Layer*) rectBatteryStatus_layer);
  
  //Adding aditional bitmaps
  bitmap_layer_set_bitmap(normalBatteryBitmapBackgroundLayer, normalBatteryBitmapLayer);
  bitmap_layer_set_bitmap(chargingBatteryBitmapBackgroundLayer, chargingBatteryBitmapLayer);
  
  layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(normalBatteryBitmapBackgroundLayer));
  layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(chargingBatteryBitmapBackgroundLayer));
  
  
  //Adding text layers
  text_layer_set_font(time1Text_layer, bsg_font);
  text_layer_set_font(time2Text_layer, bsg_font);
  text_layer_set_font(dateText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_font(batteryText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  
  text_layer_set_text_alignment(time1Text_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(time2Text_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(dateText_layer, PBL_IF_BW_ELSE(GTextAlignmentRight,GTextAlignmentCenter));
  text_layer_set_text_alignment(batteryText_layer, GTextAlignmentCenter);
  
  
  
  layer_add_child(window_get_root_layer(my_window), (Layer*) time1Text_layer);
  layer_add_child(window_get_root_layer(my_window), (Layer*) time2Text_layer);
  layer_add_child(window_get_root_layer(my_window), (Layer*) dateText_layer);
  layer_add_child(window_get_root_layer(my_window), (Layer*) batteryText_layer);
  
  #if defined(PBL_COLOR)
    
    //Only color bitmaps
    bitmap_layer_set_bitmap(feetBitmapBackgroundLayer, feetBitmapLayer);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(feetBitmapBackgroundLayer));
    
    //Only color texts
    text_layer_set_font(stepsText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_text_alignment(stepsText_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentRight));
    layer_add_child(window_get_root_layer(my_window), (Layer*) stepsText_layer);
  
  #endif
  
  
  
  //Time events
  update_time();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  //Battery events
  updateBattery();
  battery_state_service_subscribe(battery_state_handler);
  
  //Steps counting elements
  #if defined(PBL_HEALTH)
    
    if(health_service_events_subscribe(health_handler, NULL)) {
      
      //Test only
      //text_layer_set_text(stepsText_layer, "9999");
  
    }
      
  #endif
  
  
  
  
  
  window_stack_push(my_window, true);
}

void handle_deinit(void) {
  
  //Fonts
static GFont bsg_font;
  
  //Deinit text Layers
  text_layer_destroy(time1Text_layer);
  text_layer_destroy(time2Text_layer);
  text_layer_destroy(batteryText_layer);
  text_layer_destroy(stepsText_layer);
  text_layer_destroy(dateText_layer);
  text_layer_destroy(rectBarHorizontal_layer);
  text_layer_destroy(rectBarVertical_layer);
  text_layer_destroy(rectBatteryStatus_layer);
  
  //Deinit Bitmaps
  gbitmap_destroy(photoBitmapLayer);
  gbitmap_destroy(normalBatteryBitmapLayer);
  gbitmap_destroy(chargingBatteryBitmapLayer);
  gbitmap_destroy(feetBitmapLayer);
  bitmap_layer_destroy(photoBitmapBackgroundLayer);
  bitmap_layer_destroy(normalBatteryBitmapBackgroundLayer);
  bitmap_layer_destroy(chargingBatteryBitmapBackgroundLayer);
  bitmap_layer_destroy(feetBitmapBackgroundLayer);
  
  //Deinit fonts
  fonts_unload_custom_font(bsg_font);
  
  //Unsubscribe events
  battery_state_service_unsubscribe();
  tick_timer_service_unsubscribe();
  health_service_events_unsubscribe();
  
  window_destroy(my_window);
  
  //So say we all!
  
}

int main(void) {
  prv_init();
  handle_init();
  app_event_loop();
  handle_deinit();
}