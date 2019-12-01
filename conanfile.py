from conans import ConanFile, CMake

class SecureRelayConan(ConanFile):
   name = "log4cplus_gelf"
   version = "0.1"
   license = "Boost Software License v1.0"
   author = "Perepelitsyn Stanislav <stas.perepel@gmail.com>"
   url = "https://github.com/pss146/log4cplus_gelf"
   description = "GELF Appender for Log4cplus"
   topics = ("Log4cplus", "gelf")
   settings = "os", "compiler", "build_type", "arch"
   options = {"shared": [True, False]}
   default_options = "shared=False"
   generators = "cmake"
   exports_sources = ["*"]

   def configure(self):
      # We can control the options of our dependencies based on current options
      # self.options["gtest"].shared = self.options.shared
      self.options["gtest"].shared = False
      self.options["gtest"].no_main = True

   def requirements(self):
      self.requires.add("boost/1.70.0@conan/stable")
      self.requires.add("log4cplus/2.0.3@pss146/stable")
      self.requires.add("gelfcpp/0.1@pss146/stable")
      self.requires.add("gtest/1.8.1@bincrafters/stable")

   def _configure_cmake(self):
      cmake = CMake(self)
      cmake.configure()
      return cmake

   def build(self):
      cmake = self._configure_cmake()
      cmake.build()

   def package(self):
      self.copy("*.h", dst="include", src="include")
      self.copy("*.lib", dst="lib", keep_path=False)
      self.copy("*.dll", dst="bin", keep_path=False)
      self.copy("*.dylib*", dst="lib", keep_path=False)
      self.copy("*.so", dst="lib", keep_path=False)
      self.copy("*.a", dst="lib", keep_path=False)

   def package_info(self):
      self.cpp_info.libs = ['log4cplus_gelf']

   
