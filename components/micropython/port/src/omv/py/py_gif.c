/*
 * This file is part of the OpenMV project.
 * Copyright (c) 2013/2014 Ibrahim Abdelkader <i.abdalkader@gmail.com>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * GIF Python module.
 *
 */
#include "mp.h"
#include "vfs_wrapper.h"
#include "framebuffer.h"
#include "sensor.h"
#include "py_assert.h"
#include "py_helper.h"
#include "py_image.h"

static const mp_obj_type_t py_gif_type; // forward declare
// Gif class
typedef struct py_gif_obj {
    mp_obj_base_t base;
    int width;
    int height;
    bool color;
    bool loop;
    mp_obj_t fp;
} py_gif_obj_t;

static mp_obj_t py_gif_open(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args)
{
    py_gif_obj_t *gif = m_new_obj(py_gif_obj_t);
    gif->width  = py_helper_keyword_int(n_args, args, 1, kw_args, MP_OBJ_NEW_QSTR(MP_QSTR_width), MAIN_FB()->w);
    gif->height = py_helper_keyword_int(n_args, args, 2, kw_args, MP_OBJ_NEW_QSTR(MP_QSTR_height), MAIN_FB()->h);
    gif->color  = py_helper_keyword_int(n_args, args, 3, kw_args, MP_OBJ_NEW_QSTR(MP_QSTR_color), MAIN_FB()->bpp>=2);
    gif->loop   = py_helper_keyword_int(n_args, args, 4, kw_args, MP_OBJ_NEW_QSTR(MP_QSTR_loop), true);
    gif->base.type = &py_gif_type;

    file_write_open(&gif->fp, mp_obj_str_get_str(args[0]));
    gif_open(&gif->fp, gif->width, gif->height, gif->color, gif->loop);
    return gif;
}

static mp_obj_t py_gif_width(mp_obj_t gif_obj)
{
    py_gif_obj_t *arg_gif = gif_obj;
    return mp_obj_new_int(arg_gif->width);
}

static mp_obj_t py_gif_height(mp_obj_t gif_obj)
{
    py_gif_obj_t *arg_gif = gif_obj;
    return mp_obj_new_int(arg_gif->height);
}

static mp_obj_t py_gif_format(mp_obj_t gif_obj)
{
    py_gif_obj_t *arg_gif = gif_obj;
    return mp_obj_new_int(arg_gif->color ? PIXFORMAT_RGB565 : PIXFORMAT_GRAYSCALE);
}

static mp_obj_t py_gif_size(mp_obj_t gif_obj)
{
    py_gif_obj_t *arg_gif = gif_obj;
    return mp_obj_new_int(file_size(&arg_gif->fp));
}

static mp_obj_t py_gif_loop(mp_obj_t gif_obj)
{
    py_gif_obj_t *arg_gif = gif_obj;
    return mp_obj_new_int(arg_gif->loop);
}

static mp_obj_t py_gif_add_frame(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args)
{
    py_gif_obj_t *arg_gif = args[0];
    image_t *arg_img = py_image_cobj(args[1]);
    PY_ASSERT_FALSE_MSG(IM_IS_JPEG(arg_img),   "Operation not supported on JPEG images.");
    PY_ASSERT_FALSE_MSG(IM_IS_BINARY(arg_img), "Operation not supported on binary images.");
    PY_ASSERT_FALSE_MSG((arg_gif->width != arg_img->w) ||
            (arg_gif->height != arg_img->h), "Unexpected image geometry!");

    int delay = py_helper_keyword_int(n_args, args, 2, kw_args, MP_OBJ_NEW_QSTR(MP_QSTR_delay), 10);

    gif_add_frame(&arg_gif->fp, arg_img, delay);
    return mp_const_none;
}

static mp_obj_t py_gif_close(mp_obj_t gif_obj)
{
    py_gif_obj_t *arg_gif = gif_obj;
    gif_close(&arg_gif->fp);
    return mp_const_none;
}

static void py_gif_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    py_gif_obj_t *self = self_in;
    mp_printf(print, "<gif width:%d height:%d color:%d loop:%d>", self->width, self->height, self->color, self->loop);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(py_gif_width_obj, py_gif_width);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(py_gif_height_obj, py_gif_height);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(py_gif_format_obj, py_gif_format);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(py_gif_size_obj, py_gif_size);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(py_gif_loop_obj, py_gif_loop);
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(py_gif_add_frame_obj, 2, py_gif_add_frame);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(py_gif_close_obj, py_gif_close);
static const mp_map_elem_t locals_dict_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_width),       (mp_obj_t)&py_gif_width_obj     },
    { MP_OBJ_NEW_QSTR(MP_QSTR_height),      (mp_obj_t)&py_gif_height_obj    },
    { MP_OBJ_NEW_QSTR(MP_QSTR_format),      (mp_obj_t)&py_gif_format_obj    },
    { MP_OBJ_NEW_QSTR(MP_QSTR_size),        (mp_obj_t)&py_gif_size_obj      },
    { MP_OBJ_NEW_QSTR(MP_QSTR_loop),        (mp_obj_t)&py_gif_loop_obj      },
    { MP_OBJ_NEW_QSTR(MP_QSTR_add_frame),   (mp_obj_t)&py_gif_add_frame_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_close),       (mp_obj_t)&py_gif_close_obj     },
    { NULL, NULL },
};
STATIC MP_DEFINE_CONST_DICT(locals_dict, locals_dict_table);

static const mp_obj_type_t py_gif_type = {
    { &mp_type_type },
    .name  = MP_QSTR_Gif,
    .print = py_gif_print,
    .locals_dict = (mp_obj_t)&locals_dict,
};

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(py_gif_open_obj, 1, py_gif_open);
static const mp_map_elem_t globals_dict_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__),    MP_OBJ_NEW_QSTR(MP_QSTR_gif) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_Gif),         (mp_obj_t)&py_gif_open_obj   },
    { NULL, NULL },
};
STATIC MP_DEFINE_CONST_DICT(globals_dict, globals_dict_table);

const mp_obj_module_t gif_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_t)&globals_dict,
};
