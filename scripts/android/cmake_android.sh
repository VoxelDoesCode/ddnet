#!/bin/bash

# $HOME must be used instead of ~ else cargo-ndk cannot find the folder
export ANDROID_HOME=$HOME/Android/Sdk
MAKEFLAGS=-j$(nproc)
export MAKEFLAGS

ANDROID_NDK_VERSION="$(cd "$ANDROID_HOME/ndk" && find . -maxdepth 1 | sort -n | tail -1)"
ANDROID_NDK_VERSION="${ANDROID_NDK_VERSION:2}"
# ANDROID_NDK_VERSION must be exported for build.sh step
export ANDROID_NDK_VERSION
# ANDROID_NDK_HOME must be exported for cargo-ndk
export ANDROID_NDK_HOME="$ANDROID_HOME/ndk/$ANDROID_NDK_VERSION"

_DEFAULT_ANDROID_BUILD=x86
_DEFAULT_GAME_NAME=DDNet
_DEFAULT_PACKAGE_NAME=org.ddnet.client
_DEFAULT_BUILD_TYPE=Debug
_DEFAULT_BUILD_FOLDER=build-android
_ANDROID_API_LEVEL=34

_ANDROID_SUB_BUILD_DIR=build_arch

_SHOW_USAGE_INFO=0

if [ -z ${1+x} ]; then
    printf "\e[31m%s\e[30m\n" "Did not pass android build type, using default: ${_DEFAULT_ANDROID_BUILD}"
	_SHOW_USAGE_INFO=1
else
	_DEFAULT_ANDROID_BUILD=$1
fi

if [ -z ${2+x} ]; then
    printf "\e[31m%s\e[30m\n" "Did not pass game name, using default: ${_DEFAULT_GAME_NAME}"
	_SHOW_USAGE_INFO=1
else
	_DEFAULT_GAME_NAME=$2
fi

if [ -z ${3+x} ]; then
    printf "\e[31m%s\e[30m\n" "Did not pass package name, using default: ${_DEFAULT_PACKAGE_NAME}"
	_SHOW_USAGE_INFO=1
else
	_DEFAULT_PACKAGE_NAME=$3
fi

if [ -z ${4+x} ]; then
    printf "\e[31m%s\e[30m\n" "Did not pass build type, using default: ${_DEFAULT_BUILD_TYPE}"
	_SHOW_USAGE_INFO=1
else
	_DEFAULT_BUILD_TYPE=$4
fi

if [ -z ${5+x} ]; then
    printf "\e[31m%s\e[30m\n" "Did not pass build folder, using default: ${_DEFAULT_BUILD_FOLDER}"
	_SHOW_USAGE_INFO=1
else
	_DEFAULT_BUILD_FOLDER=$5
fi

_ANDROID_JAR_KEY_NAME=~/.android/debug.keystore
_ANDROID_JAR_KEY_PW=android
_ANDROID_JAR_KEY_ALIAS=androiddebugkey

if [ -z ${TW_KEY_NAME+x} ]; then
    printf "\e[31m%s\e[30m\n" "Did not pass a key for the jar signer, using default: ${_ANDROID_JAR_KEY_NAME}"
else
	_ANDROID_JAR_KEY_NAME=$TW_KEY_NAME
fi
if [ -z ${TW_KEY_PW+x} ]; then
    printf "\e[31m%s\e[30m\n" "Did not pass a key pw for the jar signer, using default: ${_ANDROID_JAR_KEY_PW}"
else
	_ANDROID_JAR_KEY_PW=$TW_KEY_PW
fi
if [ -z ${TW_KEY_ALIAS+x} ]; then
    printf "\e[31m%s\e[30m\n" "Did not pass a key alias for the jar signer, using default: ${_ANDROID_JAR_KEY_ALIAS}"
else
	_ANDROID_JAR_KEY_ALIAS=$TW_KEY_ALIAS
fi

export TW_KEY_NAME="${_ANDROID_JAR_KEY_NAME}"
export TW_KEY_PW=$_ANDROID_JAR_KEY_PW
export TW_KEY_ALIAS=$_ANDROID_JAR_KEY_ALIAS

