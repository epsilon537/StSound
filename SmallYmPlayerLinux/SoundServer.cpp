/*********************************************************************************

	SoundServer - Linux version - Written by Ruben Lysens.
	Derived from SoundServer - Windows version - Written by Arnaud Carr� (aka Leonard / OXYGENE)

*********************************************************************************/

#include "SoundServer.h"
#include "portaudio.h"
#include <cstdio>
#include <cassert>

#define NULL_DEVICE "/dev/null"
#define TTY_DEVICE "/dev/tty"

static CSoundServer *data;
static PaStream *stream;
static PaError err;

static void paError(void)
{
	//Restore stderr. We may be in a stderr silenced stated when this function is called.
	freopen(TTY_DEVICE, "w", stderr);

	Pa_Terminate();
	fprintf(stderr, "An error occured while using the portaudio stream\n");
	fprintf(stderr, "Error number: %d\n", err);
	fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
}

// Internal PortAudio callback function.
static int paCallback(const void *inputBuffer, void *outputBuffer,
					  unsigned long framesPerBuffer,
					  const PaStreamCallbackTimeInfo *timeInfo,
					  PaStreamCallbackFlags statusFlags,
					  void *userData)
{
	/* Cast data passed through stream to our structure. */
	CSoundServer *data = (CSoundServer *)userData;
	short *out = (short *)outputBuffer;
	(void)inputBuffer; /* Prevent unused variable warning. */

	assert(data);

	data->invokeUserCallback(outputBuffer, framesPerBuffer);

	return 0;
}

CSoundServer::CSoundServer()
{
	m_pUserCallback = NULL;
}

CSoundServer::~CSoundServer()
{
	close();
}

BOOL CSoundServer::open(USER_CALLBACK pUserCallback, long totalBufferedSoundLen)
{
	m_pUserCallback = pUserCallback;

	(void)totalBufferedSoundLen; // not used.

	//Silence stderr, because Pa_Initialze is very noisy.
    freopen(NULL_DEVICE, "w", stderr);
    fprintf(stderr, "you CAN'T see this stderr\n");

	/* Initialize library before making any other calls. */
	err = Pa_Initialize();
	if (err != paNoError)
	{
		paError();
		return FALSE;
	}

	//Restore stderr.
	freopen(TTY_DEVICE, "w", stderr);

	/* Open an audio I/O stream. */
	err = Pa_OpenDefaultStream(&stream,
							   0,		/* no input channels */
							   1,		/* mono output */
							   paInt16, /* 16-bit pcm output */
							   REPLAY_RATE,
							   paFramesPerBufferUnspecified, /* frames per buffer */
							   paCallback,
							   this); /* Pass pointer to self as context pointer.*/
	if (err != paNoError)
	{
		paError();
		return FALSE;
	}

	err = Pa_StartStream(stream);
	if (err != paNoError)
	{
		paError();
		return FALSE;
	}

	return TRUE;
}

void CSoundServer::close(void)
{
	if (IsRunning())
	{
		m_pUserCallback = NULL;

		err = Pa_StopStream(stream);
		if (err != paNoError)
		{
			paError();
			return;
		}

		err = Pa_CloseStream(stream);
		if (err != paNoError)
		{
			paError();
			return;
		}

		Pa_Terminate();
	}
}
