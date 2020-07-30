echo ./gradlew clean $@
./gradlew clean $@
if [[ $? == 0 ]]
	then
		echo ./gradlew assembleDebug $@
		./gradlew assembleDebug $@
		if [[ $? == 0 ]]
			then
				echo ./gradlew uninstallDebug $@
				./gradlew uninstallDebug $@
				if [[ $? == 0 ]]
					then
						echo ./gradlew installDebug $@
						./gradlew installDebug $@
				fi
		fi
fi
