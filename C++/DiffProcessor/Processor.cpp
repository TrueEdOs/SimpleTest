#pragma once
#include "Processor.h"
/* 
	First i go through the list and delete all the elements that we can't use to build the list. 
	Then i add the missing elements. 
	Thus, we spend a maximum of O(originalListSize + newListSize) = O(max(n, m)) operations.
	Budniak Eduard 2018
*/
namespace DiffProcessor
{
	Processor::Processor(long limit)
	{
		this->limit = limit;
	}
	Processor::~Processor()
	{
		// Compiler will clear all 
	}

	void Processor::do_process(SortedLimitedList<double> &must_be_equal_to, const SortedLimitedList<double> &expected_output)
	{
		
		// Limit checking 
		if(expected_output.count() > limit || must_be_equal_to.count() > limit)
			throw std::invalid_argument("Limit exceeded!");
		// Two useful pointers
		SortedLimitedList<double>::iterator currentElement = must_be_equal_to.first(), nextElement = (must_be_equal_to.first()++);
		// Go left on right removing useless garbage from the original list
		for(SortedLimitedList<double>::const_iterator it = expected_output.first(); it != expected_output.end(); it++)
		{
			while(currentElement != must_be_equal_to.end() && *currentElement < *it)
			{
				must_be_equal_to.remove(currentElement);
				currentElement = nextElement;
				if(nextElement != must_be_equal_to.end())
					nextElement++;
			}
			
			if(currentElement == must_be_equal_to.end())
			{
				break;
			}
			
			if(*currentElement == *it)
			{
				currentElement = nextElement;
				if(nextElement != must_be_equal_to.end())
					nextElement++;
			}
		}

		// Deleting too big elements
		while(currentElement != must_be_equal_to.end())
		{
			must_be_equal_to.remove(currentElement);
			currentElement = nextElement;
			if(nextElement != must_be_equal_to.end())
				nextElement++;
		}

		currentElement = must_be_equal_to.first();
		// Here we insert the elements which were not in the original list
		for(SortedLimitedList<double>::const_iterator it = expected_output.first(); it != expected_output.end(); it++)
		{
			if(currentElement == must_be_equal_to.end())
			{
				must_be_equal_to.add_last(*it);
				currentElement = must_be_equal_to.end();
			}
			else
			{
				if(*currentElement > *it)
				{
					must_be_equal_to.add_before(currentElement, *it);
				}
				else
				{
					currentElement++;
				}
			}
		}
	}
};
