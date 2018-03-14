// Auto-generated. Do not edit!

// (in-package chess_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Operation = require('./Operation.js');

//-----------------------------------------------------------

class Move {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.move_id = null;
      this.max_x = null;
      this.max_y = null;
      this.ops = null;
    }
    else {
      if (initObj.hasOwnProperty('move_id')) {
        this.move_id = initObj.move_id
      }
      else {
        this.move_id = 0;
      }
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
    // Serializes a message object of type Move
    // Serialize message field [move_id]
    bufferOffset = _serializer.uint32(obj.move_id, buffer, bufferOffset);
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
    //deserializes a message object of type Move
    let len;
    let data = new Move(null);
    // Deserialize message field [move_id]
    data.move_id = _deserializer.uint32(buffer, bufferOffset);
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
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'chess_msgs/Move';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f0fc94b29af0de9be3ec4719172be2d4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint32 move_id
    
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
    const resolved = new Move(null);
    if (msg.move_id !== undefined) {
      resolved.move_id = msg.move_id;
    }
    else {
      resolved.move_id = 0
    }

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

module.exports = Move;
