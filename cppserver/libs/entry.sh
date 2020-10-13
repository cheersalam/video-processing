#!/bin/bash


echo "Running nginx"
/usr/local/nginx/sbin/nginx &

echo "Running app"
/app/crest 8080 -D 
