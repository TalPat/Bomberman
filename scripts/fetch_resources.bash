echo -n "Fetching resources, this may take a minute..."

TEMP_PATH="$HOME/tmp_bomberman_res"
SOUND_PATH="sound/res"
GRAPHIX_PATH="renderer/res"

git clone https://github.com/wseegers/bomberman $TEMP_PATH &> /dev/null

cp -r "$TEMP_PATH"/"$SOUND_PATH" ./$SOUND_PATH
cp -r "$TEMP_PATH"/"$GRAPHIX_PATH" ./$GRAPHIX_PATH

rm -rf $TEMP_PATH

echo "done"