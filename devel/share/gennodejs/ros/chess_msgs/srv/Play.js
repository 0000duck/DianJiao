// Auto-generated. Do not edit!

// (in-package chess_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Operation = require('../msg/Operation.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class PlayRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.max_x = null;
      this.max_y = null;
      this.ops = null;
    }
    else {
      if (initObj.hasOwnProperty('max_x')) {
        this.max_x = initObj.max_x
      }
      else {
        this.max_x = 0.0;
      }
      if (initObj.hasOwnProperty('max_y')) {
        this.max_y = initObj.max_y
      }
      else {
        this.max_y = 0.0;
      }
      if (initObj.hasOwnProperty('ops')) {
        this.ops = initObj.ops
      }
      else {
        this.ops = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PlayRequest
    // Serialize message field [max_x]
    bufferOffset = _serializer.float32(obj.max_x, buffer, bufferOffset);
    // Serialize message field [max_y]
    bufferOffset = _serializer.float32(obj.max_y, buffer, bufferOffset);
    // Serialize message field [ops]
    // Serialize the length for message field [ops]
    bufferOffset = _serializer.uint32(obj.ops.length, buffer, bufferOffset);
    obj.ops.forEach((val) => {
      bufferOffset = Operation.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PlayRequest
    let len;
    let data = new PlayRequest(null);
    // Deserialize message field [max_x]
    data.max_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [max_y]
    data.max_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ops]
    // Deserialize array length for message field [ops]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.ops = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.ops[i] = Operation.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 28 * object.ops.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a service object
    return 'chess_msgs/PlayRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a0e5c4809f45bf914ed4eff2bc1a842b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    float32 max_x
    float32 max_y
    Operation[] ops
    
    ================================================================================
    MSG: chess_msgs/Operation
    # operation type go = 0 ; capture = 1 ; wait = 2
    uint32 OPERATION_GO = 0      
    uint32 OPERATION_CAPTURE = 1
    uint32 OPERATION_WAIT = 2
    
    # position type far = 0; near = 1
    uint32 POSITION_FAR = 0
    uint32 POSITION_NEAR = 1
    
    uint32 type
    
    uint32  pick_type
    float32 pick_x
    float32 pick_y
    
    uint32  place_type
    float32 place_x
    float32 place_y
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PlayRequest(null);
    if (msg.max_x !== undefined) {
      resolved.max_x = msg.max_x;
    }
    else {
      resolved.max_x = 0.0
    }

    if (msg.max_y !== undefined) {
      resolved.max_y = msg.max_y;
    }
    else {
      resolved.max_y = 0.0
    }

    if (msg.ops !== undefined) {
      resolved.ops = new Array(msg.ops.length);
      for (let i = 0; i < resolved.ops.length; ++i) {
        resolved.ops[i] = Operation.Resolve(msg.ops[i]);
      }
    }
    else {
      resolved.ops = []
    }

    return resolved;
    }
};

class PlayResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.res = null;
      this.msg = null;
    }
    else {
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
    // Serializes a message object of type PlayResponse
    // Serialize message field [res]
    bufferOffset = _serializer.bool(obj.res, buffer, bufferOffset);
    // Serialize message field [msg]
    bufferOffset = _serializer.string(obj.msg, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PlayResponse
    let len;
    let data = new PlayResponse(null);
    // Deserialize message field [res]
    data.res = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [msg]
    data.msg = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.msg.length;
    return length + 5;
  }

  static datatype() {
    // Returns string type for a service object
    return 'chess_msgs/PlayResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '21744300052380276c040efd28f6660f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    bool res
    string msg
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PlayResponse(null);
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

module.exports = {
  Request: PlayRequest,
  Response: PlayResponse,
  md5sum() { return '9ca8bd096976365b8f806f82ceddea70'; },
  datatype() { return 'chess_msgs/Play'; }
};
