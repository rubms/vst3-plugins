//------------------------------------------------------------------------
// Project     : VST SDK
//
// Category    : Examples
// Filename    : plugcontroller.cpp
// Created by  : Steinberg, 01/2018
// Description : RubenVST3 Example for VST 3
//
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2018, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation 
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this 
//     software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#include "../include/plugcontroller.h"
#include "../include/plugids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"

namespace Steinberg {
namespace RubenVST3 {

//-----------------------------------------------------------------------------
tresult PLUGIN_API PlugController::initialize (FUnknown* context)
{
	tresult result = EditController::initialize (context);
	if (result == kResultTrue)
	{
		//---Create Parameters------------
		parameters.addParameter(STR16("Bypass"), 0, 1, 0,
			Vst::ParameterInfo::kCanAutomate | Vst::ParameterInfo::kIsBypass,
			RubenDelayParams::kBypassId);

		parameters.addParameter(STR16("Damping"), 0, 0, .5,
			Vst::ParameterInfo::kCanAutomate, RubenDelayParams::kDamping, 0,
			0);

		parameters.addParameter(STR16("Room Size"), STR16("meters"), 0, .5,
			Vst::ParameterInfo::kCanAutomate, RubenDelayParams::kRoomSizeMeters, 0,
			0);

		parameters.addParameter(STR16("Reverb Time"), STR16("seconds"), 0, .5,
			Vst::ParameterInfo::kCanAutomate, RubenDelayParams::kReverbTimeSeconds, 0,
			0);

		parameters.addParameter(STR16("Early Level"), 0, 0, .5,
			Vst::ParameterInfo::kCanAutomate, RubenDelayParams::kEarlyLevel, 0,
			0);

		parameters.addParameter(STR16("Tail Level"), 0, 0, .5,
			Vst::ParameterInfo::kCanAutomate, RubenDelayParams::kTailLevel, 0,
			0);

		parameters.addParameter(STR16("Spread"), 0, 0, .5,
			Vst::ParameterInfo::kCanAutomate, RubenDelayParams::kSpread, 0,
			0);
	}
	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PlugController::setComponentState (IBStream* state)
{
	// we receive the current state of the component (processor part)
	// we read our parameters and bypass value...
	if (!state)
		return kResultFalse;

	IBStreamer streamer (state, kLittleEndian);

	float savedValue = 0.f;
	if (streamer.readFloat (savedValue) == false)
		return kResultFalse;
	setParamNormalized (RubenDelayParams::kDamping, savedValue);

	savedValue = 0.f;
	if (streamer.readFloat(savedValue) == false)
		return kResultFalse;
	setParamNormalized(RubenDelayParams::kReverbTimeSeconds, savedValue * 10);

	savedValue = 0.f;
	if (streamer.readFloat(savedValue) == false)
		return kResultFalse;
	setParamNormalized(RubenDelayParams::kRoomSizeMeters, savedValue * 10);

	savedValue = 0.f;
	if (streamer.readFloat(savedValue) == false)
		return kResultFalse;
	setParamNormalized(RubenDelayParams::kEarlyLevel, savedValue);

	savedValue = 0.f;
	if (streamer.readFloat(savedValue) == false)
		return kResultFalse;
	setParamNormalized(RubenDelayParams::kTailLevel, savedValue);

	savedValue = 0.f;
	if (streamer.readFloat(savedValue) == false)
		return kResultFalse;
	setParamNormalized(RubenDelayParams::kSpread, savedValue);

	// read the bypass
	int32 bypassState;
	if (streamer.readInt32 (bypassState) == false)
		return kResultFalse;
	setParamNormalized (kBypassId, bypassState ? 1 : 0);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace
} // namespace Steinberg
