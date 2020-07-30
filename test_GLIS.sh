adb root
if [[ $# == 0 || $1 == "--list" || $1 == "-l" ]]
	then
        echo usage test_GLIS.sh Appliication
        echo applications available are listed below
		adb shell ls -l /data/data/glnative.example/files/ASSETS/Arch/arm64-v8a
		exit 0
fi
APP="$(adb shell ls /data/app | grep glnative)"
adb shell LD_LIBRARY_PATH="/data/app/$APP/lib/arm64/" /data/data/glnative.example/files/ASSETS/Arch/arm64-v8a/$1
