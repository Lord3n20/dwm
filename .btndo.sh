if [ $1 = "vol" ]; then
  if [ $2 = "up" ]; then
    pulsemixer --change-volume +5
  elif [ $2 = "down" ]; then
    pulsemixer --change-volume -5
  elif [ $2 = "mute" ]; then
    pactl set-sink-mute @DEFAULT_SINK@ toggle
  fi
elif [ $1 = "light" ]; then
  if [ $2 = "down" ]; then
    sudo light -U 5
  elif [ $2 = "up" ]; then
    sudo light -A 10
  fi
elif [ $1 = "screen" ]; then
  flameshot gui
elif [ $1 = "reloadbg" ]; then
  feh --no-fehbg --bg-fill --randomize ~/.wall/*
elif [ $1 = "playback" ]; then
  if [[ $2 = "toggle" ]]; then
    playerctl play-pause
  elif [[ $2 = "again" ]]; then
    playerctl previous
  elif [[ $2 = "skip" ]]; then
    playerctl next
  fi
fi
