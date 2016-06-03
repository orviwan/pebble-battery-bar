#pragma once
#include <pebble.h>

typedef Layer BatteryBarLayer;

static BatteryBarLayer* battery_bar_layer_create(GRect frame);
static void battery_bar_layer_destroy(BatteryBarLayer *battery_bar_layer);
