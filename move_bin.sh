# Copy SDL bin files to the root directory

BASEDIR=$(dirname $0)
if [ $BASEDIR == "." ]
then
    echo "if"
    cp bin/*.dll ..
else
    echo "else"
    cp SDL2-Utilites/bin/*.dll .
fi