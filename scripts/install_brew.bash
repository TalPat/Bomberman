echo -n "Finding brew..."
if command -v brew >> /dev/null;
then
    echo "found"
    exit 0;
else
    echo "not found"

    while true; do
        read -p "Do you wish to install brew? [yes/no] - " yn
        case $yn in
            yes ) break;;
            no ) echo "brew not install"; exit 1;;
            * ) echo "Please answer yes or no.";;
        esac
    done

    echo "installing brew"
    sh -c "$(curl -fsSL https://raw.githubusercontent.com/wethinkcode/homebrew/master/install.sh)"
fi;
