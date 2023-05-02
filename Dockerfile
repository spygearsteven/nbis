FROM gcc:7.5

WORKDIR /app

COPY . /app

RUN apt-get update && apt-get install -y gcc make cmake libx11-dev

# RUN apk add gcc build-base make cmake libx11-dev
# ^ For alpine base image

RUN mkdir /build

RUN ./setup.sh /build --64

RUN make config

RUN make it

RUN make install
