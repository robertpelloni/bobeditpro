# Deployment Instructions
Currently, Audacity 4 is built using CMake.
```bash
mkdir build && cd build
cmake .. -G "Unix Makefiles"
make -j$(nproc)
```
Ensure `muse_framework` is initialized (`git submodule update --init --recursive`).
