#define GLIS_COMMON_WIDTH 1080
#define GLIS_COMMON_HEIGHT 2032
#include <glis/ipc/ipc.hpp>
#include <glis/font/font.hpp>
#include <glis/internal/internal.hpp>
#include <glis/backup/backup.hpp>
#include <glis/compositor/compositor.hpp>

#define GLIS_CALLBACKS_DRAW(functionName, GLIS_name, GLIS_CLASS_name, GLIS_FONT_name, GLIS_FPS_name) void functionName (GLIS & GLIS_name, GLIS_CLASS & GLIS_CLASS_name, GLIS_FONT & GLIS_FONT_name, GLIS_FPS & GLIS_FPS_name)
#define GLIS_CALLBACKS_RESIZE(functionName, GLIS_name, GLIS_CLASS_name, GLIS_FONT_name, GLIS_FPS_name, width_name, height_name) void functionName (GLIS & GLIS_name, GLIS_CLASS & GLIS_CLASS_name, GLIS_FONT & GLIS_FONT_name, GLIS_FPS & GLIS_FPS_name, GLsizei width_name, GLsizei height_name)
#define GLIS_CALLBACKS_CLOSE(functionName, GLIS_name, GLIS_CLASS_name, GLIS_FONT_name, GLIS_FPS_name) void functionName (GLIS & GLIS_name, GLIS_CLASS & GLIS_CLASS_name, GLIS_FONT & GLIS_FONT_name, GLIS_FPS & GLIS_FPS_name)