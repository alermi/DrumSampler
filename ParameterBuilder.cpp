#include "ParameterBuilder.h"

AudioProcessorValueTreeState::ParameterLayout ParameterBuilder::createParameterLayout()
{
	//std::vector<std::unique_ptr<AudioParameterFloat>> params;

	AudioProcessorValueTreeState::ParameterLayout layout;

	addKickParameters(layout);
	addSnareParameters(layout);


	auto tom1Direct = (std::make_unique<AudioParameterFloat>("Tom1 Direct Mix", "Tom1 Direct Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto tom2Direct = (std::make_unique<AudioParameterFloat>("Tom2 Direct Mix", "Tom2 Direct Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto tom3Direct = (std::make_unique<AudioParameterFloat>("Tom3 Direct Mix", "Tom3 Direct Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto masterRoomMix = (std::make_unique<AudioParameterFloat>("Master Room Mix", "Master Room Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto masterMix = (std::make_unique<AudioParameterFloat>("Master Mix", "Master Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));

	auto group = std::make_unique<AudioProcessorParameterGroup>("Others", "Others", "|",
		std::move(masterRoomMix),
		std::move(masterMix),
		std::move(tom1Direct),
		std::move(tom2Direct),
		std::move(tom3Direct));

	layout.add(std::move(group));
	return layout;
}
void ParameterBuilder::addKickParameters(AudioProcessorValueTreeState::ParameterLayout& layout) {

	auto inOut = (std::make_unique<AudioParameterFloat>("Kick In/Out Mix", "Kick In/Out Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto sub = (std::make_unique<AudioParameterFloat>("Kick Sub Mix", "Kick Sub Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto direct = (std::make_unique<AudioParameterFloat>("Kick Direct Mix", "Kick Direct Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto monoPan = (std::make_unique<AudioParameterFloat>("Kick Mono Pan", "Kick Mono Pan", NormalisableRange<float>(0.0f, 1.0f), 0.5f));


	auto specificGroup = std::make_unique<AudioProcessorParameterGroup>("Specific", "Specific", "|",
		std::move(inOut),
		std::move(sub),
		std::move(direct),
		std::move(monoPan));


	auto kickGeneral = std::make_unique<AudioProcessorParameterGroup>("Kick", "Kick", "|",
		std::move(specificGroup),
		std::move((getGeneralInstrumentParameters("Kick"))));

	layout.add(std::move(kickGeneral));

}

void ParameterBuilder::addSnareParameters(AudioProcessorValueTreeState::ParameterLayout& layout) {
	auto directSnare = (std::make_unique<AudioParameterFloat>("Snare Direct Mix", "Snare Direct Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto bottom = (std::make_unique<AudioParameterFloat>("Snare Bottom Mix", "Snare Bottom Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto monoPan = (std::make_unique<AudioParameterFloat>("Snare Mono Pan", "Snare Mono Pan", NormalisableRange<float>(0.0f, 1.0f), 0.5f));

	auto specificGroup = std::make_unique<AudioProcessorParameterGroup>("Specific", "Specific", "|",
		std::move(directSnare),
		std::move(bottom),
		std::move(monoPan));


	auto snareGeneral = std::make_unique<AudioProcessorParameterGroup>("Snare", "Snare", "|",
		std::move(specificGroup),
		std::move((getGeneralInstrumentParameters("Snare"))));

	layout.add(std::move(snareGeneral));

}
std::unique_ptr<AudioProcessorParameterGroup> ParameterBuilder::getGeneralInstrumentParameters(String instrumentName)
{
	auto oh = (std::make_unique<AudioParameterFloat>(instrumentName + " Overhead Mix", instrumentName + " Overhead Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto room = (std::make_unique<AudioParameterFloat>(instrumentName + " Room Mix", instrumentName + " Room Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto master = (std::make_unique<AudioParameterFloat>(instrumentName + " Master Mix", instrumentName + " Master Mix", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
	auto stereoPanL = (std::make_unique<AudioParameterFloat>(instrumentName + " Stereo Pan L", instrumentName + " Stereo Pan L", NormalisableRange<float>(0.0f, 1.0f), 0.0f));
	auto stereoPanR = (std::make_unique<AudioParameterFloat>(instrumentName + " Stereo Pan R", instrumentName + " Stereo Pan R", NormalisableRange<float>(0.0f, 1.0f), 1.0f));

	auto group = std::make_unique<AudioProcessorParameterGroup>("GeneralInstrument", "GeneralInstrument", "|",
		std::move(oh),
		std::move(room),
		std::move(master),
		std::move(stereoPanL),
		std::move(stereoPanR));
	return ((group));
}
