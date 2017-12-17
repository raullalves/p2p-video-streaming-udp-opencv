# PEER TO PEER (P2P) VIDEO STREAMING USING UDP
(for Linux)

This is a Peer to Peer application that streams the WebCam video using UDP.
Initially, the system creates a socket where it sends repeatedly , in a separate thread, a specific string message in broadcast mode. On the other side, in another thread, that same socket keeps listening for that same string message coming from another IP address, different from the host where the system is running into.
When that happens, that new IP is added into a kind of list of friends.
That process keeps running until the user desires to stream to one of the peers included into that list.
When both hosts want to comunicate with each other, the stream begins.

# Build
    * Install OpenCV (used for decoding and showing... TODO: Replace OpenCV by FFMpeg and SDL)
    *   ```
        make
        ```

# Run
    ./p2pstreaming