# Copyright 2018 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#
# Get a list of googletest versions and the location of their archives.
#
# The list is just the set of versions provided by this package.
# The archives are stored in this package's repository and are not downloaded.
#
# :param output_versions: name of the variable in which to store the list of versions
# :type output_versions: string
# :param output_locations: name of the variable in which to store the list of locations
# :type output_locations: string
# :param output_md5s: name of the variable in which to store the list of MD5 sums
# :type output_md5s: string
#
# @public
#
macro(osrf_testing_tools_cpp_get_googletest_versions output_versions output_locations output_md5s)
  # Manually maintained list of googletest versions provided by this package.
  set(${output_versions}
    1.14
  )
  # Manually maintained list of googletest locations in this package, indexed the same as versions.
  # They are relative to the VENDOR_DIR, which is configurable.
  set(${output_locations}
    "google/googletest/release-1.14.0.tar.gz"
  )
  # Manually maintained list of MD5 sums for the archives, indexed the same as the versions.
  set(${output_md5s}
    "c8340a482851ef6a3fe618a082304cfc"
  )
endmacro()
