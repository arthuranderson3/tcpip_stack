#!/bin/bash

docker build -t main-cli .
docker run -t -i main-cli

