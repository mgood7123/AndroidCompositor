//
// Created by konek on 7/26/2019.
//

#ifndef GLNE_GLIS_H
#define GLNE_GLIS_H

#include <android/native_window.h> // requires ndk r5 or newer
#include <EGL/egl.h> // requires ndk r5 or newer
#include <GLES3/gl32.h>
#include <cstdlib>
#include <cassert>
#include <malloc.h>
#include <string>
#include "logger.h"

#define LOG_TAG "EglSample"

#define GLIS_SWITCH_CASE_CUSTOM_CASE_CUSTOM_LOGGER_CUSTOM_STRING_CAN_I_PRINT_ERROR(LOGGING_FUNCTION, CASE_NAME, name, const, constSTRING, UNNAMED_STRING_CAN_PRINT_ERROR, UNNAMED_STRING_CANNOT_PRINT_ERROR, NAMED_STRING_CAN_PRINT_ERROR, NAMED_STRING_CANNOT_PRINT_ERROR, PRINT) CASE_NAME: { \
    if(name == nullptr || name == NULL || name == 0) { \
        if (PRINT) { \
            if (UNNAMED_STRING_CAN_PRINT_ERROR != nullptr) { \
                LOGGING_FUNCTION(UNNAMED_STRING_CAN_PRINT_ERROR, constSTRING); \
            } \
        } \
        else { \
            if (UNNAMED_STRING_CANNOT_PRINT_ERROR != nullptr) { \
                LOGGING_FUNCTION(UNNAMED_STRING_CANNOT_PRINT_ERROR); \
            } \
        } \
    } \
    else { \
        if (PRINT) { \
            if (NAMED_STRING_CAN_PRINT_ERROR != nullptr) { \
                LOGGING_FUNCTION(NAMED_STRING_CAN_PRINT_ERROR, name, constSTRING); \
            } \
        } \
        else { \
            if (NAMED_STRING_CANNOT_PRINT_ERROR != nullptr) { \
                LOGGING_FUNCTION(NAMED_STRING_CANNOT_PRINT_ERROR, name); \
            } \
        } \
    } \
    break; \
}


#define GLIS_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING_DONT_PRINT_ERROR(LOGGER, name, const, constSTRING, UNNAMED_STRING, NAMED_STRING) \
    GLIS_SWITCH_CASE_CUSTOM_CASE_CUSTOM_LOGGER_CUSTOM_STRING_CAN_I_PRINT_ERROR(LOGGER, case const, name, const, constSTRING, nullptr, UNNAMED_STRING, nullptr, NAMED_STRING, false)
    
#define GLIS_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING(LOGGER, name, const, constSTRING, UNNAMED_STRING, NAMED_STRING) \
    GLIS_SWITCH_CASE_CUSTOM_CASE_CUSTOM_LOGGER_CUSTOM_STRING_CAN_I_PRINT_ERROR(LOGGER, case const, name, const, constSTRING, UNNAMED_STRING, nullptr, NAMED_STRING, nullptr, true)

#define GLIS_ERROR_SWITCH_CASE_CUSTOM_STRING_DONT_PRINT_ERROR(name, const, constSTRING, UNNAMED_STRING, NAMED_STRING) \
    GLIS_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING_DONT_PRINT_ERROR(LOG_ERROR, name, const, constSTRING, UNNAMED_STRING, NAMED_STRING)

#define GLIS_ERROR_SWITCH_CASE_CUSTOM_STRING(name, const, constSTRING, UNNAMED_STRING, NAMED_STRING) \
    GLIS_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING(LOG_ERROR, name, const, constSTRING, UNNAMED_STRING, NAMED_STRING)

