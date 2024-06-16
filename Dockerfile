FROM alpine:latest as temp-build

RUN apk add build-base libusb-dev openssl-dev librtlsdr-dev cmake

WORKDIR /build
RUN mkdir -p /build/out

ADD . ./rtl_433
WORKDIR ./rtl_433
RUN cmake -DCMAKE_INSTALL_PREFIX:PATH=/build/out -B docker-build
RUN cmake --build docker-build --target install


FROM alpine:latest

RUN apk add libusb librtlsdr tzdata openssl
COPY --from=temp-build /build/out/ /

ENTRYPOINT ["rtl_433"]
