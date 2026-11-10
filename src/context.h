#pragma once
#include "config.h"
#include "defines.h"

typedef enum context_error
{
    context_error_none = 0,
    context_error_malloc_failed,
} context_error;

typedef struct context_t
{
    u8* cell1;
    u8* cell2;
    u8 ruleArray[RULE_ARRAY_SIZE];
    u8 cellWidth;
} context_t;

context_error context_initialize(context_t* const context, const config_t* const config);

void context_step(context_t* const context);

void context_override_state(context_t* const context);