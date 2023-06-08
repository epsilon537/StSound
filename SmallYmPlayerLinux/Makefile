
SmallYmPlayer : SmallYmPlayer.cpp SoundServer.cpp ../StSoundLibrary/YmMusic.cpp ../StSoundLibrary/Ym2149Ex.cpp ../StSoundLibrary/Ymload.cpp ../StSoundLibrary/YmUserInterface.cpp ../StSoundLibrary/digidrum.cpp ../StSoundLibrary/LZH/LzhLib.cpp
	gcc -o $@ $^ -lportaudio -lrt -lm -lasound -ljack -pthread -lstdc++

clean :
	rm -f SmallYmPlayer