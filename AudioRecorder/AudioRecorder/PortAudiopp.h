#pragma once

#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <numeric>

#include "portaudio.h"

#pragma comment(lib, "portaudio")

#define DEBUG

#define SAMPLE_RATE		96000
#define FRAMES_PER_BUFFER	512
#define TOTAL_SECONDS		3
#define NUM_CHANNELS		2
#define DITHER_FLAG		0
#define PA_SAMPLE_TYPE		paFloat32
#define SAMPLE_SILENCE		0.0f

using SAMPLE = float;

struct paData
{
	int          frameIndex;
	int          maxFrameIndex;
	SAMPLE      *recordedSamples;
};

static int record_callback(
	const void	*inputBuffer,
	void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData)
{
	paData *data = static_cast<paData*>(userData);
	const SAMPLE *rptr = static_cast<const SAMPLE*>(inputBuffer);
	SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	long framesToCalc;
	long i;
	int finished;
	unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

	if (framesLeft < framesPerBuffer)
	{
		framesToCalc = framesLeft;
		finished = paComplete;
	}
	else
	{
		framesToCalc = framesPerBuffer;
		finished = paContinue;
	}

	if (inputBuffer == NULL)
	{
		for (i = 0; i < framesToCalc; i++)
		{
			*wptr++ = SAMPLE_SILENCE;  /* left */
			if (NUM_CHANNELS == 2) *wptr++ = SAMPLE_SILENCE;  /* right */
		}
	}
	else
	{
		for (i = 0; i < framesToCalc; i++)
		{
			*wptr++ = *rptr++;  /* left */
			if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
		}
	}
	data->frameIndex += framesToCalc;
	return finished;
}

static int playCallback(
	const void *inputBuffer,
	void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData)
{
	paData *data = static_cast<paData*>(userData);
	SAMPLE *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	SAMPLE *wptr = static_cast<SAMPLE*>(outputBuffer);
	size_t i;
	int finished;
	unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

	if (framesLeft < framesPerBuffer)
	{
		/* final buffer... */
		for (i = 0; i < framesLeft; i++)
		{
			*wptr++ = *rptr++;  /* left */
			if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
		}
		for (; i < framesPerBuffer; i++)
		{
			*wptr++ = 0;  /* left */
			if (NUM_CHANNELS == 2) *wptr++ = 0;  /* right */
		}
		data->frameIndex += framesLeft;
		finished = paComplete;
	}
	else
	{
		for (i = 0; i < framesPerBuffer; i++)
		{
			*wptr++ = *rptr++;  /* left */
			if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
		}
		data->frameIndex += framesPerBuffer;
		finished = paContinue;
	}
	return finished;
}

#include <vector>
#include <iostream>

class PortAudio
{
private:
	PaStreamParameters  inputParams, outputParams;
	PaStream*           stream;
	PaError             errorStatus{ paNoError };
	paData				data;
	int                 totalTicks;
	int                 numSamples;
	int                 numBytes;

public:
	PortAudio()
	{
#ifdef DEBUG
		printf("%s\n", __FUNCTION__);
#endif
	}

	~PortAudio() noexcept
	{
#ifdef DEBUG
		printf("%s\n", __FUNCTION__);
#endif
		if (data.recordedSamples != nullptr)
			free(data.recordedSamples);
		Pa_Terminate();
	}

	void Init(int totalSeconds)
	{
#ifdef DEBUG
		printf("%s\n", __FUNCTION__);
#endif		
		totalTicks = totalSeconds * SAMPLE_RATE;
		numSamples = totalTicks * NUM_CHANNELS;
		numBytes = numSamples * sizeof(SAMPLE);

		data.maxFrameIndex = totalTicks;
		data.frameIndex = 0;
		data.recordedSamples = (SAMPLE *)malloc(numBytes);

		if (data.recordedSamples == nullptr)
		{
			printf("%s: Could not allocate memory for recording\n", __FUNCTION__);
			return;
		}

		for (int i = 0; i < numSamples; i++)
			data.recordedSamples[i] = 0;

		errorStatus = Pa_Initialize();
		if (errorStatus != paNoError)
			return;

		inputParams.device = Pa_GetDefaultInputDevice();
		if (inputParams.device == paNoDevice) {
			printf("%s: Could not find a default input device\n", __FUNCTION__);
			return;
		}

		inputParams.channelCount = 2;
		inputParams.sampleFormat = PA_SAMPLE_TYPE;
		inputParams.suggestedLatency = Pa_GetDeviceInfo(inputParams.device)->defaultLowInputLatency;
		inputParams.hostApiSpecificStreamInfo = NULL;
	}

