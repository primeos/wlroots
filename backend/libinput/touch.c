#include <stdlib.h>
#include <assert.h>
#include <libinput.h>
#include <wlr/backend/session.h>
#include <wlr/types/wlr_input_device.h>
#include <wlr/interfaces/wlr_touch.h>
#include <wlr/util/log.h>
#include "backend/libinput.h"

struct wlr_touch *wlr_libinput_touch_create(
		struct libinput_device *libinput_dev) {
	assert(libinput_dev);
	struct wlr_touch *wlr_touch = calloc(1, sizeof(struct wlr_touch));
	if (!wlr_touch) {
		wlr_log(L_ERROR, "Unable to allocate wlr_touch");
		return NULL;
	}
	wlr_touch_init(wlr_touch, NULL);
	return wlr_touch;
}

void handle_touch_down(struct libinput_event *event,
		struct libinput_device *libinput_dev) {
	struct wlr_input_device *wlr_dev =
		get_appropriate_device(WLR_INPUT_DEVICE_TOUCH, libinput_dev);
	if (!wlr_dev) {
		wlr_log(L_DEBUG, "Got a touch event for a device with no touch?");
		return;
	}
	struct libinput_event_touch *tevent =
		libinput_event_get_touch_event(event);
	struct wlr_event_touch_down wlr_event = { 0 };
	wlr_event.device = wlr_dev;
	wlr_event.time_msec =
		usec_to_msec(libinput_event_touch_get_time_usec(tevent));
	wlr_event.touch_id = libinput_event_touch_get_slot(tevent);
	wlr_event.x_mm = libinput_event_touch_get_x(tevent);
	wlr_event.y_mm = libinput_event_touch_get_y(tevent);
	libinput_device_get_size(libinput_dev, &wlr_event.width_mm, &wlr_event.height_mm);
	wl_signal_emit(&wlr_dev->touch->events.down, &wlr_event);
}

void handle_touch_up(struct libinput_event *event,
		struct libinput_device *libinput_dev) {
	struct wlr_input_device *wlr_dev =
		get_appropriate_device(WLR_INPUT_DEVICE_TOUCH, libinput_dev);
	if (!wlr_dev) {
		wlr_log(L_DEBUG, "Got a touch event for a device with no touch?");
		return;
	}
	struct libinput_event_touch *tevent =
		libinput_event_get_touch_event(event);
	struct wlr_event_touch_up wlr_event = { 0 };
	wlr_event.device = wlr_dev;
	wlr_event.time_msec =
		usec_to_msec(libinput_event_touch_get_time_usec(tevent));
	wlr_event.touch_id = libinput_event_touch_get_slot(tevent);
	wl_signal_emit(&wlr_dev->touch->events.up, &wlr_event);
}

void handle_touch_motion(struct libinput_event *event,
		struct libinput_device *libinput_dev) {
	struct wlr_input_device *wlr_dev =
		get_appropriate_device(WLR_INPUT_DEVICE_TOUCH, libinput_dev);
	if (!wlr_dev) {
		wlr_log(L_DEBUG, "Got a touch event for a device with no touch?");
		return;
	}
	struct libinput_event_touch *tevent =
		libinput_event_get_touch_event(event);
	struct wlr_event_touch_motion wlr_event = { 0 };
	wlr_event.device = wlr_dev;
	wlr_event.time_msec =
		usec_to_msec(libinput_event_touch_get_time_usec(tevent));
	wlr_event.touch_id = libinput_event_touch_get_slot(tevent);
	wlr_event.x_mm = libinput_event_touch_get_x(tevent);
	wlr_event.y_mm = libinput_event_touch_get_y(tevent);
	libinput_device_get_size(libinput_dev, &wlr_event.width_mm, &wlr_event.height_mm);
	wl_signal_emit(&wlr_dev->touch->events.motion, &wlr_event);
}

void handle_touch_cancel(struct libinput_event *event,
		struct libinput_device *libinput_dev) {
	struct wlr_input_device *wlr_dev =
		get_appropriate_device(WLR_INPUT_DEVICE_TOUCH, libinput_dev);
	if (!wlr_dev) {
		wlr_log(L_DEBUG, "Got a touch event for a device with no touch?");
		return;
	}
	struct libinput_event_touch *tevent =
		libinput_event_get_touch_event(event);
	struct wlr_event_touch_cancel wlr_event = { 0 };
	wlr_event.device = wlr_dev;
	wlr_event.time_msec =
		usec_to_msec(libinput_event_touch_get_time_usec(tevent));
	wlr_event.touch_id = libinput_event_touch_get_slot(tevent);
	wl_signal_emit(&wlr_dev->touch->events.cancel, &wlr_event);
}
