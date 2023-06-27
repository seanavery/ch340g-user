from setuptools import setup
from setuptools.extension import Extension
from Cython.Build import cythonize

# Define the extension module
extensions = [
    Extension(
        name="ch340g",
        sources=["ch340g.pyx"],
        language="c++",
        libraries=["usb-1.0"],  # Add any required libraries here
        output_dir="build",
    )
]

# Configure the setup
setup(
    name="ch340g",
    ext_modules=cythonize(extensions),
)