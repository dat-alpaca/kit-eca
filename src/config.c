#include <assert.h>
#include "config.h"
#include "defines.h"

void config_initialize(config_t* const config)
{
	assert(config);

	config->cellCharacter 	= DEFAULT_CELL_CHAR;
	config->spaceCharacter  = DEFAULT_SPACE_CHAR;

	config->cellWidth 		= DEFAULT_CELL_WIDTH;
	config->iterationCount 	= DEFAULT_ITERATION_COUNT;
	config->ruleNumber 		= DEFAULT_RULE_NUMBER;
	config->startMode 		= DEFAULT_START_MODE;
}

config_warn config_sanitize(config_t* const config)
{
	config_warn warnings = config_warn_none;

	if (config->cellWidth == 0 || config->cellWidth >= UINT8_MAX)
	{
		config->cellWidth = DEFAULT_CELL_WIDTH;	
		warnings |= config_warn_cell_width;
	}

	if (config->iterationCount == 0 || config->iterationCount >= UINT8_MAX)
	{
		config->iterationCount = DEFAULT_ITERATION_COUNT;
		warnings |= config_warn_itaration_count;
	}

	if (config->ruleNumber >= UINT8_MAX)
	{
		config->ruleNumber = DEFAULT_RULE_NUMBER;
		warnings |= config_warn_rule_number;
	}

	if (config->startMode != 0 && config->startMode != 1)
	{
		config->startMode = DEFAULT_START_MODE;
		warnings |= config_warn_start_mode;
	}

    if (config->cellCharacter == 0 || config->cellCharacter >= UINT8_MAX)
    {
        config->cellCharacter = DEFAULT_CELL_CHAR;	
		warnings |= config_warn_cell_char;
    }
    
    if (config->spaceCharacter == 0 || config->spaceCharacter >= UINT8_MAX)
    {
        config->spaceCharacter = DEFAULT_SPACE_CHAR;	
		warnings |= config_warn_space_char;
    }

	return warnings;
}