# CSV check
This is a simple example of reading CSV file and check for bad value which by default is zero.
It reads csv data and it checks for bad value, if found the value will replaced by linear interpolation method:
```
interpolated_value = (value_1 * (1.0f - interpolation_ratio) + value_2 * interpolation_ratio)
```
The interpolation_ratio value can be set to any number between 0 and 1. This will define how much the interpolated_value should closer to value_1 or value_2.

## Required
    1. Visual Studio (V16) / GCC (V7.X)
    2. CMake (V3.x)

## How to build
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release/Debug
cmake --build . --config Release/Debug 
```

## How to run
```
cd build
csv_check <input_file_path> <output_file_path>
```

## Example
```
cd build
csv_check.exe ../test/test.csv ../test/res.csv
```
