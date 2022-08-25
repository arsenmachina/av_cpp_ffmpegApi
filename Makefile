IMAGE_DOCKER_BUILD=ffmpeg_local
BUILD_DIRECTORY=./build
WORKDIR_DOCKER=/home/dev/

docker_code_build: 
	docker run -v `pwd`:${WORKDIR_DOCKER} ${IMAGE_DOCKER_BUILD} sh -c " cmake -B ${BUILD_DIRECTORY} && cd ${BUILD_DIRECTORY} && make "

	