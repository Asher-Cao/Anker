// Auto-generated. Do not edit!

// (in-package anker_data_publish.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class AnkerDataType {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.time_s = null;
      this.gx = null;
      this.gy = null;
      this.gz = null;
      this.ax = null;
      this.ay = null;
      this.az = null;
      this.odo_right_pos = null;
      this.odo_left_pos = null;
      this.odo_right_vel = null;
      this.odo_left_vel = null;
      this.opt_pos_x = null;
      this.opt_pos_y = null;
      this.opt_quality = null;
      this.wall_distance_right = null;
      this.wall_distance_left = null;
    }
    else {
      if (initObj.hasOwnProperty('time_s')) {
        this.time_s = initObj.time_s
      }
      else {
        this.time_s = 0.0;
      }
      if (initObj.hasOwnProperty('gx')) {
        this.gx = initObj.gx
      }
      else {
        this.gx = 0.0;
      }
      if (initObj.hasOwnProperty('gy')) {
        this.gy = initObj.gy
      }
      else {
        this.gy = 0.0;
      }
      if (initObj.hasOwnProperty('gz')) {
        this.gz = initObj.gz
      }
      else {
        this.gz = 0.0;
      }
      if (initObj.hasOwnProperty('ax')) {
        this.ax = initObj.ax
      }
      else {
        this.ax = 0.0;
      }
      if (initObj.hasOwnProperty('ay')) {
        this.ay = initObj.ay
      }
      else {
        this.ay = 0.0;
      }
      if (initObj.hasOwnProperty('az')) {
        this.az = initObj.az
      }
      else {
        this.az = 0.0;
      }
      if (initObj.hasOwnProperty('odo_right_pos')) {
        this.odo_right_pos = initObj.odo_right_pos
      }
      else {
        this.odo_right_pos = 0.0;
      }
      if (initObj.hasOwnProperty('odo_left_pos')) {
        this.odo_left_pos = initObj.odo_left_pos
      }
      else {
        this.odo_left_pos = 0.0;
      }
      if (initObj.hasOwnProperty('odo_right_vel')) {
        this.odo_right_vel = initObj.odo_right_vel
      }
      else {
        this.odo_right_vel = 0.0;
      }
      if (initObj.hasOwnProperty('odo_left_vel')) {
        this.odo_left_vel = initObj.odo_left_vel
      }
      else {
        this.odo_left_vel = 0.0;
      }
      if (initObj.hasOwnProperty('opt_pos_x')) {
        this.opt_pos_x = initObj.opt_pos_x
      }
      else {
        this.opt_pos_x = 0.0;
      }
      if (initObj.hasOwnProperty('opt_pos_y')) {
        this.opt_pos_y = initObj.opt_pos_y
      }
      else {
        this.opt_pos_y = 0.0;
      }
      if (initObj.hasOwnProperty('opt_quality')) {
        this.opt_quality = initObj.opt_quality
      }
      else {
        this.opt_quality = 0;
      }
      if (initObj.hasOwnProperty('wall_distance_right')) {
        this.wall_distance_right = initObj.wall_distance_right
      }
      else {
        this.wall_distance_right = 0;
      }
      if (initObj.hasOwnProperty('wall_distance_left')) {
        this.wall_distance_left = initObj.wall_distance_left
      }
      else {
        this.wall_distance_left = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type AnkerDataType
    // Serialize message field [time_s]
    bufferOffset = _serializer.float64(obj.time_s, buffer, bufferOffset);
    // Serialize message field [gx]
    bufferOffset = _serializer.float64(obj.gx, buffer, bufferOffset);
    // Serialize message field [gy]
    bufferOffset = _serializer.float64(obj.gy, buffer, bufferOffset);
    // Serialize message field [gz]
    bufferOffset = _serializer.float64(obj.gz, buffer, bufferOffset);
    // Serialize message field [ax]
    bufferOffset = _serializer.float64(obj.ax, buffer, bufferOffset);
    // Serialize message field [ay]
    bufferOffset = _serializer.float64(obj.ay, buffer, bufferOffset);
    // Serialize message field [az]
    bufferOffset = _serializer.float64(obj.az, buffer, bufferOffset);
    // Serialize message field [odo_right_pos]
    bufferOffset = _serializer.float64(obj.odo_right_pos, buffer, bufferOffset);
    // Serialize message field [odo_left_pos]
    bufferOffset = _serializer.float64(obj.odo_left_pos, buffer, bufferOffset);
    // Serialize message field [odo_right_vel]
    bufferOffset = _serializer.float64(obj.odo_right_vel, buffer, bufferOffset);
    // Serialize message field [odo_left_vel]
    bufferOffset = _serializer.float64(obj.odo_left_vel, buffer, bufferOffset);
    // Serialize message field [opt_pos_x]
    bufferOffset = _serializer.float64(obj.opt_pos_x, buffer, bufferOffset);
    // Serialize message field [opt_pos_y]
    bufferOffset = _serializer.float64(obj.opt_pos_y, buffer, bufferOffset);
    // Serialize message field [opt_quality]
    bufferOffset = _serializer.uint16(obj.opt_quality, buffer, bufferOffset);
    // Serialize message field [wall_distance_right]
    bufferOffset = _serializer.uint16(obj.wall_distance_right, buffer, bufferOffset);
    // Serialize message field [wall_distance_left]
    bufferOffset = _serializer.uint16(obj.wall_distance_left, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type AnkerDataType
    let len;
    let data = new AnkerDataType(null);
    // Deserialize message field [time_s]
    data.time_s = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [gx]
    data.gx = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [gy]
    data.gy = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [gz]
    data.gz = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [ax]
    data.ax = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [ay]
    data.ay = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [az]
    data.az = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [odo_right_pos]
    data.odo_right_pos = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [odo_left_pos]
    data.odo_left_pos = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [odo_right_vel]
    data.odo_right_vel = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [odo_left_vel]
    data.odo_left_vel = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [opt_pos_x]
    data.opt_pos_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [opt_pos_y]
    data.opt_pos_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [opt_quality]
    data.opt_quality = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [wall_distance_right]
    data.wall_distance_right = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [wall_distance_left]
    data.wall_distance_left = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 110;
  }

  static datatype() {
    // Returns string type for a message object
    return 'anker_data_publish/AnkerDataType';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1a718d0c383faab3290a892f624d74ab';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 time_s
    float64 gx
    float64 gy
    float64 gz
    float64 ax
    float64 ay
    float64 az
    float64 odo_right_pos
    float64 odo_left_pos
    float64 odo_right_vel
    float64 odo_left_vel
    float64 opt_pos_x
    float64 opt_pos_y
    uint16 opt_quality
    uint16 wall_distance_right
    uint16 wall_distance_left
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new AnkerDataType(null);
    if (msg.time_s !== undefined) {
      resolved.time_s = msg.time_s;
    }
    else {
      resolved.time_s = 0.0
    }

    if (msg.gx !== undefined) {
      resolved.gx = msg.gx;
    }
    else {
      resolved.gx = 0.0
    }

    if (msg.gy !== undefined) {
      resolved.gy = msg.gy;
    }
    else {
      resolved.gy = 0.0
    }

    if (msg.gz !== undefined) {
      resolved.gz = msg.gz;
    }
    else {
      resolved.gz = 0.0
    }

    if (msg.ax !== undefined) {
      resolved.ax = msg.ax;
    }
    else {
      resolved.ax = 0.0
    }

    if (msg.ay !== undefined) {
      resolved.ay = msg.ay;
    }
    else {
      resolved.ay = 0.0
    }

    if (msg.az !== undefined) {
      resolved.az = msg.az;
    }
    else {
      resolved.az = 0.0
    }

    if (msg.odo_right_pos !== undefined) {
      resolved.odo_right_pos = msg.odo_right_pos;
    }
    else {
      resolved.odo_right_pos = 0.0
    }

    if (msg.odo_left_pos !== undefined) {
      resolved.odo_left_pos = msg.odo_left_pos;
    }
    else {
      resolved.odo_left_pos = 0.0
    }

    if (msg.odo_right_vel !== undefined) {
      resolved.odo_right_vel = msg.odo_right_vel;
    }
    else {
      resolved.odo_right_vel = 0.0
    }

    if (msg.odo_left_vel !== undefined) {
      resolved.odo_left_vel = msg.odo_left_vel;
    }
    else {
      resolved.odo_left_vel = 0.0
    }

    if (msg.opt_pos_x !== undefined) {
      resolved.opt_pos_x = msg.opt_pos_x;
    }
    else {
      resolved.opt_pos_x = 0.0
    }

    if (msg.opt_pos_y !== undefined) {
      resolved.opt_pos_y = msg.opt_pos_y;
    }
    else {
      resolved.opt_pos_y = 0.0
    }

    if (msg.opt_quality !== undefined) {
      resolved.opt_quality = msg.opt_quality;
    }
    else {
      resolved.opt_quality = 0
    }

    if (msg.wall_distance_right !== undefined) {
      resolved.wall_distance_right = msg.wall_distance_right;
    }
    else {
      resolved.wall_distance_right = 0
    }

    if (msg.wall_distance_left !== undefined) {
      resolved.wall_distance_left = msg.wall_distance_left;
    }
    else {
      resolved.wall_distance_left = 0
    }

    return resolved;
    }
};

module.exports = AnkerDataType;
