# Build Guide
This is a comprehensive list of flags to give when building
subchemica. Not all features are supported on all platforms
and not all flags may be combined. Some flags can be combned to
customize the build.

- __-l/--library__ No local chemical library.
- __-g/--graphics__ No graphics except exporting images.
- __-t/--threads__ No multithreading.
- __-s/--simple__ Simplifies depenencies to a minimum.

# Examples
If you with to build without a chemical library or gui:
```./compile -l -g```
