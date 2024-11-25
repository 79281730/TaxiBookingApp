# TaxiBookingApp with C++ - Course 3506 Project

This is a console app using C++ and CMake.


---


## Prerequisites

- Install **CMake** and a **C++ compiler** (e.g., GCC, Clang, MSVC).

---

## Build the Project

### 1. Clone the repository
```bash
cd <project_dir>
```

### 2. Create a build directory
```bash
mkdir build
cd build
```

### 3. Configure the project
```bash
cmake ..
```

### 4. Build the project
```bash
make      # For Linux/macOS
```
Or for Ninja:
```bash
ninja     # If using Ninja
```

Or on Windows with Visual Studio, open the generated `.sln` file.

### 5. Install the project (Optional)
```bash
sudo make install    # For Linux/macOS
```
Or for Ninja:
```bash
sudo ninja install
```

### 6. Run the project
```bash
./yourproject
```

---

## Clean the build directory
```bash
rm -rf build
```