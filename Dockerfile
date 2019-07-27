FROM ubuntu:18.04 AS builder
RUN apt-get update && apt-get -y install cmake make g++ python3-pip git && apt-get clean
RUN pip3 install conan && conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
COPY source/etc/conan.ubuntu.profile /root/.conan/profiles/default
COPY .git /src/.git
WORKDIR /src
RUN git checkout .
WORKDIR /src/build
RUN conan install --build=missing /src/
RUN cmake -DCMAKE_BUILD_TYPE=Release ../source
RUN cmake --build . --config Release

FROM ubuntu:18.04 AS front 
COPY --from=builder /src/build/bin/service.front /bin/
EXPOSE 6565/tcp
CMD ["/bin/service.front `cat /etc/hosts | grep $HOSTNAME | cut -f1`"]