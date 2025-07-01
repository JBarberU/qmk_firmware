// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <lv_conf.h>

#undef LV_FONT_CUSTOM_DECLARE
#define LV_FONT_CUSTOM_DECLARE      \
    LV_FONT_DECLARE(dejavu_sans_12) \
    LV_FONT_DECLARE(dejavu_sans_18) \
    LV_FONT_DECLARE(dejavu_sans_24) \
    LV_FONT_DECLARE(dejavu_sans_32)

//const lv_font_t (dejavu_sans_12);
//const lv_font_t (dejavu_sans_18);
//const lv_font_t (dejavu_sans_24);
//const lv_font_t (dejavu_sans_32);

#undef LV_FONT_DEFAULT
#define LV_FONT_DEFAULT &dejavu_sans_32

#define LV_FONT_DEFAULT_SMALL &dejavu_sans_18
#define LV_FONT_DEFAULT_BIG &dejavu_sans_48

/*
#undef LV_FONT_DEFAULT
#define LV_FONT_DEFAULT &lv_font_montserrat_28

#undef LV_FONT_MONTSERRAT_14
#define LV_FONT_MONTSERRAT_14 0

#undef LV_FONT_MONTSERRAT_28
#define LV_FONT_MONTSERRAT_28 1

#undef LV_FONT_MONTSERRAT_48
#define LV_FONT_MONTSERRAT_48 1
*/
