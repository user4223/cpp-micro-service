FROM alpine
COPY build/bin/micro.service /
CMD ["/micro.service"]