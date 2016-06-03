#include <pebble.h>
#include "battery-bar.h"

void battery_bar_battery_update(BatteryChargeState charge_state) {
  battery_bar.charge_percent = charge_state.charge_percent;
  battery_bar.is_charging = charge_state.is_charging;
  if(battery_bar.charge_percent == 0) {
    battery_bar.charge_percent = 1;
  }

  battery_bar.color_state = battery_bar.color_normal;
  if(battery_bar.charge_percent < 20) {
    battery_bar.color_state = battery_bar.color_danger;
  } else if(battery_bar.charge_percent < 30) {
    battery_bar.color_state = battery_bar.color_warning;
  }

  static char s_txt[5];
  snprintf(s_txt, sizeof(s_txt), "%u%%", battery_bar.charge_percent);
  text_layer_set_text(s_battery_percent_layer, s_txt);
  text_layer_set_text_color(s_battery_percent_layer, battery_bar.color_state);

  layer_mark_dirty(s_battery_icon_layer);
}

void battery_bar_layer_update_callback(Layer *battery_layer, GContext* ctx) {
  graphics_context_set_stroke_color(ctx, battery_bar.color_state);
  graphics_draw_rect(ctx, GRect(0, 0, 16, 9));
  graphics_draw_rect(ctx, GRect(15, 2, 2, 5));

  graphics_context_set_stroke_color(ctx, battery_bar.color_state);
  graphics_context_set_fill_color(ctx, battery_bar.color_state);

  if(battery_bar.is_charging) {
    graphics_context_set_stroke_color(ctx, battery_bar.color_charging);
    gpath_draw_outline(ctx, s_battery_bolt_path_ptr);
  } else {
    uint8_t width = ((battery_bar.charge_percent / 100.0) * 11.0);
    if(width < 12) {
      width++;
    }
    graphics_fill_rect(ctx, GRect(2, 2, width, 5), 0, GCornerNone);
  }

}

void battery_bar_init_defaults() {
  battery_bar.percent_font = fonts_get_system_font(FONT_KEY_GOTHIC_09);
  battery_bar.container_left = 2;
  battery_bar.container_top = 2;
  battery_bar.container_layer_rect = GRect(battery_bar.container_left, battery_bar.container_top, 39, 10);
  battery_bar.percent_layer_rect = GRect(0, -1, 21, 10);
  battery_bar.icon_layer_rect = GRect(22, 0, 17, 9);
  battery_bar.hide_percent = false;
  battery_bar.hide_icon = false;
  #ifdef PBL_COLOR
    battery_bar.color_normal = GColorWhite;
    battery_bar.color_warning = GColorOrange;
    battery_bar.color_danger = GColorRed;
    battery_bar.color_charging = GColorYellow;
  #else
    battery_bar.color_normal = GColorWhite;
    battery_bar.color_warning = GColorWhite;
    battery_bar.color_danger = GColorWhite;
    battery_bar.color_charging = GColorWhite;
  #endif
}

void battery_bar_init(Layer *root_layer) {
  if(!battery_bar._defaults_loaded) {
    battery_bar_init_defaults();
  }

  s_battery_container_layer = layer_create(battery_bar.container_layer_rect);
  layer_add_child(root_layer, s_battery_container_layer);

  s_battery_percent_layer = text_layer_create(battery_bar.percent_layer_rect);
  text_layer_set_background_color(s_battery_percent_layer, GColorClear);
  text_layer_set_text_color(s_battery_percent_layer, battery_bar.color_normal);
  text_layer_set_text_alignment(s_battery_percent_layer, GTextAlignmentRight);
  text_layer_set_font(s_battery_percent_layer, battery_bar.percent_font);
  layer_add_child(s_battery_container_layer, text_layer_get_layer(s_battery_percent_layer));
  layer_set_hidden(text_layer_get_layer(s_battery_percent_layer), battery_bar.hide_percent);

  s_battery_bolt_path_ptr = gpath_create(&s_battery_bolt_path_info);

  s_battery_icon_layer = layer_create(battery_bar.icon_layer_rect);
  layer_set_update_proc(s_battery_icon_layer, battery_bar_layer_update_callback);
  layer_add_child(s_battery_container_layer, s_battery_icon_layer);
  layer_set_hidden(s_battery_icon_layer, battery_bar.hide_icon);

  battery_bar_battery_update(battery_state_service_peek());
  battery_state_service_subscribe(&battery_bar_battery_update);
}

void battery_bar_deinit() {
  battery_state_service_unsubscribe();

  gpath_destroy(s_battery_bolt_path_ptr);
  s_battery_bolt_path_ptr = NULL;

  text_layer_destroy(s_battery_percent_layer);

  layer_remove_from_parent(s_battery_bolt_layer);
  layer_remove_from_parent(s_battery_icon_layer);
  layer_remove_from_parent(s_battery_container_layer);

  layer_destroy(s_battery_bolt_layer);
  layer_destroy(s_battery_icon_layer);
  layer_destroy(s_battery_container_layer);
}
