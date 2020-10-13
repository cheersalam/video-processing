# video-processing

## Docker compose
`docker-compose up -d --build`

## Frontend (broken due to CORS, some point it got broken)
Frontend will run with url `http://localhost:3000`
* POST /stream : implemented
* GET /stream : In progress
* GET /stream/:name : implemented
* DELETE /stream/:name : In progress

## Backend
Backend will run with url `http://localhost:3001`
* POST /stream : implemented
* GET /stream : implemented
* GET /stream/:name : implemented
* DELETE /stream/:name : implemented

## Notes
* Didn't get a chance to test a lot, so there is a possibility that I might have missed some corner cases
* Didn't get a chance to review code.
* For better performance file is downloaded to server, on POST /stream. POST /stream will block until file is downloaded completely.
* Uploading png jpeg will have undefined behavior.
* Once rtmp and rtsp stream started, they will run forever.  

## Directory structure
* /client - react app. 
* /cppserver - cpp based backend

## Features
* rtmp server: Implemented based on nginx and ffmpeg
* rtsp server: Implemented based on rtsp-simple-server and ffmpeg
* png and jpeg support: In progress, implementing by converting png jpeg image to mp4 file
* webm support is not implemented

## Credits:
https://github.com/NikolajLeischner/cpprest
https://github.com/aler9/rtsp-simple-server
