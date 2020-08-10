/*
  ==============================================================================

    MutingMap.h
    Created: 7 Aug 2020 4:28:32pm
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include <set>
#include <map>
//std::set<std::set<int>> mutingSets = {
//	{38, 39, 40, 41, 42}, // Snare set
//	{48, 49, 50, 51, 52, 54, 55, 56, 57, 59} // Hi-Hat set
//};

class MutingMap {
private:
	std::map<int, std::set<int>> noteIndexedMutingMap;
	const std::set<std::set<int>> mutingSets = {
		{38, 39, 40, 41, 42}, // Snare set
		{48, 49, 50, 51, 52, 54, 55, 56, 57, 59}, // Hi-Hat set
		{62, 63}, // Ride Crash - Choke
		{77, 78}, // Cymbal 1 - Choke
		{79, 80} // Cymbal2 - Choke
	};

public:
	MutingMap() {
		auto it = mutingSets.begin();
		auto end = mutingSets.end();

		while (it != end) {
			for (const int currNote : *it ) {
				noteIndexedMutingMap[currNote] = *it;
			}
			it++;
		}
	}
	std::set<int> getMutingSet(int noteNumber) {
		return noteIndexedMutingMap[noteNumber];
	}

};