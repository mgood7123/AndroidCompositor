APP="$(adb shell ls /data/app | grep glnative)"
adb shell LD_LIBRARY_PATH="/data/app/$APP/lib/arm64/" /data/data/glnative.example/files/ASSETS/Arch/arm64-v8a/$1