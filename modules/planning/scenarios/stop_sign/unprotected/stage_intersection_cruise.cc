/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 **/

#include <string>
#include <vector>

#include "modules/planning/scenarios/stop_sign/unprotected/stage_intersection_cruise.h"

#include "cyber/common/log.h"
#include "modules/planning/common/frame.h"
#include "modules/planning/scenarios/util/util.h"

namespace apollo {
namespace planning {
namespace scenario {
namespace stop_sign {

using common::TrajectoryPoint;

Stage::StageStatus StopSignUnprotectedStageIntersectionCruise::Process(
    const TrajectoryPoint& planning_init_point, Frame* frame) {
  ADEBUG << "stage: IntersectionCruise";
  CHECK_NOTNULL(frame);

  bool plan_ok = ExecuteTaskOnReferenceLine(planning_init_point, frame);
  if (!plan_ok) {
    AERROR << "StopSignUnprotectedStageIntersectionCruise plan error";
  }

  // check pass pnc_junction
  const auto& reference_line_info = frame->reference_line_info().front();
  if (!scenario::CheckInsidePnCJunction(reference_line_info)) {
    return FinishStage();
  }

  return Stage::RUNNING;
}

Stage::StageStatus StopSignUnprotectedStageIntersectionCruise::FinishStage() {
  return FinishScenario();
}

}  // namespace stop_sign
}  // namespace scenario
}  // namespace planning
}  // namespace apollo
