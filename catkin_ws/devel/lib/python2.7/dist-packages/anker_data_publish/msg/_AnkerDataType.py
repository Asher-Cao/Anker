# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from anker_data_publish/AnkerDataType.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class AnkerDataType(genpy.Message):
  _md5sum = "de6762e996fc903aa001bbb12ea9d4dd"
  _type = "anker_data_publish/AnkerDataType"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float32 time_s
float32 gx
float32 gy
float32 gz
float32 ax
float32 ay
float32 az
float32 odo_right_pos
float32 odo_left_pos
float32 odo_right_vel
float32 odo_left_vel
float32 opt_pos_x
float32 opt_pos_y
uint16 opt_quality
uint16 wall_distance_right
uint16 wall_distance_left
"""
  __slots__ = ['time_s','gx','gy','gz','ax','ay','az','odo_right_pos','odo_left_pos','odo_right_vel','odo_left_vel','opt_pos_x','opt_pos_y','opt_quality','wall_distance_right','wall_distance_left']
  _slot_types = ['float32','float32','float32','float32','float32','float32','float32','float32','float32','float32','float32','float32','float32','uint16','uint16','uint16']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       time_s,gx,gy,gz,ax,ay,az,odo_right_pos,odo_left_pos,odo_right_vel,odo_left_vel,opt_pos_x,opt_pos_y,opt_quality,wall_distance_right,wall_distance_left

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(AnkerDataType, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.time_s is None:
        self.time_s = 0.
      if self.gx is None:
        self.gx = 0.
      if self.gy is None:
        self.gy = 0.
      if self.gz is None:
        self.gz = 0.
      if self.ax is None:
        self.ax = 0.
      if self.ay is None:
        self.ay = 0.
      if self.az is None:
        self.az = 0.
      if self.odo_right_pos is None:
        self.odo_right_pos = 0.
      if self.odo_left_pos is None:
        self.odo_left_pos = 0.
      if self.odo_right_vel is None:
        self.odo_right_vel = 0.
      if self.odo_left_vel is None:
        self.odo_left_vel = 0.
      if self.opt_pos_x is None:
        self.opt_pos_x = 0.
      if self.opt_pos_y is None:
        self.opt_pos_y = 0.
      if self.opt_quality is None:
        self.opt_quality = 0
      if self.wall_distance_right is None:
        self.wall_distance_right = 0
      if self.wall_distance_left is None:
        self.wall_distance_left = 0
    else:
      self.time_s = 0.
      self.gx = 0.
      self.gy = 0.
      self.gz = 0.
      self.ax = 0.
      self.ay = 0.
      self.az = 0.
      self.odo_right_pos = 0.
      self.odo_left_pos = 0.
      self.odo_right_vel = 0.
      self.odo_left_vel = 0.
      self.opt_pos_x = 0.
      self.opt_pos_y = 0.
      self.opt_quality = 0
      self.wall_distance_right = 0
      self.wall_distance_left = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_13f3H().pack(_x.time_s, _x.gx, _x.gy, _x.gz, _x.ax, _x.ay, _x.az, _x.odo_right_pos, _x.odo_left_pos, _x.odo_right_vel, _x.odo_left_vel, _x.opt_pos_x, _x.opt_pos_y, _x.opt_quality, _x.wall_distance_right, _x.wall_distance_left))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 58
      (_x.time_s, _x.gx, _x.gy, _x.gz, _x.ax, _x.ay, _x.az, _x.odo_right_pos, _x.odo_left_pos, _x.odo_right_vel, _x.odo_left_vel, _x.opt_pos_x, _x.opt_pos_y, _x.opt_quality, _x.wall_distance_right, _x.wall_distance_left,) = _get_struct_13f3H().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_13f3H().pack(_x.time_s, _x.gx, _x.gy, _x.gz, _x.ax, _x.ay, _x.az, _x.odo_right_pos, _x.odo_left_pos, _x.odo_right_vel, _x.odo_left_vel, _x.opt_pos_x, _x.opt_pos_y, _x.opt_quality, _x.wall_distance_right, _x.wall_distance_left))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 58
      (_x.time_s, _x.gx, _x.gy, _x.gz, _x.ax, _x.ay, _x.az, _x.odo_right_pos, _x.odo_left_pos, _x.odo_right_vel, _x.odo_left_vel, _x.opt_pos_x, _x.opt_pos_y, _x.opt_quality, _x.wall_distance_right, _x.wall_distance_left,) = _get_struct_13f3H().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_13f3H = None
def _get_struct_13f3H():
    global _struct_13f3H
    if _struct_13f3H is None:
        _struct_13f3H = struct.Struct("<13f3H")
    return _struct_13f3H
