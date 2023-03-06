FROM ubuntu:20.04

COPY . /home/szymon/Programming/terminalFlappyBird/src/src

WORKDIR /home/szymon/Programming/terminalFlappyBird/src/

RUN apt-get update 

RUN apt-get install -y -q libncurses5-dev gcc

RUN gcc -o output ./src/flappyBird.c -lcurses -lpthread

CMD [ "./output" ]
