.PHONY: build install build-x86 build-arm64 bin-arm64

install: build
	cd build && \
	make install

build:
	mkdir -p build && \
	cd build && \
	cmake .. && \
	make

# Builds x86 libraries
build-x86:
	docker build \
	-t lib-ch340g-x86 \
	-f ./etc/Dockerfile.x86 ./

# Builds arm64 libraries
build-arm64:
	docker build \
	-t lib-ch340g-arm64 \
	-f ./etc/Dockerfile.arm64 ./

# Copies library files from container to host
bin-arm64:
	rm -rf ./bin || true
	mkdir -p ./bin
	docker run --name lib-ch340g-arm64-bin lib-ch340g-arm64
	docker cp lib-ch340g-arm64-bin:/usr/local/lib/ ./bin
	docker cp lib-ch340g-arm64-bin:/usr/local/include/ch340g.h ./bin
	docker stop lib-ch340g-arm64-bin
	docker rm lib-ch340g-arm64-bin
