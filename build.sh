if [ ! -z "./main.cpp" ]; then
	echo -e "int main()\n{\n    return 0;\n}" > main.cpp
fi

mkdir -p build
cd build
rm -rf *
cmake .. && make && mv myDB ..
