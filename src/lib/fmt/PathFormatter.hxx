// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright The Music Player Daemon Project

#pragma once

#include "fs/Path.hxx"

#include <fmt/format.h>

#include <concepts>
#include <filesystem>

template<std::convertible_to<std::filesystem::path> T>
struct fmt::formatter<T> : formatter<string_view>
{
	template<typename FormatContext>
	auto format(std::filesystem::path path, FormatContext &ctx) const {
		// Missing a ToUTF8() call, so this may need fixing...
		return formatter<string_view>::format(path.string(), ctx);
	}
};
