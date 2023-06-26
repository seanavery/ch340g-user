.PHONY: build
build:
	mkdir -p build && \
	cd build && \
	cmake .. && \
	make
docker:
	docker build \
	-t ch340g-user \
	-f ./etc/Dockerfile ./
