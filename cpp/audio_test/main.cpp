#include <iostream>
#include <audiofile.h>

int main()
{
	audiofile<double> audio;
	audio.load("/home/Documents/balentian/sentence_audio/baalehm_va_ya.wav");
	audio.play();
}
