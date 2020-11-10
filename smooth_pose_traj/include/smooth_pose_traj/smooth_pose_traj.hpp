/**
 * @file smooth_pose_traj.h
 * @copyright Copyright (c) 2020, Southwest Research Institute
 *
 * @par License
 * Software License Agreement (Apache License)
 * @par
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * @par
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef INCLUDE_SMOOTH_POSE_TRAJ_H
#define INCLUDE_SMOOTH_POSE_TRAJ_H

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <boost/math/interpolators/cubic_b_spline.hpp>

namespace SmoothPoseTraj
{

  class SmoothPoseTraj
  {
    
  public:
    SmoothPoseTraj()
      {
      }
    SmoothPoseTraj(const geometry_msgs::PoseArray& input_poses, const double& point_spacing);

    ~SmoothPoseTraj()
    {
      free(sx);
      free(sy);
      free(sz);
      free(sqx);
      free(sqy);
      free(sqz);
      free(sqw);
    }

    bool process(geometry_msgs::PoseArray& output_poses, double point_spacing = -1);

    bool qnormalize(geometry_msgs::Pose& P);
  private:
    geometry_msgs::Pose interpPose(const geometry_msgs::Pose& P1, const geometry_msgs::Pose& P2, double alpha);
    geometry_msgs::Pose getPoseAtCrowDistance(double& t, double point_spacing, double &actual_distance);
    geometry_msgs::Pose getNPtAveragePose(const geometry_msgs::PoseArray& input_poses, int pose_index, int n_pts);
    bool align_x_to_next(geometry_msgs::PoseArray &poses);
    
  public:
    double point_spacing_, total_distance_, max_t_;
    
    boost::math::cubic_b_spline<double> sx_;
    boost::math::cubic_b_spline<double> sy_;
    boost::math::cubic_b_spline<double> sz_;
    boost::math::cubic_b_spline<double> sqx_;
    boost::math::cubic_b_spline<double> sqy_;
    boost::math::cubic_b_spline<double> sqz_;
    boost::math::cubic_b_spline<double> sqw_;

  private:
    boost::math::cubic_b_spline<double>* sx;
    boost::math::cubic_b_spline<double>* sy;
    boost::math::cubic_b_spline<double>* sz;
    boost::math::cubic_b_spline<double>* sqx;
    boost::math::cubic_b_spline<double>* sqy;
    boost::math::cubic_b_spline<double>* sqz;
    boost::math::cubic_b_spline<double>* sqw;

  }; // end class SmoothPoseTraj

} // end namespace SmoothPoseTraj
#endif // INCLUDE_SMOOTH_POSE_TRAJ_H
