// Copyright 2025 JBarberU (@jbarberu)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <lv_conf.h>

#undef LV_FONT_CUSTOM_DECLARE
#define LV_FONT_CUSTOM_DECLARE      \
    LV_FONT_DECLARE(dejavu_sans_12) \
    LV_FONT_DECLARE(dejavu_sans_18) \
    LV_FONT_DECLARE(dejavu_sans_24) \
    LV_FONT_DECLARE(dejavu_sans_32)

#undef LV_FONT_DEFAULT
#define LV_FONT_DEFAULT &dejavu_sans_32

#define LV_FONT_DEFAULT_SMALL &dejavu_sans_18
#define LV_FONT_DEFAULT_BIG &dejavu_sans_48
