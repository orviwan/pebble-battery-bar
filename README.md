# battery-bar

Pebble library for easily adding a battery bar to your app.

![Screenshot of library in action](info/animation.gif)

## Usage

````c
// This is a simple example, demonstrating the basic usage.

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  // Apply the default settings
  battery_bar_init_defaults();

  // Position the battery bar
  battery_bar.container_top = 50;
  battery_bar.container_left = 50;

  // Initialize the battery bar
  battery_bar_init(window_layer);
}

static void window_unload(Window *window) {

  // Tidy up
  battery_bar_deinit();
}
````

## Settings Documentation

X coordinate for the container layer

    battery_bar.container_left = 2;

Y coordinate for the container layer

    battery_bar.container_top = 2;

Hide the percentage text

    battery_bar.hide_percent = false;

Hide the battery icon

    battery_bar.hide_icon = false;

Change the colors for the various states.

    battery_bar.color_normal = GColorWhite;
    battery_bar.color_warning = GColorOrange;
    battery_bar.color_danger = GColorRed;
    battery_bar.color_charging = GColorYellow;
