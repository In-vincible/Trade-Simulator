# ================
# BUILD STAGE
# ================
FROM --platform=linux/amd64 ubuntu:latest as build
LABEL authors="bikram.bharti99@gmail.com"

ARG BOOST_VERSION=1.80.0
ENV DEBIAN_FRONTEND noninteractive

RUN apt update -y && apt upgrade -y
RUN apt install -y cmake g++ gcc gdb git
RUN apt install -y libgtest-dev build-essential software-properties-common pkg-config
RUN apt install -y libtool automake autoconf valgrind libssl-dev wget
RUN apt install -y libpthread-stubs0-dev


# Install Boost
# https://www.boost.org/doc/libs/1_80_0/more/getting_started/unix-variants.html
RUN cd /tmp && \
    BOOST_VERSION_MOD=$(echo $BOOST_VERSION | tr . _) && \
    wget https://boostorg.jfrog.io/artifactory/main/release/${BOOST_VERSION}/source/boost_${BOOST_VERSION_MOD}.tar.bz2 && \
    tar --bzip2 -xf boost_${BOOST_VERSION_MOD}.tar.bz2 && \
    cd boost_${BOOST_VERSION_MOD} && \
    ./bootstrap.sh --prefix=/usr/local --with-libraries=program_options,system,filesystem,thread,test && \
    ./b2 install link=static && \
    rm -rf /tmp/*

WORKDIR /app
COPY . /app/

RUN cmake . && make && make test

# ================
# RUNTIME STAGE
# ================
FROM gcr.io/distroless/static

WORKDIR /app

COPY --from=build --chown=nonroot:nonroot /app/simulator /app/simulator
COPY --from=build --chown=nonroot:nonroot /app/config config
COPY --from=build --chown=nonroot:nonroot /app/input input

USER nonroot:nonroot
CMD ["/app/simulator"]

