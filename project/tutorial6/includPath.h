#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GL/glut.h"
#include <time.h>
#include <random>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "gl/gl.h"

#define MAIN_MENU_WIRE 1
#define MAIN_MENU_QUIT 2
#define MAIN_MENU_LUMIOSITY 3
#define MAIN_MENU_FILL 101
#define MAIN_MENU_MOVERIGHT 102
#define MAIN_MENU_MOVELEFT 103
#define MAIN_MENU_LUMIOSITYFALSE 104
#define MAIN_MENU_MOVEUP 105
#define MAIN_MENU_MOVEDOWN 106
#define SUB_MENU_RED_BG 8
#define SUB_MENU_WHITE_BG 7
#define SUB_MENU_GREY_BG 99