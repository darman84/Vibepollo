/**
 * @file globals.h
 * @brief Declarations for globally accessible variables and functions.
 */
#pragma once

#include <chrono>

// local includes
#include "entry_handler.h"
#include "thread_pool.h"

/**
 * @brief A thread pool for processing tasks.
 */
extern thread_pool_util::ThreadPool task_pool;

/**
 * @brief A boolean flag to indicate whether the cursor should be displayed.
 */
extern bool display_cursor;

/**
 * @brief True while the host cursor is hidden by a game (ShowCursor(FALSE)).
 * When set, absolute mouse move packets from the client are ignored to avoid
 * overriding the game's ClipCursor restriction and causing a position jump.
 */
extern bool cursor_is_captured;

/**
 * @brief Timestamp of the most recent transition from captured to non-captured.
 * Used to enforce a grace period during which absolute mouse position packets
 * are temporarily ignored, giving the client time to switch back to absolute mode.
 */
extern std::chrono::steady_clock::time_point cursor_capture_release_ts;

/**
 * @brief True while a drag-scroll-capable mouse button (middle or X1/mouse4)
 * is held down on the host. Used to proactively block absolute mouse positions
 * and to manage cursor capture state around drag-scroll operations.
 */
extern bool middle_button_held;

#ifdef _WIN32
  // Declare global singleton used for NVIDIA control panel modifications
  #include "platform/windows/nvprefs/nvprefs_interface.h"

/**
 * @brief A global singleton used for NVIDIA control panel modifications.
 */
extern nvprefs::nvprefs_interface nvprefs_instance;
#endif

/**
 * @brief Handles process-wide communication.
 */
namespace mail {
#define MAIL(x) \
  constexpr auto x = std::string_view { \
    #x \
  }

  /**
   * @brief A process-wide communication mechanism.
   */
  extern safe::mail_t man;

  // Global mail
  MAIL(shutdown);
  MAIL(broadcast_shutdown);
  MAIL(video_packets);
  MAIL(audio_packets);
  MAIL(switch_display);

  // Local mail
  MAIL(touch_port);
  MAIL(idr);
  MAIL(invalidate_ref_frames);
  MAIL(gamepad_feedback);
  MAIL(hdr);
#undef MAIL

}  // namespace mail
