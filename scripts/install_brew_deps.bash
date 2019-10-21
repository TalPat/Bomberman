# Ensure brew exists
echo Checking dependancies

if ! command -v brew >> /dev/null;
then
    echo "Error: brew not found"
    exit 1;
fi

for dep in "$@"
do
    echo -n "Finding $dep..."
    if brew list $dep &> /dev/null;
    then
        echo "found"
    else
        echo "not found"
        echo "Installing $dep"
        brew install $dep
    fi
done