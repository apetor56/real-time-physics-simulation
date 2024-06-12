# Real time phisics simulation - college project

Simple visualisation of collision detection with SAT algorithm and SFML.

https://github.com/apetor56/real-time-physics-simulation/assets/99681079/e77a710e-9259-48da-8804-0f8638bc5b5f

**Requirements:**
- **cmake** (minimum 3.19 version),
- **compiler (standard c++23)**: you can use one of these:
  - **g++** (from MinGW),
  - **clang++** (from LLVM),
  - **mvsc143** or **clang-cl** (if you are using **Visual Studio 2022**).

If you use **g++** or **clang++** make sure you have **MinGW Makefiles** installed. Unix Makefiles should work as well, but it is not included in cmake presets. To use that you have to manually type in bash cmake command with choosen generator.

---

**Instalation:**
- run `setup.bat` and choose your toolset. You should see output like this
  
    ```bash
    Pass the number to select your toolset:
    Generator                   Compiler
    1) Visual Studio 17 2022    mvsc143,
    2) Visual Studio 17 2022    clang-cl
    3) MinGW Makefile           clang++
    4) MinGW Makefile           g++
    ```
- when setup is done in root directory type 
  ```bash
  cmake --build build
  ```
Build can take a while.

---

**Run application:**
- go to `build` directory and run `CollisionDetection.exe`,
- or if you use Visual Studio run program via IDE
