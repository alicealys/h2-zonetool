#pragma once
#include "../zonetool.hpp"

namespace zonetool
{
	class IRawFile
	{
	private:
		std::string name_;
		RawFile* asset_ = nullptr;

	public:
		static void dump(RawFile* asset);
	};
}