#define GLIS_ERROR_SWITCH_CASE(name, const) \
    GLIS_ERROR_SWITCH_CASE_CUSTOM_STRING(name, const, #const, "%s", "%s generated error: %s")

#define GLIS_ERROR_SWITCH_CASE_DEFAULT(name, err) \
    GLIS_SWITCH_CASE_CUSTOM_CASE_CUSTOM_LOGGER_CUSTOM_STRING_CAN_I_PRINT_ERROR(LOG_ERROR, default, name, err, err, "Unknown error: %d", "Unknown error", "%s generated an unknown error: %d", "%s generated an unknown error", true)

#define GLIS_boolean_to_string(val, TRUE_VALUE) val == TRUE_VALUE ? "true" : "false"

#define GLIS_SHADER_SOURCE__BEGIN R"glsl(
#define GLIS_SHADER_SOURCE__END )glsl";
#define GLIS_SHADER_SOURCE__(S, source, E) S source E
#define GLIS_SHADER_SOURCE(source) GLIS_SHADER_SOURCE__(GLIS_SHADER_SOURCE__BEGIN, source, GLIS_SHADER_SOURCE__END)

#define GLIS_error_to_string_exec(x) x; GLIS_error_to_string(#x)

void GLIS_error_to_string(const char * name, GLint err) {
    switch(err) {

        // GENERATED BY glGetError() ITSELF
        GLIS_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING_DONT_PRINT_ERROR(LOG_INFO, name, GL_NO_ERROR, "GL_NO_ERROR", "no error was generated", "%s did not generate an error")
        GLIS_ERROR_SWITCH_CASE(name, GL_INVALID_ENUM)
        GLIS_ERROR_SWITCH_CASE(name, GL_INVALID_VALUE)
        GLIS_ERROR_SWITCH_CASE(name, GL_INVALID_OPERATION)
        GLIS_ERROR_SWITCH_CASE(name, GL_INVALID_FRAMEBUFFER_OPERATION)
        GLIS_ERROR_SWITCH_CASE(name, GL_OUT_OF_MEMORY)

        // GENERATED BY OTHER FUNCTIONS
        GLIS_ERROR_SWITCH_CASE(name, EGL_BAD_DISPLAY)
        GLIS_ERROR_SWITCH_CASE(name, EGL_NOT_INITIALIZED)
        GLIS_ERROR_SWITCH_CASE(name, EGL_BAD_CONFIG)
        GLIS_ERROR_SWITCH_CASE(name, EGL_BAD_ATTRIBUTE)
        GLIS_ERROR_SWITCH_CASE(name, EGL_BAD_ALLOC)
        GLIS_ERROR_SWITCH_CASE(name, EGL_BAD_MATCH)

        // WHEN ALL ELSE FAILS
        GLIS_ERROR_SWITCH_CASE_DEFAULT(name, err)
    }
}

void GLIS_error_to_string() {
    GLIS_error_to_string(nullptr, glGetError());
}

void GLIS_error_to_string(const char * name) {
    GLIS_error_to_string(name, glGetError());
}

void GLIS_error_to_string(GLint err) {
    GLIS_error_to_string(nullptr, err);
}

void GLIS_GL_INFORMATION() {
    LOG_INFO("GL_VERSION: %s", glGetString(GL_VERSION));
    LOG_INFO("GL_VENDOR: %s", glGetString(GL_VENDOR));
    LOG_INFO("GL_RENDERER: %s", glGetString(GL_RENDERER));
    LOG_INFO("GL_EXTENSIONS: %s", glGetString(GL_EXTENSIONS));
}

class GLIS_CLASS {
public:
    int init_GLIS = false;
    bool
            init_eglGetDisplay = false,
            init_eglInitialize = false,
            init_eglChooseConfig = false,
            init_eglCreateWindowSurface = false,
            init_eglCreatePbufferSurface = false,
            init_eglCreateContext = false,
            init_eglMakeCurrent = false;
    const GLint *configuration_attributes = nullptr, *context_attributes = nullptr, *surface_attributes = nullptr;
    EGLint eglMajVers = 0, eglMinVers = 0, number_of_configurations = 0;
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLConfig configuration = 0;
    EGLContext context = EGL_NO_CONTEXT, shared_context = EGL_NO_CONTEXT;
    EGLSurface surface = EGL_NO_SURFACE;
    ANativeWindow * native_window = nullptr;
    GLint width = 0, height = 0;
};

void GLIS_destroy_GLIS(class GLIS_CLASS & GLIS) {
    if (!GLIS.init_GLIS) return;

    if (GLIS.init_eglMakeCurrent) {
        eglMakeCurrent(GLIS.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        GLIS.init_eglMakeCurrent = false;
    }
    if(GLIS.init_eglCreateContext) {
        eglDestroyContext(GLIS.display, GLIS.context);
        GLIS.context = EGL_NO_CONTEXT;
        GLIS.shared_context = EGL_NO_CONTEXT;
        GLIS.init_eglCreateContext = false;
    }
    if (GLIS.init_eglCreateWindowSurface || GLIS.init_eglCreatePbufferSurface) {
        eglDestroySurface(GLIS.display, GLIS.surface);
        GLIS.surface = EGL_NO_SURFACE;
        GLIS.init_eglCreateWindowSurface = false;
        GLIS.init_eglCreatePbufferSurface = false;
    }
    if (GLIS.init_eglChooseConfig) {
        // TODO: figure how to undo init_eglChooseConfig
    }
    if (GLIS.init_eglInitialize) {
        eglTerminate(GLIS.display);
        GLIS.init_eglInitialize = false;
    }
    if (GLIS.init_eglGetDisplay) {
        GLIS.display = EGL_NO_DISPLAY;
        GLIS.init_eglGetDisplay = false;
    }
    GLIS.init_GLIS = false;
}


bool GLIS_init_display(class GLIS_CLASS & GLIS) {
    if ((GLIS.display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        GLIS_error_to_string("eglGetDisplay");
        return false;
    }
    GLIS.init_eglGetDisplay = true;

    if (eglInitialize(GLIS.display, &GLIS.eglMajVers, &GLIS.eglMinVers) != EGL_TRUE) {
        GLIS_error_to_string("eglInitialize");
        return false;
    }
    GLIS.init_eglInitialize = true;

    LOG_INFO("EGL init with version %d.%d", GLIS.eglMajVers, GLIS.eglMinVers);
    return true;
}

bool GLIS_init_config(class GLIS_CLASS & GLIS) {
    if (!eglChooseConfig(GLIS.display, GLIS.configuration_attributes, &GLIS.configuration, 1, &GLIS.number_of_configurations)) {
        GLIS_error_to_string("eglChooseConfig");
        return false;
    }
    GLIS.init_eglChooseConfig = true;
    return true;
}

bool GLIS_init_surface_CreateWindowSurface(class GLIS_CLASS & GLIS) {
    if (!(GLIS.surface = eglCreateWindowSurface(GLIS.display, GLIS.configuration, GLIS.native_window, nullptr))) {
        GLIS_error_to_string("eglCreateWindowSurface");
        return false;
    }
    GLIS.init_eglCreateWindowSurface = true;
    return true;
}

bool GLIS_init_surface_CreatePbufferSurface(class GLIS_CLASS & GLIS) {
    if (!(GLIS.surface = eglCreatePbufferSurface(GLIS.display, GLIS.configuration, GLIS.surface_attributes))) {
        if (GLIS.surface == EGL_NO_SURFACE) LOG_INFO("EGL_NO_SURFACE");
        GLIS_error_to_string("eglCreatePbufferSurface");
        return false;
    }
    GLIS.init_eglCreatePbufferSurface = true;
    return true;
}

bool GLIS_create_context(class GLIS_CLASS & GLIS) {
    if (!(GLIS.context = eglCreateContext(GLIS.display, GLIS.configuration, GLIS.shared_context, GLIS.context_attributes))) {
        GLIS_error_to_string("eglCreateContext");
        return false;
    }
    GLIS.init_eglCreateContext = true;
    return true;
}

bool GLIS_switch_to_context(class GLIS_CLASS & GLIS) {
    if (!eglMakeCurrent(GLIS.display, GLIS.surface, GLIS.surface, GLIS.context)) {
        GLIS_error_to_string("eglMakeCurrent");
        return false;
    }
    GLIS.init_eglMakeCurrent = true;
    GLIS_GL_INFORMATION();
    return true;
}

bool GLIS_get_width_height(class GLIS_CLASS & GLIS) {
    if (!eglQuerySurface(GLIS.display, GLIS.surface, EGL_WIDTH, &GLIS.width)) {
        GLIS_error_to_string("eglQuerySurface (EGL_WIDTH)");
        return false;
    }
    if (!eglQuerySurface(GLIS.display, GLIS.surface, EGL_HEIGHT, &GLIS.height)) {
        GLIS_error_to_string("eglQuerySurface (EGL_HEIGHT)");
        return false;
    }
    return true;
}

bool GLIS_initialize(class GLIS_CLASS & GLIS, GLint surface_type) {
    if (GLIS.init_GLIS) return true;

    LOG_INFO("Initializing");

    if (!GLIS_init_display(GLIS)) {
        GLIS_destroy_GLIS(GLIS);
        return false;
    }
    if (!GLIS_init_config(GLIS)) {
        GLIS_destroy_GLIS(GLIS);
        return false;
    }
    if (surface_type == EGL_WINDOW_BIT) {
        LOG_INFO("creating window surface");
        if (!GLIS_init_surface_CreateWindowSurface(GLIS)) {
            GLIS_destroy_GLIS(GLIS);
            return false;
        }
    }
    else if (surface_type == EGL_PBUFFER_BIT) {
        LOG_INFO("creating pixel buffer surface");
        if (!GLIS_init_surface_CreatePbufferSurface(GLIS)) {
            GLIS_destroy_GLIS(GLIS);
            return false;
        }
    }
    if (!eglBindAPI(EGL_OPENGL_ES_API)) {
        GLIS_destroy_GLIS(GLIS);
        return false;
    }
    if (!GLIS_create_context(GLIS)) {
        GLIS_destroy_GLIS(GLIS);
        return false;
    }
    if (!GLIS_switch_to_context(GLIS)) {
        GLIS_destroy_GLIS(GLIS);
        return false;
    }
    if (!GLIS_get_width_height(GLIS)) {
        GLIS_destroy_GLIS(GLIS);
        return false;
    }
    GLIS.init_GLIS = true;
    LOG_INFO("Initialized");
    return true;
}

bool GLIS_setupOnScreenRendering(class GLIS_CLASS & GLIS, EGLContext shared_context) {
    GLIS.shared_context = shared_context;

    const EGLint config[] = { EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE };
    GLIS.configuration_attributes = config;

    const EGLint context[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    GLIS.context_attributes = context;

    const EGLint surface[] = { EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT, EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_RED_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_DEPTH_SIZE, 16, EGL_NONE };
    GLIS.surface_attributes = surface;

    return GLIS_initialize(GLIS, EGL_WINDOW_BIT);
}

bool GLIS_setupOnScreenRendering(class GLIS_CLASS & GLIS) {
    return GLIS_setupOnScreenRendering(GLIS, EGL_NO_CONTEXT);
}

bool GLIS_setupOffScreenRendering(class GLIS_CLASS & GLIS, int w, int h, EGLContext shared_context) {
    GLIS.shared_context = shared_context;

    const EGLint config[] = { EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT, EGL_NONE };
    GLIS.configuration_attributes = config;

    const EGLint context[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    GLIS.context_attributes = context;

    const EGLint surface[] = { EGL_WIDTH, w, EGL_HEIGHT, h, EGL_TEXTURE_FORMAT, EGL_TEXTURE_RGB, EGL_TEXTURE_TARGET, EGL_TEXTURE_2D, EGL_NONE };
    GLIS.surface_attributes = surface;

    return GLIS_initialize(GLIS, EGL_PBUFFER_BIT);
}

bool GLIS_setupOffScreenRendering(class GLIS_CLASS & GLIS, int w, int h) {
    return GLIS_setupOffScreenRendering(GLIS, w, h, EGL_NO_CONTEXT);
}

GLboolean GLIS_ShaderCompilerSupported() {
    GLboolean GLSC_supported;
    GLIS_error_to_string_exec(glGetBooleanv(GL_SHADER_COMPILER, &GLSC_supported));
    LOG_INFO("Supports Shader Compiler: %s", GLSC_supported == GL_TRUE ? "true" : "false");
    return GLSC_supported;
}

GLuint GLIS_createShader(GLenum shaderType, const char * & src) {
    if (GLIS_ShaderCompilerSupported()) {
        const char * SHADER_TYPE = nullptr;
        switch (shaderType) {
            case GL_COMPUTE_SHADER:
                SHADER_TYPE = "Compute";
                break;
            case GL_FRAGMENT_SHADER:
                SHADER_TYPE = "Fragment";
                break;
            case GL_GEOMETRY_SHADER:
                SHADER_TYPE = "Geometry";
                break;
            case GL_VERTEX_SHADER:
                SHADER_TYPE = "Vertex";
                break;
            default:
                SHADER_TYPE = "Unknown";
                break;
        }
        LOG_INFO("Creating %s Shader", SHADER_TYPE);
        GLuint shader = GLIS_error_to_string_exec(glCreateShader(shaderType));
        if (!shader) {
            return 0;
        }
        GLIS_error_to_string_exec(glShaderSource(shader, 1, &src, nullptr));
        GLint compiled = GL_FALSE;
        LOG_INFO("Compiling %s Shader", SHADER_TYPE);
        GLIS_error_to_string_exec(glCompileShader(shader));
        GLIS_error_to_string_exec(glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled));
        if (compiled != GL_TRUE) {
            GLint infoLogLen = 0;
            GLIS_error_to_string_exec(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen));
            if (infoLogLen > 0) {
                GLchar *infoLog = (GLchar *) malloc(static_cast<size_t>(infoLogLen));
                if (infoLog) {
                    GLIS_error_to_string_exec(
                            glGetShaderInfoLog(shader, infoLogLen, nullptr, infoLog));
                    LOG_ERROR("Could not compile %s shader:\n%s\n", SHADER_TYPE, infoLog);
                    free(infoLog);
                }
            }
            GLIS_error_to_string_exec(glDeleteShader(shader));
            return 0;
        }
        assert(glIsShader(shader) == GL_TRUE);
        return shader;
    } else return 0;
}

GLboolean GLIS_validate_program_link(GLuint & Program) {
    GLint linked = GL_FALSE;
    GLIS_error_to_string_exec(glGetProgramiv(Program, GL_LINK_STATUS, &linked));
    if (linked != GL_TRUE) {
        GLint infoLogLen = 0;
        GLIS_error_to_string_exec(glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &infoLogLen));
        if (infoLogLen > 0) {
            GLchar *infoLog = (GLchar *) malloc(static_cast<size_t>(infoLogLen));
            if (infoLog) {
                GLIS_error_to_string_exec(
                        glGetProgramInfoLog(Program, infoLogLen, nullptr, infoLog));
                LOG_ERROR("Could not link program:\n%s\n", infoLog);
                free(infoLog);
            }
        }
        GLIS_error_to_string_exec(glDeleteProgram(Program));
        return GL_FALSE;
    }
    return GL_TRUE;
}

GLboolean GLIS_validate_program_valid(GLuint & Program) {
    GLint validated = GL_FALSE;
    GLIS_error_to_string_exec(glValidateProgram(Program));
    GLIS_error_to_string_exec(glGetProgramiv(Program, GL_VALIDATE_STATUS, &validated));
    if (validated != GL_TRUE) {
        GLint infoLogLen = 0;
        GLIS_error_to_string_exec(glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &infoLogLen));
        if (infoLogLen > 0) {
            GLchar *infoLog = (GLchar *) malloc(static_cast<size_t>(infoLogLen));
            if (infoLog) {
                GLIS_error_to_string_exec(
                        glGetProgramInfoLog(Program, infoLogLen, nullptr, infoLog));
                LOG_ERROR("Could not validate program:\n%s\n", infoLog);
                free(infoLog);
            }
        }
        GLIS_error_to_string_exec(glDeleteProgram(Program));
        return GL_FALSE;
    }
    return GL_TRUE;
}

GLboolean GLIS_validate_program(GLuint & Program) {
    if (GLIS_validate_program_link(Program) == GL_TRUE)
        if (GLIS_validate_program_valid(Program) == GL_TRUE) {
            GLboolean v = GLIS_error_to_string_exec(glIsProgram(Program));
            return v;
        }
    return GL_FALSE;
}

/*
// Normalized Device Coordinates (NDC)
                   height
( -1, 1)             | (  0,  1)  (  1,  1)
                     |
                     |
                     |
                     |
                     |
                     |
                     |
                     |
( -1,  0)            | (  0,  0)  (  1,  0)
---------------------+--------------------- width
                     |
                     |
                     |
                     |
                     |
                     |
                     |
                     |
                     |
( -1, -1)            | (  0, -1)   (  1, -1)

// height = 40
// width = 20

GLIS_set_conversion_origin(GLIS_CONVERSION_ORIGIN_TOP_LEFT);
GLIS_convertPair(0,0,20,40);
GLIS_convertPair(0,40,20,40);
GLIS_convertPair(20,0,20,40);
GLIS_convertPair(10,10,20,40);
GLIS_convertPair(10,20,20,40);
GLIS_convertPair(20,20,20,40);
GLIS_convertPair(20,40,20,40);
GLIS_set_conversion_origin(GLIS_CONVERSION_ORIGIN_TOP_RIGHT);
GLIS_convertPair(0,0,20,40);
GLIS_convertPair(0,40,20,40);
GLIS_convertPair(20,0,20,40);
GLIS_convertPair(10,10,20,40);
GLIS_convertPair(10,20,20,40);
GLIS_convertPair(20,20,20,40);
GLIS_convertPair(20,40,20,40);
GLIS_set_conversion_origin(GLIS_CONVERSION_ORIGIN_BOTTOM_LEFT);
GLIS_convertPair(0,0,20,40);
GLIS_convertPair(0,40,20,40);
GLIS_convertPair(20,0,20,40);
GLIS_convertPair(10,10,20,40);
GLIS_convertPair(10,20,20,40);
GLIS_convertPair(20,20,20,40);
GLIS_convertPair(20,40,20,40);
GLIS_set_conversion_origin(GLIS_CONVERSION_ORIGIN_BOTTOM_RIGHT);
GLIS_convertPair(0,0,20,40);
GLIS_convertPair(0,40,20,40);
GLIS_convertPair(20,0,20,40);
GLIS_convertPair(10,10,20,40);
GLIS_convertPair(10,20,20,40);
GLIS_convertPair(20,20,20,40);
GLIS_convertPair(20,40,20,40);

    converting with origin top left
    inverting 'y'
    width: 0, height: 0, ConvertPair: -1.000000, 1.000000
    inverting 'y'
    width: 0, height: 40, ConvertPair: -1.000000, -1.000000
    inverting 'y'
    width: 20, height: 0, ConvertPair: 1.000000, 1.000000
    inverting 'y'
    width: 10, height: 10, ConvertPair: 0.000000, 0.500000
    inverting 'y'
    width: 10, height: 20, ConvertPair: 0.000000, -0.000000
    inverting 'y'
    width: 20, height: 20, ConvertPair: 1.000000, -0.000000
    inverting 'y'
    width: 20, height: 40, ConvertPair: 1.000000, -1.000000
    converting with origin top right
    inverting 'x'
    inverting 'y'
    width: 0, height: 0, ConvertPair: 1.000000, 1.000000
    inverting 'x'
    inverting 'y'
    width: 0, height: 40, ConvertPair: 1.000000, -1.000000
    inverting 'x'
    inverting 'y'
    width: 20, height: 0, ConvertPair: -1.000000, 1.000000
    inverting 'x'
    inverting 'y'
    width: 10, height: 10, ConvertPair: -0.000000, 0.500000
    inverting 'x'
    inverting 'y'
    width: 10, height: 20, ConvertPair: -0.000000, -0.000000
    inverting 'x'
    inverting 'y'
    width: 20, height: 20, ConvertPair: -1.000000, -0.000000
    inverting 'x'
    inverting 'y'
    width: 20, height: 40, ConvertPair: -1.000000, -1.000000
    converting with origin bottom left
    no conversion
    width: 0, height: 0, ConvertPair: -1.000000, -1.000000
    no conversion
    width: 0, height: 40, ConvertPair: -1.000000, 1.000000
    no conversion
    width: 20, height: 0, ConvertPair: 1.000000, -1.000000
    no conversion
    width: 10, height: 10, ConvertPair: 0.000000, -0.500000
    no conversion
    width: 10, height: 20, ConvertPair: 0.000000, 0.000000
    no conversion
    width: 20, height: 20, ConvertPair: 1.000000, 0.000000
    no conversion
    width: 20, height: 40, ConvertPair: 1.000000, 1.000000
    converting with origin bottom right
    inverting 'x'
    width: 0, height: 0, ConvertPair: 1.000000, -1.000000
    inverting 'x'
    width: 0, height: 40, ConvertPair: 1.000000, 1.000000
    inverting 'x'
    width: 20, height: 0, ConvertPair: -1.000000, -1.000000
    inverting 'x'
    width: 10, height: 10, ConvertPair: -0.000000, -0.500000
    inverting 'x'
    width: 10, height: 20, ConvertPair: -0.000000, 0.000000
    inverting 'x'
    width: 20, height: 20, ConvertPair: -1.000000, 0.000000
    inverting 'x'
    width: 20, height: 40, ConvertPair: -1.000000, 1.000000
*/

template <typename TYPE>
float GLIS_inverse(TYPE num) {
    return num<0?-num:-(num);
}

template <typename TYPE>
float GLIS_convert(TYPE num, TYPE num_max) {
    // 3 year old magic
    return (num-(num_max/2))/(num_max/2);
}

template <typename TYPE>
class GLIS_coordinates {
    public:
        GLIS_coordinates(TYPE TYPE_INITIALIZER) {
            TYPE x = TYPE_INITIALIZER;
            TYPE y = TYPE_INITIALIZER;
        }

        TYPE x;
        TYPE y;
};

template <typename TYPE>
class GLIS_rect {
    public:
        GLIS_rect(TYPE TYPE_INITIALIZER) {
            topLeft = GLIS_coordinates<TYPE>(TYPE_INITIALIZER);
            topRight = GLIS_coordinates<TYPE>(TYPE_INITIALIZER);
            bottomLeft = GLIS_coordinates<TYPE>(TYPE_INITIALIZER);
            bottomRight = GLIS_coordinates<TYPE>(TYPE_INITIALIZER);
        }

        class GLIS_coordinates <TYPE> topLeft = NULL;
        class GLIS_coordinates <TYPE> topRight = NULL;
        class GLIS_coordinates <TYPE> bottomLeft = NULL;
        class GLIS_coordinates <TYPE> bottomRight = NULL;
};

template <typename TYPE>
class GLIS_rect<TYPE> GLIS_points_to_rect(TYPE TYPE_INITIALIZER, TYPE x1, TYPE y1, TYPE x2, TYPE y2) {
    class GLIS_rect<TYPE> r(TYPE_INITIALIZER);
    /* assume origin bottom left */
    r.bottomLeft.x = x1;
    r.bottomLeft.y = y1;
    r.topRight.x = x2;
    r.topRight.y = y2;
    /* figure out bottomRight and topLeft */
    r.bottomRight.x = x2;
    r.bottomRight.y = y1;
    r.topLeft.x = x1;
    r.topLeft.y = y2;
    return r;
}

#define GLIS_CONVERSION_ORIGIN_TOP_LEFT 0
#define GLIS_CONVERSION_ORIGIN_TOP_RIGHT 1
#define GLIS_CONVERSION_ORIGIN_BOTTOM_LEFT 2
#define GLIS_CONVERSION_ORIGIN_BOTTOM_RIGHT 3

int GLIS_CONVERSION_ORIGIN = GLIS_CONVERSION_ORIGIN_BOTTOM_LEFT;

void GLIS_set_conversion_origin(int origin) {
    GLIS_CONVERSION_ORIGIN = origin;
    switch (GLIS_CONVERSION_ORIGIN) {
        case GLIS_CONVERSION_ORIGIN_TOP_LEFT:
            LOG_INFO("converting with origin top left");
            break;
        case GLIS_CONVERSION_ORIGIN_TOP_RIGHT:
            LOG_INFO("converting with origin top right");
            break;
        case GLIS_CONVERSION_ORIGIN_BOTTOM_LEFT:
            LOG_INFO("converting with origin bottom left");
            break;
        case GLIS_CONVERSION_ORIGIN_BOTTOM_RIGHT:
            LOG_INFO("converting with origin bottom right");
            break;
        default:
            LOG_INFO("unknown conversion");
            break;
    }
}

template <typename TYPEFROM, typename TYPETO>
class GLIS_coordinates<TYPETO> GLIS_convertPair(TYPETO TYPETO_INITIALIZER, TYPEFROM x, TYPEFROM y, TYPEFROM x_max, TYPEFROM y_max) {
    class GLIS_coordinates<TYPETO> xy(TYPETO_INITIALIZER);
    if (x > x_max) LOG_INFO("x is out of bounds (expected %hi, got %hi)\n", x_max, x);
    else if (y < 0) LOG_INFO("x is out of bounds (expected %hi, got %hi)\n", 0, x);
    if (y > y_max) LOG_INFO("y is out of bounds (expected %hi, got %hi)\n", y_max, y);
    else if (y < 0) LOG_INFO("y is out of bounds (expected %hi, got %hi)\n", 0, y);
    else {
        xy.x = GLIS_convert<TYPETO>(static_cast<TYPETO>(x), static_cast<TYPETO>(x_max)); // x
        xy.y = GLIS_convert<TYPETO>(static_cast<TYPETO>(y), static_cast<TYPETO>(y_max)); // y
        switch (GLIS_CONVERSION_ORIGIN) {
            case GLIS_CONVERSION_ORIGIN_TOP_LEFT:
                LOG_INFO("inverting 'y'");
                xy.y = GLIS_inverse<TYPETO>(xy.y);
                break;
            case GLIS_CONVERSION_ORIGIN_TOP_RIGHT:
                LOG_INFO("inverting 'x'");
                xy.x = GLIS_inverse<TYPETO>(xy.x);
                LOG_INFO("inverting 'y'");
                xy.y = GLIS_inverse<TYPETO>(xy.y);
                break;
            case GLIS_CONVERSION_ORIGIN_BOTTOM_LEFT: {
                LOG_INFO("no conversion");
                break;
            }
            case GLIS_CONVERSION_ORIGIN_BOTTOM_RIGHT:
                LOG_INFO("inverting 'x'");
                xy.x = GLIS_inverse<TYPETO>(xy.x);
                break;
            default:
                LOG_INFO("unknown conversion");
                break;
        }
        LOG_INFO("width: %hi, width_max: %hi, height: %hi, height_max: %hi, ConvertPair: %f, %f\n", x, x_max, y, y_max, xy.x, xy.y);
    }
    return xy;
}

template <typename TYPE>
struct GLIS_quater_position {
    TYPE x;
    TYPE y;
    TYPE z;
};

template <typename TYPE>
struct GLIS_quater_color {
    TYPE R;
    TYPE B;
    TYPE G;
};

template <typename TYPE>
struct GLIS_quater {
    struct GLIS_quater_position<TYPE> position;
    struct GLIS_quater_color<TYPE> color;
    struct GLIS_quater_position<TYPE> texture_position;
};

template <typename TYPE>
struct GLIS_vertex_map_rectangle {
    struct GLIS_quater<TYPE> top_right;
    struct GLIS_quater<TYPE> bottom_right;
    struct GLIS_quater<TYPE> bottom_left;
    struct GLIS_quater<TYPE> top_left;
};

template <typename TYPE>
class GLIS_vertex_data {
    public:
        TYPE *vertex;
        int size_of_position;
        int size_of_color;
        int size_of_texture_position;
        int size_per_quater;
        int number_of_points;
        size_t vertex_size;
        unsigned int *indices;
        size_t indices_size;
        size_t typesize;

        void print(const char *format) {
            std::string fmt = "\n";
            fmt += "VECTOR OUTPUT:    |       positions       |       colors          |texture positions|";
            fmt += "\n";
            fmt += "VALUES:           |   X      Y      Z     |   R      B      G     |   X      Y      |";
            fmt += "\n";
            fmt += "TOP RIGHT:      ";
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format; fmt += ", "; fmt += format;
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format; fmt += ", "; fmt += format;
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format;
            fmt += "   |";
            fmt += "\n";
            fmt += "BOTTOM RIGHT:   ";
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format; fmt += ", "; fmt += format;
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format; fmt += ", "; fmt += format;
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format;
            fmt += "   |";
            fmt += "\n";
            fmt += "BOTTOM LEFT:    ";
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format; fmt += ", "; fmt += format;
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format; fmt += ", "; fmt += format;
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format;
            fmt += "   |";
            fmt += "\n";
            fmt += "TOP LEFT:       ";
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format; fmt += ", "; fmt += format;
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format; fmt += ", "; fmt += format;
            fmt += "  |  ";
            fmt += format; fmt += ", "; fmt += format;
            fmt += "   |";
            LOG_INFO(fmt.c_str(),
                     vertex[0], vertex[1], vertex[2],
                     vertex[3], vertex[4], vertex[5],
                     vertex[6], vertex[7],
                     vertex[8], vertex[9], vertex[10],
                     vertex[11], vertex[12], vertex[13],
                     vertex[14], vertex[15],
                     vertex[16], vertex[17], vertex[18],
                     vertex[19], vertex[20], vertex[21],
                     vertex[22], vertex[23],
                     vertex[24], vertex[25], vertex[26],
                     vertex[27], vertex[28], vertex[29],
                     vertex[30], vertex[31]
            );
        }

        void bind_buffers(GLuint * vertex_buffer_object, GLuint * vertex_array_object,
                         GLuint * element_buffer_object, GLenum usage) {
            GLIS_error_to_string_exec(glBindVertexArray(*vertex_array_object));
            GLIS_error_to_string_exec(glBindBuffer(GL_ARRAY_BUFFER, *vertex_buffer_object));
            GLIS_error_to_string_exec(glBufferData(GL_ARRAY_BUFFER, this->vertex_size, this->vertex, usage));
            GLIS_error_to_string_exec(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *element_buffer_object));
            GLIS_error_to_string_exec(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices_size, this->indices, usage));
        }

        void init_attributes() {
            // position attribute
            GLIS_error_to_string_exec(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
            GLIS_error_to_string_exec(glEnableVertexAttribArray(0));
            // color attribute
            GLIS_error_to_string_exec(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
            GLIS_error_to_string_exec(glEnableVertexAttribArray(1));
            // texture coord attribute
            GLIS_error_to_string_exec(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))));
            GLIS_error_to_string_exec(glEnableVertexAttribArray(2));
        }
};

