.PHONY: build
build:
	mkdir -p build && \
	cd build && \
	cmake .. && \
	make
x86:
	docker build \
	-t lib-ch340g-x86 \
	-f ./etc/Dockerfile.x86 ./
