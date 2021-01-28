	#!/bin/bash
	for i in *.mp3; do
            j="${i%.mp3}"
            soundconverter -b -m audio/mpeg -s .ogg "$j.mp3" && rm -f "$j.mp3"  && echo "$i réencodé en ogg."
	done
