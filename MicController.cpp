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

std::map<String, float> MicController::getMicGains(String controllerName)
{

	float roomFader = (*this->treeState->getRawParameterValue(controllerName + " Room Mix")) * (*this->treeState->getRawParameterValue("Master Room Mix"));
	float master = (*this->treeState->getRawParameterValue(controllerName + " Master Mix")) * (*this->treeState->getRawParameterValue("Master Mix"));
	float overHead = *this->treeState->getRawParameterValue(controllerName + " Overhead Mix");

	float kickInOut = *this->treeState->getRawParameterValue("Kick In/Out Mix");
	float kickSub = *this->treeState->getRawParameterValue("Kick Sub Mix");
	float kickDirect = *this->treeState->getRawParameterValue("Kick Direct Mix");
	float snareDirect = *this->treeState->getRawParameterValue("Snare Direct Mix");
	float snareBottomTop = *this->treeState->getRawParameterValue("Snare Bottom Mix");
	float tom1Direct = *this->treeState->getRawParameterValue("Tom1 Direct Mix");
	float tom2Direct = *this->treeState->getRawParameterValue("Tom2 Direct Mix");
	float tom3Direct = *this->treeState->getRawParameterValue("Tom3 Direct Mix");
	//{ "kickin", "kickout", "snarebot", "snaretop", "tom1", "tom2", "tom3", "ride", "roommono", "roomstereo", "roomfar", "oh" };


	//micGains["kickin"] = float(0.2f*master*kickDirect*kickInOut);
	//micGains["kickout"] = float(0.2f*master*kickDirect*(1 - kickInOut));
	//micGains["kicksub"] = float(0.2f* master * kickDirect * kickSub);
	//micGains["snrbot"] = float(0.2f*master*snareDirect*snareBottomTop);
	//micGains["snrtop"] = float(0.2f*master*snareDirect*(1 - snareBottomTop));
	//micGains["tom1"] = float(0.5f*master*tom1Direct);
	//micGains["tom2"] = float(0.5f*master*tom2Direct);
	//micGains["tom3"] = float(0.5f*master*tom3Direct);
	//micGains["ride"] = float(0.0f);
	//micGains["roommono"] = float(0.2*roomFader*master);
	//micGains["roomstereo"] = float(0.2*roomFader*master);
	//micGains["roomfar"] = float(0.2*roomFader*master);
	//micGains["oh"] = float(0.2*overHead*master);


	std::map<String, float> micGains = {
		{"kickin", float(0.2f*master*kickDirect*kickInOut)},
		{"kickout", float(0.2f*master*kickDirect*(1 - kickInOut))},
		{"kicksub", float(0.2f* master * kickDirect * kickSub)},
		{"snrtop", float(0.2f*master*snareDirect*(1 - snareBottomTop))},
		{"snrbot", float(0.2f*master*snareDirect*snareBottomTop)},
		{"tom1", float(0.5f*master*tom1Direct)},
		{"tom2", float(0.5f*master*tom2Direct)},
		{"tom3", float(0.5f*master*tom3Direct)},
		{"tom4", 1},
		{"tom5", 1},
		{"hh", 1},
		{"ride", 1},
		{"roommono", float(0.2*roomFader*master)},
		{"roomstereo", float(0.2*roomFader*master)},
		{"roomfar", float(0.2*roomFader*master)},
		{"oh", float(0.2*overHead*master)}
	};
	// TODO: jassert if all the entries have been filled
	return micGains;
}
//{ "kickin", "kickout", "snrbot", "snrtop", "tom1", "tom2", "tom3", "ride", "roommono", "roomstereo",
//"roomfar", "oh" };
//micVector.push_back(float(0.2*master*kickDirect*kickInOut)); // kick_in 1
//micVector.push_back(float(0.2*master*kickDirect*(1 - kickInOut))); // kick_out 1
//micVector.push_back(float(0.2*master*snareDirect*snareBottomTop)); // snare_bottom
//micVector.push_back(float(0.2*master*snareDirect*(1 - snareBottomTop))); // snare_top
//micVector.push_back(float(0.5*master*tom1Direct)); // tom1
//micVector.push_back(float(0.5*master*tom2Direct)); // tom2
//micVector.push_back(float(0.5*master*tom3Direct)); // tom3
////Todo: set ride
//micVector.push_back(float(0)); // ride
//micVector.push_back(float(0.2*roomFader*master)); // room_mono
//micVector.push_back(float(0.2*roomFader*master)); // room_main
//micVector.push_back(float(0.2*roomFader*master)); // room_wide
//micVector.push_back(float(0.2*overHead*master)); // overhead
std::map<String, float> MicController::getEmptyMicGains() {
	std::map<String, float> micGains;
	std::vector<String> micNames = getMicNames();
	for ( String mic : micNames) {
		micGains[mic] = 0.0f;
	}
	return micGains;
}

void MicController::applyCommonControls(std::map<String, float> *micGains) {


}