from conans import ConanFile, CMake

class SecureRelayConan(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   generators = "cmake"
   default_options = {
      "*:shared": False,
   }

   def configure(self):
      # We can control the options of our dependencies based on current options
      # self.options["gtest"].shared = self.options.shared
      self.options["gtest"].shared = False

   def requirements(self):
      self.requires.add("boost/1.70.0@conan/stable")
      self.requires.add("log4cplus/2.0.3@pss146/stable")
      self.requires.add("gelfcpp/0.1@pss146/stable")
      self.requires.add("gtest/1.8.1@bincrafters/stable")

   
