#!/bin/bash

docker build -t cmd-parser-testcli .
docker run -t -i cmd-parser-testcli

