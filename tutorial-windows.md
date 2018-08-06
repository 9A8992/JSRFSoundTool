# Tutorial for Windows
written by [ChrisDerWahre](https://github.com/ChrisderWahre)

# Step 1. - Downloading
To start modding the sounds you need the following:
 - XBoxADPCM Converter i use [this one](https://github.com/Sergeanur/XboxADPCM/releases) 
 - 9A8992's JSRF Sound Tool (click here)(https://github.com/9A8992/JSRFSoundTool/releases)
 
# Step 2. - Setting up
To set up extract both downloaded files into 1 folder (both command line tools)
copy the file to mod (i use gum) from your `JSRF/Media/Sounds/SE/` folder into the folder `JSRFInput`

# Step 3. - Extracting
To extract the sounds from the .dat file type the following:

To navigate to the folder where the .exe files are in the command promt: `cd C:/Users/**User here**/Desktop/JSRFSoundTool` (or every other directory where you have the tool installed)
and to extract the .dat now: `JSRFSoundTool.exe split pv_gum.dat`

# Step 4. - Converting
To convert the XBox readable waves to pc readable type the following:
`XboxADPCM.exe WavOutput/pv_gum_1.wav WavInput/pv_gum_1.wav` to directly outputting it into the WavInput folder, do this with every wav file OR copy all of the WavInput files in it and convert it to windows readable. with this command:
`XboxADPCM.exe WavInput/pv_gum_1.wav WavInput/pv_gum_1.wav` to overwrite it to windows readable.

# Step 5. - Editing
You are now able to edit the files, but make sure they are the **EXACT** same length !!!
You can use the free tool [AudaCity](https://www.audacityteam.org/) to edit them

# Step 6. - Converting it back
To convert it back to the XBox readable files use the following command:
`XboxADPCM.exe WavInput/pv_gum_1.wav WavInput/pv_gum_1.wav` (it will automatically switch between them, if you want to check if your pc wav player plays it if YES its PC wav if not its XBox Wav)

# Step 7. - Making it a JSRF Sound file
To make the modded sounds a jsrf sounds file use the following command:
`JSRFSoundTool.exe join pv_gum.dat` it will give you the jsrf file in the JSRFOutput folder.


Now you are basically done, if it crashes, its not the same length.

Cheers, Chris.
