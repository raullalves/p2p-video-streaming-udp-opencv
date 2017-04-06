# Pure P2P video streaming application using OpenCV, UDP sockets and threads in windows

The purpose of this project was developing a pure P2P application, as part of an academic module in my college, in Brazil
Initially, the system creates a socket where it sends repeatedly , in a separate thread, a specific string message in broadcast mode. On the other hand, in another thread, that same socket keeps listening for that same string message coming from another IP address, different from the host where the system is running into.
When that happens, that new IP is added into a kind of list of friends.
That process keeps running until the user desires to stream to one of the peers included into that list.
When both hosts want to comunicate with each other, the stream begins.

# Demo
To compile the project, you should use c++11, and include OpenCV libraries, such as core, highgui, imgcodecs, videoio and imgproc. Also, include WS2_32 for using sockets in windows.

Any doubts, feel free to ask.
