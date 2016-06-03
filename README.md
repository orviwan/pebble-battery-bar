# battery-bar

Pebble library for easily adding a battery bar to your app.

![Screenshot of library in action](info/animation.gif)

## Usage

````c
// This is a simple example, demonstrating the basic usage.

static BatteryBarLayer *s_battery_layer;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  s_battery_layer = battery_bar_layer_create(GRect(20, 20, 39, 10));
  layer_add_child(window_layer, s_battery_layer);
}

static void window_unload(Window *window) {
  battery_bar_layer_destroy(s_battery_layer);
}

````
