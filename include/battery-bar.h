#pragma once
#include <pebble.h>

typedef struct BatteryBarSettings {
  bool _defaults_loaded;
  bool is_charging;
  uint8_t charge_percent;
  int8_t container_top;
  int8_t container_left;
  GFont percent_font;
  GRect container_layer_rect;
  GRect percent_layer_rect;
  GRect icon_layer_rect;
  bool hide_percent;
  bool hide_icon;
  GColor color_normal;
  GColor color_warning;
  GColor color_danger;
  GColor color_charging;
  GColor color_state;
} BatteryBarSettings;
BatteryBarSettings battery_bar;

static Layer *s_battery_container_layer, *s_battery_icon_layer, *s_battery_bolt_layer;
static TextLayer *s_battery_percent_layer;

static GPath *s_battery_bolt_path_ptr = NULL;

static GPathInfo s_battery_bolt_path_info = {
  .num_points = 13,
  .points = (GPoint []) {{4,4},{6,4},{6,3},{8,3},{8,2},{8,4},{12,4},{10,4},{10,5},{8,5},{8,6},{8,4},{11,4}}
};

void battery_bar_battery_update(BatteryChargeState charge_state);
void battery_bar_layer_update_callback(Layer *battery_layer, GContext* ctx);
void battery_bar_init_defaults();
void battery_bar_init(Layer *root_layer);
void battery_bar_deinit();
