/*********************************************************************************

	SoundServer - Linux Version - Written by Ruben
	Derived from Windows Version by Arnaud Carr� (aka Leonard / OXYGENE)

*********************************************************************************/

#ifndef __SOUNDSERVER__
#define __SOUNDSERVER__

#include <cstddef>

#define FALSE false
#define TRUE  true

#define REPLAY_RATE 44100

typedef void (*USER_CALLBACK)(void *pBuffer, long bufferLen);
typedef bool BOOL;

class CSoundServer
{

public:
	CSoundServer();
	~CSoundServer();

	BOOL open(USER_CALLBACK pUserCallback,
			  long totalBufferedSoundLen = 4000); // Buffered sound, in ms

	void close(void);

	BOOL IsRunning() { return m_pUserCallback != NULL; }

	/*Entry point into CSoundServer object from freestanding PortAudio callback function.*/
	void invokeUserCallback(void *pBuffer, long bufferLen) {
		if (m_pUserCallback)
			m_pUserCallback(pBuffer, bufferLen);
	}

private:
	volatile USER_CALLBACK m_pUserCallback;
};

#endif