	void Record(int totalSeconds)
	{
#ifdef DEBUG
		printf("%s\n", __FUNCTION__);
#endif
		Init(totalSeconds);

		errorStatus = Pa_OpenStream(
			&stream,
			&inputParams,
			NULL,
			SAMPLE_RATE,
			FRAMES_PER_BUFFER,
			paClipOff,
			record_callback,
			&data);

		if (errorStatus != paNoError) return;

		errorStatus = Pa_StartStream(stream);
		if (errorStatus != PaErrorCode::paNoError) return;
#ifdef DEBUG
		printf("%s: Recording started...\n", __FUNCTION__);
#endif
		while ((errorStatus = Pa_IsStreamActive(stream)) == 1)
		{
			Pa_Sleep(1000);
		}
		if (errorStatus < 0) return;

		errorStatus = Pa_CloseStream(stream);
		if (errorStatus != PaErrorCode::paNoError) return;
#ifdef DEBUG
		printf("%s: Recorded %d frames in %ds\n", __FUNCTION__, totalTicks, totalSeconds);
		
		float min = *std::min_element(data.recordedSamples, data.recordedSamples + data.frameIndex);
		float max = *std::max_element(data.recordedSamples, data.recordedSamples + data.frameIndex);
		float average = std::accumulate(data.recordedSamples, data.recordedSamples + data.frameIndex, 0.f) / data.frameIndex;

		printf("min: %f\tmax: %f\tavg: %f\n", min, max, average);
#endif
	}

	void SaveTo(const char *file)
	{
#ifdef DEBUG
		printf("%s\n", __FUNCTION__);
#endif
		if (file != nullptr && data.frameIndex > 0)
		{
			FILE  *fid;
			fid = fopen(file, "wb");
			if (fid == NULL)
			{
				printf("%s: Could not open file.", __FUNCTION__);
			}
			else
			{
				fwrite(data.recordedSamples, NUM_CHANNELS * sizeof(SAMPLE), totalTicks, fid);
				fclose(fid);
				printf("%s: Wrote data to 'recorded.raw'\n", __FUNCTION__);
			}
		}
	}

	void Playback(paData *data)
	{
#ifdef DEBUG
		printf("%s\n", __FUNCTION__);
#endif
		if (data == nullptr)
			return;

		data->frameIndex = 0;

		outputParams.device = Pa_GetDefaultOutputDevice();
		if (outputParams.device == paNoDevice)
		{
			printf("%s: Couldn't get default playback device\n", __FUNCTION__);
			return;
		}

		outputParams.channelCount = 2;
		outputParams.sampleFormat = PA_SAMPLE_TYPE;
		outputParams.suggestedLatency = Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;
		outputParams.hostApiSpecificStreamInfo = NULL;

		errorStatus = Pa_OpenStream(
			&stream,
			NULL,
			&outputParams,
			SAMPLE_RATE,
			FRAMES_PER_BUFFER,
			paClipOff,
			playCallback,
			data);

		if (errorStatus != paNoError)
		{
			printf("%s: Error opening stream for playback\n", __FUNCTION__);
			return;
		}
		if (stream)
		{
			errorStatus = Pa_StartStream(stream);
			if (errorStatus != paNoError) return;

			while ((errorStatus = Pa_IsStreamActive(stream)) == 1)
			{
				Pa_Sleep(100);
			}
			errorStatus = Pa_CloseStream(stream);
		}
	}

	void Playback()
	{
		Playback(&data);
	}

	operator bool()
	{
		return errorStatus == PaErrorCode::paNoError;
	}
};
