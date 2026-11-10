#pragma once
#include "defines.h"
#include "start_mode.h"

typedef enum config_warn : u8
{
	config_warn_none			= 0,
	config_warn_cell_width		= 1 << 0,
	config_warn_itaration_count	= 1 << 1,
	config_warn_rule_number		= 1 << 2,
	config_warn_start_mode		= 1 << 3,
	config_warn_cell_char		= 1 << 4,
	config_warn_space_char		= 1 << 5,
} config_warn;

typedef struct config_t
{
	start_mode startMode;
	u8 cellWidth;
	u8 ruleNumber;
	u8 iterationCount;
	u8 cellCharacter;
	u8 spaceCharacter;
} config_t;

void config_initialize(config_t* const config);

config_warn config_sanitize(config_t* const config);