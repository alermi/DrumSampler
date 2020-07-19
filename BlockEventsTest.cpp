/*
  ==============================================================================

    BlockEventsTest.cpp
    Created: 14 Jul 2020 9:43:09pm
    Author:  Ani

  ==============================================================================
*/


#include "BlockEvents.h"
#include "../JuceLibraryCode/JuceHeader.h"

class BlockEventsTest : public UnitTest
{
public:
	BlockEventsTest() : UnitTest("Testing BlockEvents") {}

	BlockEvents blockEvents;

	void initialise() override
	{
		blockEvents.setBlockSize(100);
	}
	void runTest() override
	{
		//TODO: Test changing the block size
		//beginTest("Part 1");
		//blockEvents.processEvent(90, false);
		//blockEvents.processEvent(12, true);
		//blockEvents.processEvent(90, true);
		//blockEvents.processEvent(90, false);
		//blockEvents.processEvent(93, false);
		//blockEvents.finishReceivingHits();
		//
		//BlockEvents::Event nextEvent = blockEvents.getNextEvent();
		//expect(nextEvent.timeStamp == 12 && nextEvent.isNoteOn == true);
		//nextEvent = blockEvents.getNextEvent();
		//expect(nextEvent.timeStamp == 90 && nextEvent.isNoteOn == true);
		//nextEvent = blockEvents.getNextEvent();
		//expect(nextEvent.timeStamp == 93 && nextEvent.isNoteOn == false);
		//expect(blockEvents.isEmpty());


		//beginTest("Part 2");
		//blockEvents.startReceivingHits();
		//blockEvents.finishReceivingHits();
		//expect(blockEvents.isEmpty());

		//beginTest("Part 3");
		//blockEvents.startReceivingHits();
		//blockEvents.processEvent(0, false);
		//blockEvents.processEvent(53, true);
		//blockEvents.processEvent(3, true);
		//blockEvents.processEvent(53, false);
		//blockEvents.processEvent(0, true);
		//blockEvents.processEvent(0, true);
		//blockEvents.processEvent(3, true);
		//blockEvents.processEvent(3, true);
		//blockEvents.processEvent(87, false);
		//blockEvents.processEvent(53, true);
		//blockEvents.finishReceivingHits();

		//nextEvent = blockEvents.getNextEvent();
		//expect(nextEvent.timeStamp == 0 && nextEvent.isNoteOn == true);
		//nextEvent = blockEvents.getNextEvent();
		//expect(nextEvent.timeStamp == 3 && nextEvent.isNoteOn == true);
		//nextEvent = blockEvents.getNextEvent();
		//expect(nextEvent.timeStamp == 53 && nextEvent.isNoteOn == true);
		//nextEvent = blockEvents.getNextEvent();
		//expect(nextEvent.timeStamp == 87 && nextEvent.isNoteOn == false);
		//expect(blockEvents.isEmpty());

	}
};

static BlockEventsTest blockEventsTest;