_ANDROID_VERSION_CODE=1
if [ -z ${TW_VERSION_CODE+x} ]; then
    printf "\e[31m%s\e[30m\n" "Did not pass a version code, using default: ${_ANDROID_VERSION_CODE}"
else
	_ANDROID_VERSION_CODE=$TW_VERSION_CODE
fi

export TW_VERSION_CODE=$_ANDROID_VERSION_CODE

_ANDROID_VERSION_NAME="1.0"
if [ -z ${TW_VERSION_NAME+x} ]; then
    printf "\e[31m%s\e[30m\n" "Did not pass a version name, using default: ${_ANDROID_VERSION_NAME}"
else
	_ANDROID_VERSION_NAME=$TW_VERSION_NAME
fi

export TW_VERSION_NAME=$_ANDROID_VERSION_NAME

printf "\e[31m%s\e[1m\n" "Building with setting, for arch: ${_DEFAULT_ANDROID_BUILD}, with build type: ${_DEFAULT_BUILD_TYPE}, with name: ${_DEFAULT_GAME_NAME} (${_DEFAULT_PACKAGE_NAME})"

if [ $_SHOW_USAGE_INFO == 1 ]; then	
    printf "\e[31m%s\e[1m\n" "Usage: ./cmake_android.sh <x86/x86_64/arm/arm64/all> <Game name> <Package name> <Debug/Release> <Build folder>"
fi

printf "\e[33mBuilding cmake\e[0m\n"

function build_for_type() {
	cmake \
		-H. \
		-G "Ninja" \
		-DPREFER_BUNDLED_LIBS=ON \
		-DCMAKE_BUILD_TYPE="${_DEFAULT_BUILD_TYPE}" \
		-DANDROID_PLATFORM="android-${_ANDROID_API_LEVEL}" \
		-DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
		-DANDROID_NDK="$ANDROID_NDK_HOME" \
		-DANDROID_ABI="${2}" \
		-DANDROID_ARM_NEON=TRUE \
		-DCMAKE_ANDROID_NDK="$ANDROID_NDK_HOME" \
		-DCMAKE_SYSTEM_NAME=Android \
		-DCMAKE_SYSTEM_VERSION="$_ANDROID_API_LEVEL" \
		-DCMAKE_ANDROID_ARCH_ABI="${2}" \
		-DCARGO_NDK_TARGET="${3}" \
		-DCARGO_NDK_API="$_ANDROID_API_LEVEL" \
		-DDDNET_TEST_NO_LINK=ON \
		-B"${_DEFAULT_BUILD_FOLDER}/$_ANDROID_SUB_BUILD_DIR/$1" \
		-DSERVER=OFF \
		-DTOOLS=OFF \
		-DDEV=TRUE \
		-DCMAKE_CROSSCOMPILING=ON \
		-DVULKAN=ON \
		-DVIDEORECORDER=OFF
	(
		cd "${_DEFAULT_BUILD_FOLDER}/$_ANDROID_SUB_BUILD_DIR/$1" || exit 1
		cmake --build . --target game-client
	)
}

mkdir "${_DEFAULT_BUILD_FOLDER}"

if [[ "${_DEFAULT_ANDROID_BUILD}" == "arm" || "${_DEFAULT_ANDROID_BUILD}" == "all" ]]; then
	build_for_type arm armeabi-v7a armv7-linux-androideabi &
fi

if [[ "${_DEFAULT_ANDROID_BUILD}" == "arm64" || "${_DEFAULT_ANDROID_BUILD}" == "all" ]]; then
	build_for_type arm64 arm64-v8a aarch64-linux-android &
fi

if [[ "${_DEFAULT_ANDROID_BUILD}" == "x86" || "${_DEFAULT_ANDROID_BUILD}" == "all" ]]; then
	build_for_type x86 x86 i686-linux-android &
fi

if [[ "${_DEFAULT_ANDROID_BUILD}" == "x86_64" || "${_DEFAULT_ANDROID_BUILD}" == "x64" || "${_DEFAULT_ANDROID_BUILD}" == "all" ]]; then
	build_for_type x86_64 x86_64 x86_64-linux-android &
fi

wait

printf "\e[36mPreparing gradle build\n"

cd "${_DEFAULT_BUILD_FOLDER}" || exit 1

mkdir -p src/main
mkdir -p src/main/res/mipmap

