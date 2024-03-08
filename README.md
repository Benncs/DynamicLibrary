# Dynamic Library Loader
<div align="left">

  [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
</div>
This repository provides a dynamic library loader, serving as a header-only library. It offers a wrapper around OS-specific API shared object loading, enabling seamless integration into your projects. Additionally, it includes a header file to establish a standardized method for defining modules using macros.

# Features 

- OS-Specific API Wrapper: Simplifies the process of loading shared objects by providing a unified interface across different operating systems.

- Standardized Module Definition: The included header file enables developers to define modules using macros, ensuring consistency and ease of use.

- Cross-Platform Compatibility: Works seamlessly across various operating systems, allowing developers to write code without worrying about platform-specific nuances.


# Usage

An example is provided in "../examples"

## For Module Definition:

1. **Include Header:** Include the `<dyn_module.hpp>` header file to access macro definitions.

2. **Define Module Header:** Define a header for your module, outlining the signature of the functions that need to be exported to the application. Create a "module" structure containing function pointers corresponding to the defined function signatures.

## For the External Library:

1. **Include Module Header:** Include the header file of your module.

2. **Implement Functions:** Implement the necessary functions required by your module.

3. **Create Global Variable:** Create a global variable named `module` with function pointers pointing to the functions you've implemented and need to export. You can include "private" functions within the module that are not included in the module definition.

## Example:

An example is provided to demonstrate the usage. From the application's perspective (Loader):

1. **Include Dynamic Library Loader Header:** Include `"dynlib.hpp"`.

2. **Include Library Header:** Include the common header for your library.

3. **Provide Object Path:** Provide the path of the `.so` (or `.dll`) object to import, where the definitions are located.

4. **Retrieve Imported Module:** Retrieve the imported module.

*Note: If the module's name isn't specified, it is assumed that the external library developer followed the naming conventions given in the header. If not, you can use a custom module name and typename to define the struct manually.*



# License

This project is licensed under the MIT License, allowing for unrestricted use, modification, and distribution. Please review the LICENSE file for detailed licensing terms.