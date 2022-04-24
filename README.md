# Screen Event Capturer
This project records the computer screen and waits for an event to occur, once the event occurs the program will then save a video file with footage of the event occuring.

To prevent an indefinately long video, the user selects a duration for the video. Two streams are repeatedly ran in parallel for the durtion of the video.

The two streams are 50% overlapping where one stream's first half is recording along with the other streams second half and vice versa.

When the event occurs the program checks which stream is in the center half and saves that file while discarding all other files.

## Build Instructions
Install Gstreamer using the script provided

```sudo ./install_gstreamer.sh```

Install cmake and git

```sudo apt install cmake git```

clone repo

```git clone https://github.com/Abdob/Screen-Event-Capturer```

change directories into repo, create a build directory and build using cmake

```
cd Screen-Event-Capturer
mkdir build
cd build
cmake ..
make
```

## Run Instructions
Run the program

``` ./screen_recording_app```

Enter a duration in seconds as prompted and allow the recording to happen.

When ready to stop, open a separate terminal induce an event by creating an event file on the same directory where the program is ran

```
cd Screen-Event-Capturer/build
touch event
```


