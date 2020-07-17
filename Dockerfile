FROM ubuntu:latest AS builder
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get update \
    && apt-get -y install cmake make g++ python3-pip python3-setuptools python3-wheel git \
    && apt-get clean
RUN pip3 install conan 
COPY .git /src/.git
WORKDIR /src
RUN git checkout .
WORKDIR /src/build
RUN conan install --build=missing ../ -s compiler.libcxx=libstdc++11
RUN cmake -DCMAKE_BUILD_TYPE=Release ../source
RUN cmake --build . --config Release

FROM ubuntu:latest AS front 
COPY --from=builder /src/build/bin/service.front /bin/
COPY --from=builder /src/build/service/front/run.sh /bin/service.front.sh
EXPOSE 6565/tcp
CMD ["/bin/service.front.sh"]
