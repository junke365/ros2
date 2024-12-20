// Copyright (c) 2020, Willow Garage, Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the copyright holder nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.


#include <benchmark/benchmark.h>
#include <urdf_parser/urdf_parser.h>

#include <string>

#include "urdf/model.hpp"

const char test_xml[] =
  "<?xml verison=\"1.0\"?>"
  "<robot name=\"benchy_bot\">"
  "  <link name=\"link1\">"
  "    <inertial>"
  "      <mass value=\"1\"/>"
  "      <inertia ixx=\"1\" iyy=\"1\" izz=\"1\" ixy=\"0\" ixz=\"0\" iyz=\"0\"/>"
  "    </inertial>"
  "    <visual>"
  "      <geometry>"
  "        <box size=\"1 1 1\"/>"
  "      </geometry>"
  "    </visual>"
  "    <collision>"
  "      <geometry>"
  "        <box size=\"1 1 1\"/>"
  "      </geometry>"
  "    </collision>"
  "  </link>"
  "</robot>";

static void BM_no_plugin(benchmark::State & state)
{
  for (auto _ : state) {
    if (nullptr == urdf::parseURDF(test_xml)) {
      state.SkipWithError("Failed to read xml");
      break;
    }
  }
}

static void BM_with_plugin(benchmark::State & state)
{
  for (auto _ : state) {
    urdf::Model m;
    if (!m.initString(test_xml)) {
      state.SkipWithError("Failed to read xml");
      break;
    }
  }
}

BENCHMARK(BM_no_plugin);
BENCHMARK(BM_with_plugin);

BENCHMARK_MAIN();
