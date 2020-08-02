#include "ParameterBuilder.h"

AudioProcessorValueTreeState::ParameterLayout ParameterBuilder::createParameterLayout()
{
	//std::vector<std::unique_ptr<AudioParameterFloat>> params;

	AudioProcessorValueTreeState::ParameterLayout layout;

	addKickParameters(layout);
	addSnareParameters(layout);
	addTomParameters(layout);
	addCymbalParameters(layout);
	addCymbalBalanceParameters(layout);

	auto masterRoomMix = (std::make_unique<AudioParameterFloat>("Master Room Mix", "Master Room Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto masterMix = (std::make_unique<AudioParameterFloat>("Master Mix", "Master Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));

	for (String micName : MicController::getMicNames()) {

	}
	auto panGroup = std::make_unique<AudioProcessorParameterGroup>("Pans", "Pans", "|");
	for (String micName : MicController::getMicNames()) {
		panGroup.get()->addChild(getPanParameters(micName));
	}
	layout.add(std::move(panGroup));

	auto masterGroup = std::make_unique<AudioProcessorParameterGroup>("Master", "Master", "|",
		std::move(masterRoomMix),
		std::move(masterMix));

	layout.add(std::move(masterGroup));
	return layout;
}
void ParameterBuilder::addKickParameters(AudioProcessorValueTreeState::ParameterLayout& layout) {

	auto in = (std::make_unique<AudioParameterFloat>("Kick In Mix", "Kick In Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto out = (std::make_unique<AudioParameterFloat>("Kick Out Mix", "Kick Out Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto sub = (std::make_unique<AudioParameterFloat>("Kick Sub Mix", "Kick Sub Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));


	auto specificGroup = std::make_unique<AudioProcessorParameterGroup>("Specific", "Specific", "|",
		std::move(in),
		std::move(out),
		std::move(sub));
		//std::move((getSpecificInstrumentParameters("Kick", false))));


	auto kickGeneral = std::make_unique<AudioProcessorParameterGroup>("Kick", "Kick", "|",
		std::move(specificGroup),
		std::move((getGeneralInstrumentParameters("Kick"))));

	layout.add(std::move(kickGeneral));

}

void ParameterBuilder::addSnareParameters(AudioProcessorValueTreeState::ParameterLayout& layout) {
	auto bottom = (std::make_unique<AudioParameterFloat>("Snare Bottom Mix", "Snare Bottom Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto top = (std::make_unique<AudioParameterFloat>("Snare Top Mix", "Snare Top Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));

	auto specificGroup = std::make_unique<AudioProcessorParameterGroup>("Specific", "Specific", "|",
		std::move(bottom),
		std::move(top));
		//std::move(getSpecificInstrumentParameters("Snare", false)));


	auto snareGeneral = std::make_unique<AudioProcessorParameterGroup>("Snare", "Snare", "|",
		std::move(specificGroup),
		std::move(getGeneralInstrumentParameters("Snare")));

	layout.add(std::move(snareGeneral));

}


void ParameterBuilder::addTomParameters(AudioProcessorValueTreeState::ParameterLayout& layout) {

	auto specificGroup = std::make_unique<AudioProcessorParameterGroup>("Specific", "Specific", "|",
		std::move(getCloseMicParameter("Tom1")),
		std::move(getCloseMicParameter("Tom2")),
		std::move(getCloseMicParameter("Tom3")),
		std::move(getCloseMicParameter("Tom4")),
		std::move(getCloseMicParameter("Tom5")));


	auto snareGeneral = std::make_unique<AudioProcessorParameterGroup>("Tom", "Tom", "|",
		std::move(specificGroup),
		std::move(getGeneralInstrumentParameters("Tom")));

	layout.add(std::move(snareGeneral));

}

void ParameterBuilder::addCymbalParameters(AudioProcessorValueTreeState::ParameterLayout& layout) {

	auto specificGroup = std::make_unique<AudioProcessorParameterGroup>("Specific", "Specific", "|",
		std::move(getCloseMicParameter("HiHat")),
		std::move(getCloseMicParameter("Ride")));
		//std::move(getSpecificInstrumentParameters("Crash1", false)),
		//std::move(getSpecificInstrumentParameters("Crash2", false)),
		//std::move(getSpecificInstrumentParameters("China", false)),
		//std::move(getSpecificInstrumentParameters("Stack1", false)),
		//std::move(getSpecificInstrumentParameters("Stack2", false)),
		//std::move(getSpecificInstrumentParameters("Splash", false)));


	auto snareGeneral = std::make_unique<AudioProcessorParameterGroup>("Cymbal", "Cymbal", "|",
		std::move(specificGroup),
		std::move(getGeneralInstrumentParameters("Cymbal")));

	layout.add(std::move(snareGeneral));

}
std::unique_ptr<AudioProcessorParameterGroup> ParameterBuilder::getGeneralInstrumentParameters(String generalInstrumentName)
{
	auto oh = (std::make_unique<AudioParameterFloat>(generalInstrumentName + " Overhead Mix", generalInstrumentName + " Overhead Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto roomFar = (std::make_unique<AudioParameterFloat>(generalInstrumentName + " Room Far Mix", generalInstrumentName + " Room Far Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto roomMono = (std::make_unique<AudioParameterFloat>(generalInstrumentName + " Room Mono Mix", generalInstrumentName + " Room Mono Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto roomStereo = (std::make_unique<AudioParameterFloat>(generalInstrumentName + " Room Stereo Mix", generalInstrumentName + " Room Stereo Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));

	auto group = std::make_unique<AudioProcessorParameterGroup>("GeneralInstrument", "GeneralInstrument", "|",
		std::move(oh),
		std::move(roomMono),
		std::move(roomStereo),
		std::move(roomFar));
	return group;
}

std::unique_ptr<AudioProcessorParameter> ParameterBuilder::getCloseMicParameter(String specificInstrumentName)
{	
	std::unique_ptr<AudioProcessorParameterGroup> group;

	//auto master = (std::make_unique<AudioParameterFloat>(specificInstrumentName + " Master Mix", specificInstrumentName + " Master Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	//auto pan = (std::make_unique<AudioParameterFloat>(specificInstrumentName + " Pan", specificInstrumentName + " Pan", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	//if (hasCloseMic) {
	auto close = (std::make_unique<AudioParameterFloat>(specificInstrumentName + " Close", specificInstrumentName + " Close", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	return close;
		//group = std::make_unique<AudioProcessorParameterGroup>("SpecificInstrument", "SpecificInstrument", "|",
			//std::move(close);
			//std::move(master),
			//std::move(pan));
	//}
	//else {
	//	//group = std::make_unique<AudioProcessorParameterGroup>("SpecificInstrument", "SpecificInstrument", "|",
	//		//std::move(master),
	//		//std::move(pan));
	//	return NULL;

	//}

	//return group;
}


void ParameterBuilder::addCymbalBalanceParameters(AudioProcessorValueTreeState::ParameterLayout& layout) {
	auto bottom = (std::make_unique<AudioParameterFloat>("Snare Bottom Mix", "Snare Bottom Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));

	auto balances = std::make_unique<AudioProcessorParameterGroup>("Cymbal Balance", "Cymbal Balance", "|",
		std::move(getCymbalBalanceParameters("Room Mono")),
		std::move(getCymbalBalanceParameters("Room Stereo")),
		std::move(getCymbalBalanceParameters("Room Far")),
		std::move(getCymbalBalanceParameters("Overhead")));


	layout.add(std::move(balances));
}


std::unique_ptr<AudioProcessorParameterGroup> ParameterBuilder::getCymbalBalanceParameters(String micType)
{

	auto hihat = (std::make_unique<AudioParameterFloat>("HiHat " + micType, "HiHat " + micType, NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto ride = (std::make_unique<AudioParameterFloat>("Ride " + micType, "Ride " + micType, NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto crash1 = (std::make_unique<AudioParameterFloat>("Crash1 " + micType, "Crash1 " + micType, NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto crash2 = (std::make_unique<AudioParameterFloat>("Crash2 " + micType, "Crash2 " + micType, NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto china = (std::make_unique<AudioParameterFloat>("China " + micType, "China " + micType, NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto stack1 = (std::make_unique<AudioParameterFloat>("Stack1 " + micType, "Stack1 " + micType, NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto stack2 = (std::make_unique<AudioParameterFloat>("Stack2 " + micType, "Stack2 " + micType, NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto splash = (std::make_unique<AudioParameterFloat>("Splash " + micType, "Splash " + micType, NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto group = std::make_unique<AudioProcessorParameterGroup>(micType, micType, "|",
		std::move(hihat),
		std::move(ride),
		std::move(crash1),
		std::move(crash2),
		std::move(china),
		std::move(stack1),
		std::move(stack2),
		std::move(splash));
	return group;
}


std::unique_ptr<AudioProcessorParameterGroup> ParameterBuilder::getPanParameters(String micName) {

	auto leftPan = (std::make_unique<AudioParameterFloat>(micName + " Left Pan", micName + " Left Pan", NormalisableRange<float>(0.0f, 1.0f), 0.0f));
	auto rightPan = (std::make_unique<AudioParameterFloat>(micName + " Right Pan", micName + " Right Pan", NormalisableRange<float>(0.0f, 1.0f), 1.0f));

	return std::make_unique<AudioProcessorParameterGroup>(micName + " Pans", micName + " Pans", "|",
		std::move(leftPan),
		std::move(rightPan));
}