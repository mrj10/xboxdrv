/*
**  Xbox360 USB Gamepad Userspace Driver
**  Copyright (C) 2012 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEADER_XBOXDRV_AXIS_EVENT_FACTORY_HPP
#define HEADER_XBOXDRV_AXIS_EVENT_FACTORY_HPP

#include "axis_event.hpp"

class UInput;

class AxisEventFactory
{
private:
  UInput& m_uinput;
  int  m_slot;
  bool m_extra_devices;

public:
  AxisEventFactory(UInput& uinput, int slot, bool extra_devices);
  
  AxisEventPtr invalid();

  AxisEventPtr create_abs(int device_id, int code, int min, int max, int fuzz, int flat);
  AxisEventPtr create_rel(int device_id, int code, int repeat = 10, float value = 5);

  /** If an AxisEvent gets created the user has to set min/max with set_axis_range() */ 
  AxisEventPtr from_string(const std::string& str);

private:
  AxisEventFactory(const AxisEventFactory&);
  AxisEventFactory& operator=(const AxisEventFactory&);
};

#endif

/* EOF */
