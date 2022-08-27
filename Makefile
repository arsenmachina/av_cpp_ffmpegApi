IMAGE_DOCKER_BUILD=ffmpeg_local
NAME_EXE_FILE=ff_ms
LOCAL_BUILD_DIR_RUN=${PWD}/build/run/
BUILD_DIRECTORY=/home/dev/build/dev
RUN_DIRECTORY=/home/dev/build/run/
WORKDIR_DOCKER=/home/dev/
IF_VIDEO?=test.mp4
USER=1000


install: 
	docker build . -t ffmpeg_local


build_code: 
	
	docker run -v `pwd`:${WORKDIR_DOCKER} --user ${USER}:${USER} ${IMAGE_DOCKER_BUILD} \
	sh -c " mkdir -p ${BUILD_DIRECTORY} ${RUN_DIRECTORY} && \
		cmake -B ${BUILD_DIRECTORY} && cd ${BUILD_DIRECTORY} && make \
		&& cp ${BUILD_DIRECTORY}/${NAME_EXE_FILE} ${RUN_DIRECTORY} \
	"
	
run_code:
	docker run -v ${LOCAL_BUILD_DIR_RUN}:${RUN_DIRECTORY} ${IMAGE_DOCKER_BUILD} sh -c "cd ${RUN_DIRECTORY} && \
	./${NAME_EXE_FILE} ${IF_VIDEO} "
