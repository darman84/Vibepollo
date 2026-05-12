/**
 * @file globals.cpp
 * @brief Definitions for globally accessible variables and functions.
 */
// local includes
#include "globals.h"

safe::mail_t mail::man;
thread_pool_util::ThreadPool task_pool;
bool display_cursor = true;
bool cursor_is_captured = false;
std::chrono::steady_clock::time_point cursor_capture_release_ts;
bool middle_button_held = false;

#ifdef _WIN32
nvprefs::nvprefs_interface nvprefs_instance;
#endif
