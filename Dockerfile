FROM alpine as tcpip_stack-build-env
RUN apk add --no-cache build-base
WORKDIR /app
COPY . .
RUN make

FROM alpine
COPY --from=tcpip_stack-build-env /app/maincli /app/maincli
WORKDIR /app
CMD ./maincli
