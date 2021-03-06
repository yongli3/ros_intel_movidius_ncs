/*
 * Copyright (c) 2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MOVIDIUS_NCS_LIB_NCS_H
#define MOVIDIUS_NCS_LIB_NCS_H

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>

#include "movidius_ncs_lib/result.h"
#include "movidius_ncs_lib/graph.h"
#include "movidius_ncs_lib/device.h"

namespace movidius_ncs_lib
{
class Ncs
{
public:
  Ncs(int device_index,
      Device::LogLevel log_level,
      const std::string& network_conf_path);
  ~Ncs();

  ResultPtr infer(cv::Mat image, uint32_t top_n);

private:
  void init();

  void loadGraph();
  void getDevice();

  void loadStatistics(std::vector<float>& mean,
                      std::vector<float>& stddev);
  int loadInputSize();
  std::vector<std::string> loadCategories();

  static std::string appendPathSeparator(const std::string& networ_conf_path);
  static void splitIntoLines(const std::string& content,
                             std::vector<std::string>& lines);
  static std::string getFileContent(const std::string& filename);

  Device::Ptr device_;
  Graph::Ptr graph_;

  const int device_index_;
  const Device::LogLevel log_level_;
  const std::string base_path_;
  const std::string graph_file_path_;
  const std::string stat_file_path_;
  const std::string inputsize_file_path_;
  const std::string categories_file_path_;
};
}  // namespace movidius_ncs_lib
#endif  // MOVIDIUS_NCS_LIB_NCS_H