template <typename TYPE>
void GLIS_fill_vertex_rect(TYPE * vertex, struct GLIS_quater<TYPE> & quater, int offset) {
    vertex[offset+0] = quater.position.x;
    vertex[offset+1] = quater.position.y;
    vertex[offset+2] = quater.position.z;
    vertex[offset+3] = quater.color.R;
    vertex[offset+4] = quater.color.B;
    vertex[offset+5] = quater.color.G;
    vertex[offset+6] = quater.texture_position.x;
    vertex[offset+7] = quater.texture_position.y;
};

template <typename TYPE>
struct GLIS_vertex_data<TYPE> GLIS_build_vertex_rect(struct GLIS_vertex_map_rectangle<TYPE> & data) {
    struct GLIS_vertex_data<TYPE> v;
    v.typesize = sizeof(TYPE);
    v.size_of_position = 3;
    v.size_of_color = 3;
    v.size_of_texture_position = 2;
    v.size_per_quater = v.size_of_position+v.size_of_color+v.size_of_texture_position;
    v.number_of_points = 4;
    v.vertex_size = v.typesize*(v.size_per_quater*v.number_of_points);
    v.vertex = static_cast<TYPE*>(malloc(v.vertex_size));
    GLIS_fill_vertex_rect(v.vertex, data.top_right, 0*v.size_per_quater);
    GLIS_fill_vertex_rect(v.vertex, data.bottom_right, 1*v.size_per_quater);
    GLIS_fill_vertex_rect(v.vertex, data.bottom_left, 2*v.size_per_quater);
    GLIS_fill_vertex_rect(v.vertex, data.top_left, 3*v.size_per_quater);
    v.indices_size = 6 * sizeof(unsigned int);
    v.indices = static_cast<unsigned int *>(malloc(v.indices_size));
    v.indices[0] = 0;
    v.indices[1] = 1;
    v.indices[2] = 3;
    v.indices[3] = 1;
    v.indices[4] = 2;
    v.indices[5] = 3;
    return v;
}

