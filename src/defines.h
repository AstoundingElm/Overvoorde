#pragma once
#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define _DEBUG 

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// Signed int types.
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

// Floating point types
typedef float f32;
typedef double f64;

// Boolean types
typedef int b32;
typedef char b8;

#define debugBreak() __builtin_trap()
#define nullptr NULL
#define TUT5_MAX_EXTENSION_COUNT 20
#define TUT5_MAX_LAYER_COUNT 20
#define TUT1_MAX_QUEUE_FAMILY 20
#define MAX_DEVICES 10



