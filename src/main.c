#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "context.h"
#include "platform.h"
#include "defines.h"

#include "config.h"

// Arguments:
static void argument_handle(i32 argc, char** argv, config_t* const config)
{
	assert(config);

	for (i32 i = 1; i < argc; ++i)
	{
		if (strncmp(argv[i], "--iterations=", 13) == 0)
            config->iterationCount = atoi(argv[i] + 13);

        if (strncmp(argv[i], "--rule=", 7) == 0)
            config->ruleNumber = atoi(argv[i] + 7);
        
        if (strncmp(argv[i], "--start_mode=", 13) == 0)
            config->startMode = atoi(argv[i] + 13);
        
        if (strncmp(argv[i], "--cell_width=", 13) == 0)
            config->cellWidth = atoi(argv[i] + 13);

		if (strncmp(argv[i], "--cell=", 7) == 0)
            config->cellCharacter = argv[i][7];

		if (strncmp(argv[i], "--space=", 8) == 0)
            config->spaceCharacter = argv[i][8];
	}
}

// View:
static void report_config_warning(config_warn warn)
{
	if (warn == config_warn_none)
		return;

	if ((warn & config_warn_cell_width))
		fprintf(stderr, "Warning: Cell width must be a value between 1 and 255. Using default value: %d\n", DEFAULT_CELL_WIDTH);

	if ((warn & config_warn_itaration_count))
		fprintf(stderr, "Warning: Iteration must be a value between 1 and 255. Using default value: %d\n", DEFAULT_ITERATION_COUNT);

	if ((warn & config_warn_rule_number))
		fprintf(stderr, "Warning: Rule number must be a value between 1 and 255. Using default value: %d\n", DEFAULT_RULE_NUMBER);

	if ((warn & config_warn_start_mode))
		fprintf(stderr, "Warning: Start mode must be 0 (random) or 1 (center). Using default value: %d\n", DEFAULT_START_MODE);

	if ((warn & config_warn_cell_char))
		fprintf(stderr, "Warning: Cell character must be a char. Using default value: %c\n", DEFAULT_CELL_CHAR);

	if ((warn & config_warn_space_char))
		fprintf(stderr, "Warning: Space character must be a char. Using default value: %c\n", DEFAULT_SPACE_CHAR);
}

static void display_header_information(u8 rule[], const config_t* const config)
{
    printf("-=-= Report (Paulo C. - 25122026) =-=-\n");
	printf("- Cell width      = %d\n", config->cellWidth);
	printf("- Iteration Count = %d\n", config->iterationCount);
	printf("- Start mode      = %d\n", config->startMode);
	printf("- Rule Number     = %d\n", config->ruleNumber);
	printf("- Cell character  = %c\n", config->cellCharacter);
	printf("- Space character = %c\n", config->spaceCharacter);
	printf("\n");

	printf("Rule Number breakdown:\n");
	printf("| 111 110 101 100 011 010 001 000 |\n");
	printf("|  %d   %d   %d   %d   %d   %d   %d   %d  |\n", rule[7], rule[6], rule[5], rule[4], rule[3], rule[2], rule[1], rule[0]);
	printf("\n");

	printf("Grid result:\n");
	printf("\n");
}

static void draw_state(u8 cell[], u8 width, const config_t* const config)
{
	for(u8 j = 0; j < width; ++j)
		printf("%c", cell[j] == 1 ? (char)config->cellCharacter : (char)config->spaceCharacter);

    printf("\n");
}

int main(int argc, char** argv)
{
	config_t config;
	{
		config_initialize(&config);
		argument_handle(argc, argv, &config);
		
		config_warn warning = config_sanitize(&config);
		report_config_warning(warning);
	}

	context_t context;
	{
		context_error error = context_initialize(&context, &config);
		if (error == context_error_malloc_failed)
		{
			fprintf(stderr, "An error occurred when allocating memory for the cell arrays.\n");
			return 1;
		}

		display_header_information(context.ruleArray, &config);
	}
	
	for(u8 i = 0; i < config.iterationCount; ++i)
	{
		context_step(&context);
		draw_state(context.cell1, config.cellWidth, &config);
		context_override_state(&context);
		
		SLEEP_MS(100); 
	}
}