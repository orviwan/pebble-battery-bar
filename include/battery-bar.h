#pragma once
#include <pebble.h>

typedef Layer BatteryBarLayer;

BatteryBarLayer* battery_bar_layer_create();
void battery_bar_layer_destroy(BatteryBarLayer *battery_bar_layer);
void battery_bar_set_percent_hidden(bool hidden);
void battery_bar_set_icon_hidden(bool hidden);
void battery_bar_set_colors(GColor normal, GColor warning, GColor danger, GColor charging);
void battery_bar_set_position(GPoint position);
