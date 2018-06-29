#pragma once
#include <stdexcept>
#include "SortedLimitedList.h"

namespace DiffProcessor
{
	class Processor
	{
		// Add to control lists size
		long limit;
	public:
		Processor(long limit);
		~Processor();
		void do_process(SortedLimitedList<double> &must_be_equal_to, const SortedLimitedList<double> &expected_output);
	};
};