function copy_dummy_files() {
	rm ./"$2"
	cp ../"$1" "$2"
}

function copy_dummy_files_rec() {
	rm -R ./"$2"/"$1"
	cp -R ../"$1" "$2"
}

copy_dummy_files scripts/android/files/build.sh build.sh
copy_dummy_files scripts/android/files/gradle-wrapper.jar gradle-wrapper.jar
copy_dummy_files scripts/android/files/build.gradle build.gradle
copy_dummy_files scripts/android/files/gradle-wrapper.properties gradle-wrapper.properties
copy_dummy_files scripts/android/files/gradle.properties gradle.properties
copy_dummy_files scripts/android/files/proguard-rules.pro proguard-rules.pro
copy_dummy_files scripts/android/files/settings.gradle settings.gradle
copy_dummy_files scripts/android/files/AndroidManifest.xml src/main/AndroidManifest.xml
copy_dummy_files_rec scripts/android/files/res src/main
copy_dummy_files other/icons/DDNet_256x256x32.png src/main/res/mipmap/ic_launcher.png
copy_dummy_files other/icons/DDNet_256x256x32.png src/main/res/mipmap/ic_launcher_round.png

function copy_libs() {
	mkdir -p "lib/$2"
	cp "$_ANDROID_SUB_BUILD_DIR/$1/libDDNet.so" "lib/$2"
	cp "$_ANDROID_SUB_BUILD_DIR/$1/libs/libSDL2.so" "lib/$2"
	cp "$_ANDROID_SUB_BUILD_DIR/$1/libs/libhidapi.so" "lib/$2"
}

if [[ "${_DEFAULT_ANDROID_BUILD}" == "arm" || "${_DEFAULT_ANDROID_BUILD}" == "all" ]]; then
	copy_libs arm armeabi-v7a
fi

if [[ "${_DEFAULT_ANDROID_BUILD}" == "arm64" || "${_DEFAULT_ANDROID_BUILD}" == "all" ]]; then
	copy_libs arm64 arm64-v8a
fi

if [[ "${_DEFAULT_ANDROID_BUILD}" == "x86" || "${_DEFAULT_ANDROID_BUILD}" == "all" ]]; then
	copy_libs x86 x86
fi

if [[ "${_DEFAULT_ANDROID_BUILD}" == "x86_64" || "${_DEFAULT_ANDROID_BUILD}" == "x64" || "${_DEFAULT_ANDROID_BUILD}" == "all" ]]; then
	copy_libs x86_64 x86_64
fi

_DEFAULT_ANDROID_BUILD_DUMMY=$_DEFAULT_ANDROID_BUILD
if [[ "${_DEFAULT_ANDROID_BUILD}" == "all" ]]; then
	_DEFAULT_ANDROID_BUILD_DUMMY=arm
fi

mkdir -p assets/asset_integrity_files
cp -R "$_ANDROID_SUB_BUILD_DIR/$_DEFAULT_ANDROID_BUILD_DUMMY/data" ./assets/asset_integrity_files

curl --remote-name --time-cond cacert.pem https://curl.se/ca/cacert.pem
cp ./cacert.pem ./assets/asset_integrity_files/data/cacert.pem

# create integrity file for extracting assets
(
	cd assets/asset_integrity_files || exit 1

	tmpfile="$(mktemp /tmp/hash_strings.XXX)"

	find data -iname "*" -type f -print0 | while IFS= read -r -d $'\0' file; do
		sha_hash=$(sha256sum "$file" | cut -d' ' -f 1)
		echo "$file $sha_hash" >> "$tmpfile"
	done

	full_hash="$(sha256sum "$tmpfile" | cut -d' ' -f 1)"

	rm "integrity.txt"
	{
		echo "$full_hash"
		cat "$tmpfile"
	} > "integrity.txt"
)

printf "\e[0m"

echo "Building..."

rm -R src/main/java/org
mkdir -p src/main/java
cp -R ../scripts/android/files/java/org src/main/java/
cp -R ../ddnet-libs/sdl/java/org src/main/java/

# shellcheck disable=SC1091
source ./build.sh "$_DEFAULT_GAME_NAME" "$_DEFAULT_PACKAGE_NAME" "$_DEFAULT_BUILD_TYPE"

cd ..
