.PHONY: build

build:
	docker build -t main-cli .

run:
	docker run -t -i main-cli