template <typename TYPEFROM, typename TYPETO>
struct GLIS_vertex_map_rectangle<TYPETO> GLIS_build_vertex_data_rect(TYPETO TYPETO_INITIALIZER, class GLIS_rect<TYPEFROM> data, TYPEFROM max_x, TYPEFROM max_y) {
    struct GLIS_vertex_map_rectangle<TYPETO> m;
    GLIS_set_conversion_origin(GLIS_CONVERSION_ORIGIN_BOTTOM_LEFT);
    GLIS_coordinates<TYPETO> point1 = GLIS_convertPair<TYPEFROM, TYPETO>(TYPETO_INITIALIZER, data.topLeft.x,data.topLeft.y,max_x,max_y);
    m.top_left.position.x = point1.x;
    m.top_left.position.y = point1.y;
    m.top_left.position.z = 0.0F;
    m.top_left.texture_position.x = 0.0F;
    m.top_left.texture_position.y = 1.0F;
    m.top_left.texture_position.z = 0.0F;
    m.top_left.color.R = 1.0F;
    m.top_left.color.B = 1.0F;
    m.top_left.color.G = 1.0F;
    GLIS_coordinates<TYPETO> point2 = GLIS_convertPair<TYPEFROM, TYPETO>(TYPETO_INITIALIZER, data.topRight.x,data.topRight.y,max_x,max_y);
    m.top_right.position.x = point2.x;
    m.top_right.position.y = point2.y;
    m.top_right.position.z = 0.0F;
    m.top_right.texture_position.x = 1.0F;
    m.top_right.texture_position.y = 1.0F;
    m.top_right.texture_position.z = 0.0F;
    m.top_right.color.R = 0.0F;
    m.top_right.color.B = 0.0F;
    m.top_right.color.G = 1.0F;
    GLIS_coordinates<TYPETO> point3 = GLIS_convertPair<TYPEFROM, TYPETO>(TYPETO_INITIALIZER, data.bottomLeft.x,data.bottomLeft.y,max_x,max_y);
    m.bottom_left.position.x = point3.x;
    m.bottom_left.position.y = point3.y;
    m.bottom_left.position.z = 0.0F;
    m.bottom_left.texture_position.x = 0.0F;
    m.bottom_left.texture_position.y = 0.0F;
    m.bottom_left.texture_position.z = 0.0F;
    m.bottom_left.color.R = 1.0F;
    m.bottom_left.color.B = 0.0F;
    m.bottom_left.color.G = 0.0F;
    GLIS_coordinates<TYPETO> point4 = GLIS_convertPair<TYPEFROM, TYPETO>(TYPETO_INITIALIZER, data.bottomRight.x,data.bottomRight.y,max_x,max_y);
    m.bottom_right.position.x = point4.x;
    m.bottom_right.position.y = point4.y;
    m.bottom_right.position.z = 0.0F;
    m.bottom_right.texture_position.x = 1.0F;
    m.bottom_right.texture_position.y = 0.0F;
    m.bottom_right.texture_position.z = 0.0F;
    m.bottom_right.color.R = 0.0F;
    m.bottom_right.color.B = 1.0F;
    m.bottom_right.color.G = 0.0F;
    return m;
}

