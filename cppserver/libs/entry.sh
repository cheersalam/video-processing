#!/bin/bash


echo "Running nginx"
/usr/local/nginx/sbin/nginx &

echo "Running rtsp server"
/app/rtsp/rtsp-simple-server &

echo "Running app"
/app/crest 3001 -D
