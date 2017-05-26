# PEER TO PEER (P2P) VIDEO STREAMING USING UDP

This is a Peer to Peer application that streams the WebCam video using UDP.
Initially, the system creates a socket where it sends repeatedly , in a separate thread, a specific string message in broadcast mode. On the other side, in another thread, that same socket keeps listening for that same string message coming from another IP address, different from the host where the system is running into.
When that happens, that new IP is added into a kind of list of friends.
That process keeps running until the user desires to stream to one of the peers included into that list.
When both hosts want to comunicate with each other, the stream begins.

# DEMO
To compile the project, you should use c++11, and include OpenCV libraries, such as core, highgui, imgcodecs, videoio and imgproc. Also, include WS2_32 for using sockets in windows.

# EXAMPLE
    >>g++ -std=c++11 -o videostreaming main.cpp Peer.cpp No.cpp -I"<OPENCV_INCLUDE_DIR>" -L"<MINGW_LIB_DIR>" -lWS2_32 -llibopencv_core310 -llibopencv_highgui310 -llibopencv_imgcodecs310 -llibopencv_videoio310 -llibopencv_imgproc310
    
Where OPENCV_INCLUDE_DIR = Location of your opencv. Ex, in my case it was C:/opencv/include

MINGW_LIB_DIR = MinGW libs location

libopencv_core310, libopencv_highgui310.. -> are the opencv libraries. You shoud change it for your specific OpenCV version

Any doubts, feel free to ask.
