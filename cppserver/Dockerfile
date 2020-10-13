  
FROM ubuntu:16.04

ENV PATH $PATH:/usr/local/nginx/sbin

# update and upgrade packages
RUN apt-get update && \
  apt-get upgrade -y && \
  apt-get clean && \
  apt-get install -y --no-install-recommends build-essential \
  wget software-properties-common && \
# ffmpeg
  add-apt-repository ppa:jonathonf/ffmpeg-4 && \
  apt-get update && \
  apt-get install -y --no-install-recommends ffmpeg && \
# nginx dependencies
  apt-get install -y --no-install-recommends libpcre3-dev \
  zlib1g-dev libssl-dev wget && \
  rm -rf /var/lib/apt/lists/*


# get nginx source
WORKDIR /src
RUN wget http://nginx.org/download/nginx-1.7.5.tar.gz && \
  tar zxf nginx-1.7.5.tar.gz && \
  rm nginx-1.7.5.tar.gz && \
# get nginx-rtmp module
  wget https://github.com/arut/nginx-rtmp-module/archive/v1.1.6.tar.gz && \
  tar zxf v1.1.6.tar.gz && \
  rm v1.1.6.tar.gz


# compile nginx
WORKDIR /src/nginx-1.7.5
RUN ./configure --add-module=/src/nginx-rtmp-module-1.1.6 \
  --conf-path=/config/nginx.conf \
  --error-log-path=/logs/error.log \
  --http-log-path=/logs/access.log && \
  make && \
  make install

ADD nginx/nginx.conf /config/nginx.conf


WORKDIR /



RUN apt-get update -y && apt-get install -y g++ make wget libboost-all-dev git
RUN wget https://cmake.org/files/v3.9/cmake-3.9.4.tar.gz && tar xvzf cmake-3.9.4.tar.gz && cd cmake-3.9.4 && ./bootstrap && make && make install && cd .. && rm -rf cmake-3.9.4
RUN apt-get install -y libssl-dev
RUN mkdir -p app/libs
ADD libs/build_dependencies.sh app/libs
RUN cd app/libs && ./build_dependencies.sh
ADD . /app
RUN cd /app && ls -la && cmake . && cmake --build .
EXPOSE 8080
EXPOSE 1935

ADD libs/entry.sh app/
CMD ./app/entry.sh
#CMD ["nginx", "-g", "daemon off;"]
#ENTRYPOINT ["bash", "-c", "./app/crest 8080"]