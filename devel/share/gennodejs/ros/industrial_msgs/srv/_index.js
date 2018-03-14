
"use strict";

let GetRobotInfo = require('./GetRobotInfo.js')
let SetDrivePower = require('./SetDrivePower.js')
let StopMotion = require('./StopMotion.js')
let StartMotion = require('./StartMotion.js')
let SetRemoteLoggerLevel = require('./SetRemoteLoggerLevel.js')
let CmdJointTrajectory = require('./CmdJointTrajectory.js')

module.exports = {
  GetRobotInfo: GetRobotInfo,
  SetDrivePower: SetDrivePower,
  StopMotion: StopMotion,
  StartMotion: StartMotion,
  SetRemoteLoggerLevel: SetRemoteLoggerLevel,
  CmdJointTrajectory: CmdJointTrajectory,
};
