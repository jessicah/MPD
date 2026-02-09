// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright The Music Player Daemon Project

#include "List.hxx"
#include "AllocatedPath.hxx"
#include "Glob.hxx"

#ifdef HAVE_CLASS_GLOB
#include "DirectoryReader.hxx"

#include <algorithm>
#include <vector>
#include <filesystem>
#endif

std::forward_list<AllocatedPath>
ListWildcard(Path pattern)
{
#ifdef HAVE_CLASS_GLOB
	//const auto base = pattern.GetBase();
	const auto base = pattern.stem();
	if (StringFindAny(base.c_str(), PATH_LITERAL("*?")) != nullptr) {
		//const Glob glob(base.ToUTF8Throw().c_str());
		const Glob glob(base.c_str());

		std::vector<AllocatedPath> v;
		v.reserve(256);

		const auto directory_path = pattern.parent_path();
		for (auto const &name_fs : std::filesystem::directory_iterator(directory_path))
		{
			try {
				if (glob.Check(name_fs.path().filename().c_str()))
					v.emplace_back(name_fs.path());
			} catch (...) {
			}
		}
		// DirectoryReader reader(directory_path);
		// while (reader.ReadEntry()) {
		// 	const Path name_fs = reader.GetEntry();

		// 	try {
		// 		if (glob.Check(name_fs.ToUTF8Throw().c_str()))
		// 			v.emplace_back(directory_path / name_fs);
		// 	} catch (...) {
		// 	}
		// }

		// TODO: proper Unicode collation?
		std::sort(v.begin(), v.end(),
			  [](const std::filesystem::path a, const std::filesystem::path b){
				  return StringCompare(a.c_str(), b.c_str()) < 0;
			  });

		return {v.begin(), v.end()};
	}
#endif

	return {AllocatedPath(pattern)};
}
