if [ ! -f main.cpp ]; then
	cat  << EOF > main.cpp
#include <JsonhlDeserializer.hpp>
#include <dbhlCommand.hpp>

int main(int ac, char **av)
{
    dbHL::CommandHandler handler;
    handler.launchDB();
    return 0;
}
EOF
fi

rm -f myDB
mkdir -p build
cd build

if [ -n "$1" ]; then
	if [ "$1" == "--all" ]; then
		rm -rf *
	else
		echo "Unrecognized option: $1" 1>&2
		echo "You can use --all to rebuild all the project or just ./build.sh to build only the necessary"
		exit 1
	fi
fi
cmake .. && make && mv myDB ..
