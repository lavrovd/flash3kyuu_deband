#pragma once

#include "impl_dispatch.h"

enum {
	PIXEL_PROC_8BIT = 0,
	PIXEL_PROC_HIGH_NO_DITHERING,
	PIXEL_PROC_HIGH_ORDERED_DITHERING,
	PIXEL_PROC_HIGH_FLOYD_STEINBERG_DITHERING,
	PIXEL_PROC_MAX
};

#define CALL_IMPL(func, ...) \
	( mode == PIXEL_PROC_8BIT ? pixel_proc_8bit::##func(__VA_ARGS__) : \
	  mode == PIXEL_PROC_HIGH_NO_DITHERING ? pixel_proc_high_no_dithering::##func(__VA_ARGS__) : \
	  mode == PIXEL_PROC_HIGH_ORDERED_DITHERING ? pixel_proc_high_ordered_dithering::##func(__VA_ARGS__) : \
	  mode == PIXEL_PROC_HIGH_FLOYD_STEINBERG_DITHERING ? pixel_proc_high_f_s_dithering::##func(__VA_ARGS__) : \
	  pixel_proc_8bit::##func(__VA_ARGS__) )

#define CHECK_MODE() if (mode < 0 || mode >= PIXEL_PROC_MAX) abort()

#include "pixel_proc_c_8bit.h"

#include "pixel_proc_c_high_no_dithering.h"
#include "pixel_proc_c_high_ordered_dithering.h"
#include "pixel_proc_c_high_f_s_dithering.h"

template <int mode>
static inline void pixel_proc_init_context(char context_buffer[CONTEXT_BUFFER_SIZE], int frame_width)
{
	CHECK_MODE();
	CALL_IMPL(init_context, context_buffer, frame_width);
}

template <int mode>
static inline void pixel_proc_destroy_context(void* context)
{
	CHECK_MODE();
	CALL_IMPL(destroy_context, context);
}

template <int mode>
static inline void pixel_proc_next_pixel(void* context)
{
	CHECK_MODE();
	CALL_IMPL(next_pixel, context);
}

template <int mode>
static inline void pixel_proc_next_row(void* context)
{
	CHECK_MODE();
	CALL_IMPL(next_row, context);
}

template <int mode>
static inline int pixel_proc_upsample(void* context, unsigned char pixel)
{
	CHECK_MODE();
	return CALL_IMPL(upsample, context, pixel);
}

template <int mode>
static inline int pixel_proc_downsample(void* context, int pixel, int row, int column)
{
	CHECK_MODE();
	return CALL_IMPL(downsample, context, pixel, row, column);
}

template <int mode>
static inline int pixel_proc_avg_2(void* context, int pixel1, int pixel2)
{
	CHECK_MODE();
	return CALL_IMPL(avg_2, context, pixel1, pixel2);
}

template <int mode>
static inline int pixel_proc_avg_4(void* context, int pixel1, int pixel2, int pixel3, int pixel4)
{
	CHECK_MODE();
	return CALL_IMPL(avg_4, context, pixel1, pixel2, pixel3, pixel4);
}
