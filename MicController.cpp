/*
  ==============================================================================

    MicController.cpp
    Created: 16 Jun 2020 4:45:33pm
    Author:  Ani

  ==============================================================================
*/

#include "MicController.h"

std::vector<String> MicController::getMicNames()
{
	std::vector<String> micNames;
	micNames.reserve(MIC_CHANNEL_MAP.size());
	for (auto const& imap : MIC_CHANNEL_MAP)
		micNames.push_back(imap.first);

	return std::vector<String>(micNames);
}

std::map<String, int> MicController::getMicChannelMap()
{
	return MIC_CHANNEL_MAP;
}
