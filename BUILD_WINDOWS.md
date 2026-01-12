# Windows 编译指南

本文档说明如何在 Windows 系统上编译 orientnet 项目。

## 前置要求

### 必需软件

1. **CMake** (版本 >= 3.16)
   - 下载地址: https://cmake.org/download/
   - 安装时选择 "Add CMake to system PATH"

2. **C++ 编译器** (支持 C++17 标准)
   - 选项1: **Visual Studio 2019 或更高版本** (推荐)
     - 下载地址: https://visualstudio.microsoft.com/
     - 安装时选择 "Desktop development with C++" 工作负载
   - 选项2: **MinGW-w64**
     - 下载地址: https://www.mingw-w64.org/downloads/
     - 或使用 MSYS2: https://www.msys2.org/

## 编译步骤

### 方法1: 使用 Visual Studio (MSVC) - 推荐

1. **打开 Visual Studio Developer Command Prompt**
   - 在开始菜单搜索 "Developer Command Prompt for VS"
   - 或使用 "x64 Native Tools Command Prompt for VS"

2. **进入项目目录**
   ```cmd
   cd C:\orient\my\orientnet
   ```

3. **创建构建目录并配置**
   ```cmd
   mkdir build
   cd build
   cmake .. -DBUILD_TEST=ON
   ```
   
   如果需要指定生成器或架构:
   ```cmd
   cmake .. -G "Visual Studio 16 2019" -A x64 -DBUILD_TEST=ON
   ```
   
   或者使用 Visual Studio 2017:
   ```cmd
   cmake .. -G "Visual Studio 15 2017 Win64" -DBUILD_TEST=ON
   ```

4. **编译项目**
   ```cmd
   cmake --build . --config Release
   ```
   
   或者编译 Debug 版本:
   ```cmd
   cmake --build . --config Debug
   ```

5. **运行测试** (如果编译了测试)
   ```cmd
   cd ..
   bin\test.exe
   ```

### 方法2: 使用 Visual Studio GUI

1. **打开 Visual Studio**

2. **打开项目**
   - File -> Open -> CMake...
   - 选择项目根目录的 `CMakeLists.txt`

3. **配置 CMake**
   - 在 CMake 设置中，添加 `BUILD_TEST` 变量，值为 `ON`

4. **编译**
   - Build -> Build All (或按 F7)
   - 选择配置: Debug 或 Release

### 方法3: 使用 MinGW-w64

1. **安装 MinGW-w64**
   - 如果使用 MSYS2:
     ```bash
     pacman -S mingw-w64-x86_64-gcc
     pacman -S mingw-w64-x86_64-cmake
     pacman -S mingw-w64-x86_64-make
     ```

2. **打开 MSYS2 MinGW 64-bit 终端**

3. **进入项目目录**
   ```bash
   cd /c/orient/my/orientnet
   ```

4. **创建构建目录并配置**
   ```bash
   mkdir -p build
   cd build
   cmake .. -G "MinGW Makefiles" -DBUILD_TEST=ON
   ```

5. **编译**
   ```bash
   cmake --build . -j4
   ```

6. **运行测试**
   ```bash
   cd ..
   ./bin/test.exe
   ```

## 常见问题

### 1. CMake 找不到编译器

**问题**: `CMake Error: No CMAKE_CXX_COMPILER could be found.`

**解决方案**:
- 确保已安装 Visual Studio 或 MinGW
- 在 Visual Studio Developer Command Prompt 中运行 CMake
- 或手动指定编译器路径:
  ```cmd
  cmake .. -DCMAKE_CXX_COMPILER="C:/Program Files/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.xx.xxxxx/bin/Hostx64/x64/cl.exe"
  ```

### 2. 找不到 pthread

**问题**: `Could NOT find Threads (missing: Threads_FOUND)`

**解决方案**:
- Windows 上 CMake 会自动使用 Windows 线程库
- 如果使用 MinGW，确保安装了 `mingw-w64-x86_64-pthreads-w32`

### 3. Protobuf 依赖问题

**问题**: 如果项目依赖 3rdparty/protobuf，可能需要先编译 protobuf

**解决方案**:
```cmd
cd 3rdparty\protobuf
mkdir build
cd build
cmake .. -Dprotobuf_BUILD_TESTS=OFF
cmake --build . --config Release
```

### 4. 清理构建

如果需要重新配置:
```cmd
rmdir /s /q build
mkdir build
cd build
cmake .. -DBUILD_TEST=ON
```

## 输出文件位置

- 库文件: `build/Release/orientnet.lib` (或 `Debug/orientnet.lib`)
- 测试程序: `bin/test.exe`
- 示例程序: `example/` 目录下的可执行文件

## 编译选项

- `BUILD_TEST`: 是否编译测试程序 (ON/OFF, 默认 OFF)
- `CMAKE_BUILD_TYPE`: 构建类型 (Debug/Release/RelWithDebInfo/MinSizeRel)
  - Visual Studio 使用 `--config` 参数指定
  - MinGW 使用 `-DCMAKE_BUILD_TYPE=Release`

## 示例命令总结

**Visual Studio (Release):**
```cmd
mkdir build && cd build
cmake .. -DBUILD_TEST=ON
cmake --build . --config Release
```

**Visual Studio (Debug):**
```cmd
mkdir build && cd build
cmake .. -DBUILD_TEST=ON
cmake --build . --config Debug
```

**MinGW:**
```bash
mkdir -p build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_TEST=ON
cmake --build . -j4
```

