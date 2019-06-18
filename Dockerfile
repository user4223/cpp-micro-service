FROM alpine:latest AS builder
RUN apk --no-cache add musl-dev cmake make g++ linux-headers python py-pip git
RUN pip install conan && conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
RUN mkdir -p /src/build
COPY conanfile.txt /src/
COPY source/etc/conan.alpine.profile /src/
WORKDIR /src/build
RUN conan install --profile=/src/conan.alpine.profile --build=outdated /src/
COPY .git /src/.git
WORKDIR /src
RUN git checkout .
WORKDIR /src/build
#RUN cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS='-static' ../source
RUN cmake -DCMAKE_BUILD_TYPE=Release ../source
RUN cmake --build . --config Release

#FROM alpine:latest
#COPY --from=builder /src/build/bin/micro.service /bin/
#EXPOSE 6565
#CMD ["/bin/micro.service"]