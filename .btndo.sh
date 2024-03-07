if [ $1 = "vol" ]; then
    echo Ändere Lautstärke
    if [ $2 = "up" ]; then
        echo Lauter
    elif [ $2 = "down" ]; then
        echo leiser
    elif [ $2 = "mute" ]; then
        echo stumm
    fi
elif [ $1 = "light" ]; then
    echo Ändere Lautstärke
    if [ $2 = "up" ]; then
        sudo light -A 10
    elif [ $2 = "down" ]; then
        sudo light -U 10
    fi
elif [ $1 = "thinkvantage" ]; then
    st -e bash -c "echo wixer && sleep 1"
    #mpv ~/.bndo.m4a
fi
