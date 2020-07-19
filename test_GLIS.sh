adb shell LD_LIBRARY_PATH="/data/app/$(adb shell ls /data/app | grep glnative)/lib/arm64/" /data/data/glnative.example/files/ASSETS/Arch/arm64-v8a/$1
