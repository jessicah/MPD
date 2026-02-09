// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright The Music Player Daemon Project

#ifndef MPD_FS_LIST_XX
#define MPD_FS_LIST_XX

#include <forward_list>
#include <filesystem>

class AllocatedPath;

/**
 * Returns a sorted list of files matching the given pattern.
 *
 * Throws on error.
 */
std::forward_list<AllocatedPath>
ListWildcard(std::filesystem::path pattern);

#endif
