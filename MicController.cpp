/*
  ==============================================================================

    MicController.cpp
    Created: 16 Jun 2020 4:45:33pm
    Author:  Ani

  ==============================================================================
*/

#include "MicController.h"

MicController::MicController(AudioProcessorValueTreeState* treeState)
{
	this->treeState = treeState;
}

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

std::map<String, float> MicController::getMicGains(String generalControllerName, String specificControllerName)
{

	float roomMono = (*this->treeState->getRawParameterValue(generalControllerName + " Room Mono Mix")) * (*this->treeState->getRawParameterValue("Master Room Mix"));
	float roomStereo = (*this->treeState->getRawParameterValue(generalControllerName + " Room Stereo Mix")) * (*this->treeState->getRawParameterValue("Master Room Mix"));
	float roomFar = (*this->treeState->getRawParameterValue(generalControllerName + " Room Far Mix")) * (*this->treeState->getRawParameterValue("Master Room Mix"));
	float overHead = *this->treeState->getRawParameterValue(generalControllerName + " Overhead Mix");
	//float master = (*this->treeState->getRawParameterValue(specificControllerName + " Master Mix")) * (*this->treeState->getRawParameterValue("Master Mix"));
	float master = (*this->treeState->getRawParameterValue("Master Mix"));


	float kickIn = *this->treeState->getRawParameterValue("Kick In Mix");
	float kickOut = *this->treeState->getRawParameterValue("Kick Out Mix");
	float kickSub = *this->treeState->getRawParameterValue("Kick Sub Mix");
	float snareBottom = *this->treeState->getRawParameterValue("Snare Bottom Mix");
	float snareTop = *this->treeState->getRawParameterValue("Snare Top Mix");
	float tom1Close = *this->treeState->getRawParameterValue("Tom1 Close");
	float tom2Close = *this->treeState->getRawParameterValue("Tom2 Close");
	float tom3Close = *this->treeState->getRawParameterValue("Tom3 Close");
	float tom4Close = *this->treeState->getRawParameterValue("Tom4 Close");
	float tom5Close = *this->treeState->getRawParameterValue("Tom5 Close");
	float hiHatClose = *this->treeState->getRawParameterValue("HiHat Close");
	float rideClose = *this->treeState->getRawParameterValue("Ride Close");


	std::map<String, float> micGains = {
		{"kickin", float(0.2f*master*kickIn)},
		{"kickout", float(0.2f*master*kickOut)},
		{"kicksub", float(0.2f* master * kickSub)},
		{"snrtop", float(0.2f*master*snareTop)},
		{"snrbot", float(0.2f*master*snareBottom)},
		{"tom1", float(0.5f*master*tom1Close)},
		{"tom2", float(0.5f*master*tom2Close)},
		{"tom3", float(0.5f*master*tom3Close)},
		{"tom4", float(0.5f*master*tom4Close)},
		{"tom5", float(0.5f*master*tom5Close)},
		{"hh", float(0.5f*master*hiHatClose)},
		{"ride", float(0.5*master*rideClose)},
		{"roommono", float(0.2*roomMono*master)},
		{"roomstereo", float(0.2*roomStereo*master)},
		{"roomfar", float(0.2*roomFar*master)},
		{"oh", float(0.5*overHead*master)}
	};
	// TODO: jassert if all the entries have been filled
	if (generalControllerName.compare("Cymbal") == 0) {
		applyCymbalControl(&micGains, specificControllerName);
	}
	return micGains;
}

std::map<String, float> MicController::getEmptyMicGains() {
	std::map<String, float> micGains;
	std::vector<String> micNames = getMicNames();
	for ( String mic : micNames) {
		micGains[mic] = 0.0f;
	}
	return micGains;
}

void MicController::applyCymbalControl(std::map<String, float> *micGains, String specificInstrumentName) {

	float roomFar = *this->treeState->getRawParameterValue(specificInstrumentName + " Room Far");
	float roomStereo = *this->treeState->getRawParameterValue(specificInstrumentName + " Room Stereo");
	float roomMono = *this->treeState->getRawParameterValue(specificInstrumentName + " Room Mono");
	float overhead = *this->treeState->getRawParameterValue(specificInstrumentName + " Overhead");

	(*micGains)["roomfar"] *= roomFar;
	(*micGains)["roomstereo"] *= roomStereo;
	(*micGains)["roommono"] *= roomMono;
	(*micGains)["oh"] *= overhead;
}