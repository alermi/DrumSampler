/*
  ==============================================================================

    Constants.cpp
    Created: 2 Aug 2020 10:12:02pm
    Author:  Ani

  ==============================================================================
*/

#include "Constants.h"

std::map<String, std::map<String, bool>> Constants::getAllInstrumentsBleedFlags() {


	return {
		{"Kick",
			{
				{"kickin", false},
				{ "kickout", false},
				{ "kicksub", false},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{"Snare",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", false},
				{ "snrbot", false},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{"HiHat",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", false},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{"Ride",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", false},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{"Tom1",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", false},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{ "Tom2",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", false},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{ "Tom3",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", false},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{ "Tom4",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", false},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{ "Tom5",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", false},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{ "Crash1",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{ "Crash2",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{ "China",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{ "Stack1",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{ "Stack2",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		},
		{ "Splash",
			{
				{"kickin", true},
				{ "kickout", true},
				{ "kicksub", true},
				{ "snrtop", true},
				{ "snrbot", true},
				{ "tom1", true},
				{ "tom2", true},
				{ "tom3", true},
				{ "tom4", true},
				{ "tom5", true},
				{ "hh", true},
				{ "ride", true},
				{ "roommono", false},
				{ "roomstereo", false},
				{ "roomfar", false},
				{ "oh", false}
			}
		}
	};
};