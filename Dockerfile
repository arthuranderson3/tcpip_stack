FROM alpine as tcpip_stack-build-env
RUN apk add --no-cache build-base
WORKDIR /app
COPY . .
RUN make

FROM alpine
COPY --from=tcpip_stack-build-env /app/topo_test /app/topo_test
WORKDIR /app
CMD ./topo_test
