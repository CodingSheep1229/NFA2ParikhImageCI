rm -rf build/*
cd build
CXX_FLAGS="-Wall -pedantic -Werror -Wno-variadic-macros -Wno-long-long -Wno-shadow"
CXX_FLAGS=${CXX_FLAGS}" "${ENV_CXX_FLAGS}
cmake CMAKE_OPTIONS=${CMAKE_OPTIONS}" "${ENV_CMAKE_OPTIONS} -DCMAKE_CXX_FLAGS=${CXX_FLAGS} -DBUILD_TESTS=ON .. 
make
ctest