#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "context.h"

static void context_rule_array_populate(u8 ruleArray[RULE_ARRAY_SIZE], u8 ruleNumber)
{
	for (u8 i = 0; i < RULE_ARRAY_SIZE; i++)
		ruleArray[i] = (ruleNumber >> i) & 0x1;
}

static void context_initial_state_populate(context_t* const context, start_mode mode)
{
    assert(context);
    assert(context->cell1);
    assert(context->cell2);
    assert(context->ruleArray);

    u8 cellWidth = context->cellWidth;

	if (mode == start_mode_random)
	{
        for (u8 i = 0; i < cellWidth; ++i)
			context->cell1[i] = arc4random() % 2;

		return;
    }
	
	u8 center = (cellWidth - (cellWidth % 2)) / 2;
	for(u8 i = 0; i < cellWidth; ++i)
		context->cell1[i] = (i == center) ? 1 : 0;
}

context_error context_initialize(context_t* const context, const config_t* const config)
{
    assert(context->ruleArray);

    context->cellWidth = config->cellWidth;
    context_rule_array_populate(context->ruleArray, config->ruleNumber);

    context->cell1 = (u8*)malloc(sizeof(u8) * config->cellWidth);
    context->cell2 = (u8*)malloc(sizeof(u8) * config->cellWidth);

    if (!context->cell1 || !context->cell2)
        return context_error_malloc_failed;

    context_initial_state_populate(context, config->startMode);

    return context_error_none;
}

void context_step(context_t* const context)
{
    assert(context);

    u8 cellWidth = context->cellWidth;
    u8* cell1 = context->cell1;
    u8* cell2 = context->cell2;

	for(u8 i = 0; i < cellWidth; ++i)
	{
		u8 left   = cell1[(i == 0) ? cellWidth - 1 : i - 1];
		u8 center = cell1[i];
		u8 right  = cell1[(i == cellWidth - 1) ? 0 : i + 1];

		u8 index = (left << 2) | (center << 1) | right;
    	cell2[i] = context->ruleArray[index];
	}
}

void context_override_state(context_t* const context)
{
    assert(context);
    memcpy(context->cell1, context->cell2, sizeof(u8) * context->cellWidth);
}