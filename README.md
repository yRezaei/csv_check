# CSV check
This is an example of reading a CSV file and check for bad value. By default, the bad value is zero.
After reading the CSV file, it checks for bad value, and if any found the value will be replaced by linear interpolation between previous and next available value. It is assumed that no adjacent bad value exists.
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
