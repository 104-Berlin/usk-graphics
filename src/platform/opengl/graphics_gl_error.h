#pragma once

extern char const *gl_error_string(GLenum const err);

#define glCall(x)                                                                            \
    x;                                                                                       \
    {GLenum glob_err = 0;                                                                     \
    while ((glob_err = glGetError()) != GL_NO_ERROR)                                         \
    {                                                                                        \
        printf("GL_ERROR calling \"%s\": %s %s\n", #x, gl_error_string(glob_err), __FILE__); \
    }}
