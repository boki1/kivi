#ifndef KIVI_SRC_BACKEND_ARCH_ALL_HH_
#define KIVI_SRC_BACKEND_ARCH_ALL_HH_

#include <string_view>

#include <compiler/machine_target.hh>

namespace compiler
{

	template<typename T>
	[[nodiscard]] machine_target configure_target();

	struct x86_64
	{
		static constexpr std::string_view name = "x86_64";
	};

	template<>
	[[nodiscard]] machine_target configure_target<x86_64>();

}

#endif //KIVI_SRC_BACKEND_ARCH_ALL_HH_
