echo -n "Fetching resources, this may take a minute..."

TEMP_PATH="$HOME/tmp_bomberman_res"
SOUND_PATH="sound"
GRAPHIX_PATH="renderer"

git clone https://github.com/TalPat/bombermanres.git $TEMP_PATH &> /dev/null

cp -r "$TEMP_PATH/$SOUND_PATH/res" ./$SOUND_PATH
cp -r "$TEMP_PATH/$GRAPHIX_PATH/res" ./$GRAPHIX_PATH

rm -rf $TEMP_PATH

echo "done"