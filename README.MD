# Jet Set Radio Future Sound Effect Tool

JSRFSoundTool is a console application for splitting and creating Jet set Radio Future sound effect Files. A JSRF sound effect file is essentially a wav container containing various sound effects in [Xbox ADPCM format](http://xboxdevwiki.net/Xbox_ADPCM), that can be replaced by wav files of the same length/size in Xbox ADPCM format and then played in the game.

## Required Materials

* A reliable way to convert standard 16-bit PCM wav files into Xbox ADPCM wav files. I've used [Sergeanur's XboxADPCM tool](https://github.com/Sergeanur/XboxADPCM) with success. (For linux users, that program works with wine).
* JSRF sound files to work with. (They are found in /Media/Sounds/SE/)
* A moded xbox with JSRF installed, in order to use the created sound effect files.

## Usage
Before beginnign, it is important to note this:

# The Wav files you create MUST be the same length as the ones you are replacing. If they are not, the game will crash when attempting to load the generated sound effect file

The program is used:

## JSRFSoundTool(.exe) [join/split] (sound effect file)
Example: JSRFSoundTool pv_gum.dat

The sound effect file must be placed in the folder "JSRFInput" for either of the commands.

The split command splits a JSRF sound file into individual wav files and writes them to the folder "WavOutput" (Which must already exist for the program to work), with the naming scheme pv_gum_1.wav, etc. The wav files will be in Xbox ADPCm format.

The Join command will make a JSRF sound effect file from individual wav files in the "WavInput" folder of the same number and naming scheme as the split command would give. The wav files must be in Xbox ADPCM format. (It is good practice run split on the file you want to edit, replace the wavs, and then move them to the WavInput folder and run join). Note that the original sound effect file is required for this process (or generated SE file derrived from the original of its type, but it is good practce to always use originals for the JSRFInput. The file will be written into the folder "JSRFOutput"

Note that all four folders "JSRFInput", "JSRFOutput", "WavInput", "WavOutput" must already exist in the same folder as the program, as the program cannot make its own folders.

Also note again that each individual wav file must be the same length as it's conjugate you are trying to replace. After converting the new wav file to Xbox ADPCM format, any wav file of the same length will always be the same file size.

## Licence

JSRFSoundTool is licensed under GPL3.
