# SmallYmPlayer Linux Port.

The Linux port of the SmallYmPlayer is based on the [PortAudio](http://portaudio.com/) library.
On Ubuntu, the following commands install the required packages:

```
sudo apt-get install libasound-dev portaudio19-dev libportaudio2 libportaudiocpp0
sudo apt-get install ffmpeg
```

To build the player, just run **make** in this directory.

```
$ make
gcc -o SmallYmPlayer SmallYmPlayer.cpp SoundServer.cpp ../StSoundLibrary/YmMusic.cpp ../StSoundLibrary/Ym2149Ex.cpp ../StSoundLibrary/Ymload.cpp ../StSoundLibrary/YmUserInterface.cpp ../StSoundLibrary/digidrum.cpp ../StSoundLibrary/LZH/LzhLib.cpp -lportaudio -lrt -lm -lasound -ljack -pthread -lstdc++
```

Now you can run the player:

```
$ ./SmallYmPlayer ../YmSampleFiles/jess2.ym
SmallYmPlayer.
Using ST-Sound Library, under BSD license
Copyright (C) 1995-1999 Arnaud Carre ( http://leonard.oxg.free.fr )
Linux port by Ruben Lysens / Epsilon537.
Loading music "../YmSampleFiles/jess2.ym"...
Name.....: Sharpness Buzztone
Author...: Jean Sebastien Gerard
Comment..: Converted by Oedipus
Duration.: 6:31
Driver...: YM-Chip driver

Playing music...(press a key to abort)
Time: 0:01
```

Enjoy! :-)

