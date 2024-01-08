FROM alpine:latest

RUN apk add --update gcc g++ clang gdb cmake make ninja autoconf automake dos2unix tar rsync python3 && rm -rf /tmp/* /var/cache/apk/*