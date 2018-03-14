// Auto-generated. Do not edit!

// (in-package chess_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Result {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.move_id = null;
      this.res = null;
      this.msg = null;
    }
    else {
      if (initObj.hasOwnProperty('move_id')) {
        this.move_id = initObj.move_id
      }
      else {
        this.move_id = 0;
      }
      if (initObj.hasOwnProperty('res')) {
        this.res = initObj.res
      }
      else {
        this.res = false;
      }
      if (initObj.hasOwnProperty('msg')) {
        this.msg = initObj.msg
      }
      else {
        this.msg = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Result
    // Serialize message field [move_id]
    bufferOffset = _serializer.uint32(obj.move_id, buffer, bufferOffset);
    // Serialize message field [res]
    bufferOffset = _serializer.bool(obj.res, buffer, bufferOffset);
    // Serialize message field [msg]
    bufferOffset = _serializer.string(obj.msg, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Result
    let len;
    let data = new Result(null);
    // Deserialize message field [move_id]
    data.move_id = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [res]
    data.res = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [msg]
    data.msg = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.msg.length;
    return length + 9;
  }

  static datatype() {
    // Returns string type for a message object
    return 'chess_msgs/Result';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ae465118b1a9be7edaa0ca21933a04d1';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint32 move_id
    
    bool res
    string msg
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Result(null);
    if (msg.move_id !== undefined) {
      resolved.move_id = msg.move_id;
    }
    else {
      resolved.move_id = 0
    }

    if (msg.res !== undefined) {
      resolved.res = msg.res;
    }
    else {
      resolved.res = false
    }

    if (msg.msg !== undefined) {
      resolved.msg = msg.msg;
    }
    else {
      resolved.msg = ''
    }

    return resolved;
    }
};

module.exports = Result;
