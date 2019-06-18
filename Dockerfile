FROM alpine:latest AS builder
RUN apk --no-cache add musl-dev cmake make g++ linux-headers python py-pip git
RUN pip install conan && conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
RUN rm -f /src && mkdir -p /src/build
WORKDIR /src
COPY .git ./.git
RUN git checkout .
WORKDIR /src/build
COPY source/etc/conan.alpine.profile .
RUN conan install --profile=./conan.alpine.profile --build=outdated ..
RUN cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS='-static' ../source
RUN cmake --build . --config Release

#FROM alpine:latest
#COPY --from=builder /src/build/bin/micro.service /bin/
#EXPOSE 6565
#CMD ["/bin/micro.service"]