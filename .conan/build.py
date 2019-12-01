#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
from bincrafters import build_template_header_only

if __name__ == "__main__":
    builder = build_template_header_only.get_builder(test_folder=os.path.join(".conan", "test_package"))
    builder.run()