GLuint GLIS_texture_buffer(GLuint & renderedTexture, GLint & texture_width, GLint & texture_height) {
    GLuint FBOID;
    GLIS_error_to_string_exec(glGenFramebuffers(1, &FBOID));
    GLIS_error_to_string_exec(glBindFramebuffer(GL_FRAMEBUFFER, FBOID));
    GLuint rboColorId;
    GLIS_error_to_string_exec(glGenRenderbuffers(1, &rboColorId));
    GLIS_error_to_string_exec(glBindRenderbuffer(GL_RENDERBUFFER, rboColorId));
    GLIS_error_to_string_exec(glRenderbufferStorage(GL_RENDERBUFFER,
                                                    GL_RGB8,
                                                    texture_width,
                                                    texture_height
    ));
    GLIS_error_to_string_exec(glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                                        GL_COLOR_ATTACHMENT0,
                                                        GL_RENDERBUFFER,
                                                        rboColorId));
    GLIS_error_to_string_exec(glBindFramebuffer(GL_FRAMEBUFFER, FBOID));

    GLenum FramebufferStatus = GLIS_error_to_string_exec(
        glCheckFramebufferStatus(GL_FRAMEBUFFER));

    if (FramebufferStatus != GL_FRAMEBUFFER_COMPLETE)
        LOG_ERROR("framebuffer is not complete");
    else
        LOG_INFO("framebuffer is complete");

    // create a new texture
    GLIS_error_to_string_exec(glGenTextures(1, &renderedTexture));
    GLIS_error_to_string_exec(glBindTexture(GL_TEXTURE_2D, renderedTexture));
    GLIS_error_to_string_exec(glTexImage2D(GL_TEXTURE_2D,
                                           0,
                                           GL_RGBA,
                                           texture_width,
                                           texture_height,
                                           0,
                                           GL_RGBA,
                                           GL_UNSIGNED_BYTE,
                                           0));
    GLIS_error_to_string_exec(glGenerateMipmap(GL_TEXTURE_2D));
    GLIS_error_to_string_exec(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLIS_error_to_string_exec(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLIS_error_to_string_exec(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
    GLIS_error_to_string_exec(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
    // Set "renderedTexture" as our colour attachement #0
    GLIS_error_to_string_exec(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0));
    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    GLIS_error_to_string_exec(glDrawBuffers(1, DrawBuffers)); // "1" is the size of DrawBuffers
    return FBOID;
}

#endif //GLNE_GLIS_H
