FROM alpine as cmd-parser-build-env
RUN apk add --no-cache build-base
WORKDIR /usr/app
COPY . .
RUN make

FROM alpine
COPY --from=cmd-parser-build-env /usr/app/exe /usr/app/exe
WORKDIR /usr/app
CMD ./exe show 
