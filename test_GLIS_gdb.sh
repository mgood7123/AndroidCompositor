APP="$(adb shell ls /data/app | grep glnative)"
adb push ~/Android/Sdk/ndk/21.1.6352462/prebuilt/android-arm64/gdbserver /data/local/tmp
adb shell chmod +x /data/local/tmp/gdbserver/gdbserver
adb shell LD_LIBRARY_PATH="/data/app/$APP/lib/arm64/" /data/local/tmp/gdbserver/gdbserver :5039 /data/data/glnative.example/files/ASSETS/Arch/arm64-v8a/$1 &
~/Android/Sdk/ndk/21.1.6352462/prebuilt/linux-x86_64/bin/gdb -ex "target remote :5039" -ex continue
