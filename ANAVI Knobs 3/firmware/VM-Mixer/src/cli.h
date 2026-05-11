#pragma once

// Initialize CLI parser
void cli_parser_init();

// Poll and process CLI input
void cli_parser_update();

// Check if input monitor mode is enabled
bool cli_input_monitor_enabled();

// Logging functions
void logInfo(const char* fmt, ...);
void logWarn(const char* fmt, ...);
void logError(const char* fmt, ...);
