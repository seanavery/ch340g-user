from setuptools import setup
from setuptools.extension import Extension
from Cython.Build import cythonize

# Define the extension module
extensions = [
    Extension(
        name="ch340g",
        sources=["ch340g.pyx"],
        language="c++",
        include_dirs=["."],  # Add the directory containing ch340g.h and ch340g.cpp
        libraries=["usb-1.0"],  # Add any required libraries here
        output_dir="cybuild",
    )
]

# Configure the setup
setup(
    name="ch340g",
    ext_modules=cythonize(extensions),
)