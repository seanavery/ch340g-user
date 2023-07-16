.PHONY: build
build:
	mkdir -p build && \
	cd build && \
	cmake .. && \
	make

build-x86:
	docker build \
	-t lib-ch340g-x86 \
	-f ./etc/Dockerfile.x86 ./

build-arm64:
	docker build \
	-t lib-ch340g-arm64 \
	-f ./etc/Dockerfile.arm64 ./
